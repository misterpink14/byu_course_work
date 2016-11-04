module ExtInt

using Error
using Lexer

export parse, calc, Num
 
abstract OWL
abstract RetVal
abstract Environment
 
type Num <: OWL
    n::Real
end

type Unaryop <: OWL
    op::Symbol
    s::OWL
end

type Binop <: OWL
    op::Symbol
    lhs::OWL
    rhs::OWL
end

type If0 <: OWL
    condition::OWL
    zero_branch::OWL
    nonzero_branch::OWL
end

type Binding <: OWL
    name::Symbol
    binding_expr::OWL
end

type With <: OWL
    binding::Array{Binding}
    body::OWL
end

type Id <: OWL
    name::Symbol
end

type FunDef <: OWL
    formal_parameter::Array{Symbol}
    fun_body::OWL
end

type FunApp <: OWL
    fun_expr::OWL
    arg_expr::Array{OWL}
end

type NumVal <: RetVal
    n::Int64
end

type ClosureVal <: RetVal
    param::Array{Symbol}
    body::OWL
    env::Environment  
end

type mtEnv <: Environment
end

type ArgMapping <: OWL
    name::Symbol
    value::RetVal
end

type CEnvironment <: Environment
    args::Array{ArgMapping}
    parent::Environment
end

#
# ----------------- Helper Functions -----------------
#
function Negative( n::Int64 )
    return 0 - Int64(n)
end

function Divide( x::Int64, y::Int64 )
    if y == 0
        throw(LispError( "cannot divide by zero" ))

    else
        return x / y
    end
end

function collatz( n::Real )
  return collatz_helper( n, 0 )
end

function collatz_helper( n::Real, num_iters::Int )
  if n == 1
    return num_iters
  end
  if mod(n,2)==0
    return collatz_helper( n/2, num_iters+1 )
  else
    return collatz_helper( 3*n+1, num_iters+1 )  
  end
end

#
# ----------------- Operator Table -----------------
#
binFuncs = Dict(
    :+ => +,
    :- => -,
    :/ => Divide,
    :* => *,
    :mod => mod )

unaryFuncs = Dict(
    :collatz => collatz,
    :- => Negative )

#
# ----------------- Parse -----------------
#
function parse( expr::Real )
    return Num( expr )
end

function parse( expr::Symbol )
  return Id( expr )
end
    
function parse( expr::Array{Any} )

    op_symbol = expr[1]

    if (op_symbol == :- && length(expr) == 2) || op_symbol == :collatz
        if length(expr) != 2
            throw( LispError("Invalid parameter length for $op_symbol") )
        end
        return Unaryop( op_symbol, parse(expr[2]) )
    elseif haskey(binFuncs, op_symbol)
        if length(expr) != 3
            throw( LispError("Invalid parameter length for $op_symbol") )
        end
        return Binop( op_symbol, parse(expr[2]), parse(expr[3]) )

    elseif op_symbol == :if0
        if length(expr) != 4
            throw( LispError("Invalid parameter length for $op_symbol") )
        end
        condition = parse( expr[2] )
        zero_branch = parse( expr[3] )
        nonzero_branch = parse( expr[4] )
        return If0( condition, zero_branch, nonzero_branch )

    elseif op_symbol == :with
        if length(expr) != 3
            throw( LispError("Invalid parameter length for $op_symbol") )
        end
        used = Dict()
        binding = Binding[]
        try
            for b_exp in expr[2]
                if haskey( used, b_exp[1] )
                    throw( LispError( "Id has already been defined" ) )
                end
                push!( binding, Binding( b_exp[1], parse(b_exp[2]) ) )
                used[b_exp[1]] = true
            end
        catch e
            throw( LispError("Invalid parameter type") )
        end
        body = parse( expr[3] )
        return With( binding, body )

    elseif op_symbol == :lambda
        if length(expr) != 3
            throw( LispError("Invalid parameter length for $op_symbol") )
        end
        used = Dict()
        for s in expr[2]
            if haskey( used, s )
                throw( LispError("Id already exists") )
            end
            used[s] = true
        end

        if typeof(expr[2]) != Array{Any,1}
            throw( LispError("Expecting Array{Symbol}") )
        end

        return FunDef( expr[2], parse(expr[3]) )
    else
        args = OWL[]
        if length(expr) > 1
            for i in 2:length(expr)
                push!( args, parse(expr[i]) )
            end
        end
        return FunApp( parse(expr[1]), args )
    end
    throw( LispError("Invalid type $op_symbol") )
end

function parse( expr::Any )
  throw( LispError("Invalid type $expr") )
end

#
# ----------------- Calc -----------------
#
function calc( ast::OWL )
  return calc( ast, mtEnv() )
end

function calc( ast::Num, env::Environment )
  return NumVal(ast.n)
end

function calc( ast::Binop, env::Environment )
    left = calc( ast.lhs, env )
    if typeof(left) != NumVal
        throw( LispError( "Expecting NumVal" ) )
    end
    right = calc( ast.rhs, env )
    if typeof(right) != NumVal
        throw( LispError( "Expecting NumVal" ) )
    end
    return NumVal( binFuncs[ast.op](left.n, right.n) )
end

function calc( ast::Unaryop, env::Environment )
    s = calc( ast.s, env )
    if typeof(s) != NumVal
        throw( LispError( "Expecting NumVal" ) )
    end
    return NumVal( unaryFuncs[ast.op](s.n) )
end

function calc( ast::If0, env::Environment )
  cond = calc( ast.condition, env )
  if cond == 0
    return calc( ast.zero_branch, env )
  else
    return calc( ast.nonzero_branch, env )
  end
end

function calc( ast::Array{Binding}, env::Environment )
    args = ArgMapping[]
    used = Dict()
    for bind in ast
        if haskey(used, bind.name)
            throw( LispError( "Id has already been defined" ) )
        end
        val = calc( bind.binding_expr )
        push!( args, ArgMapping(bind.name, val) )
        used[bind.name] = true
    end
    return args
end

function calc( ast::With, env::Environment )
    args = calc( ast.binding, env )
    extended_env = CEnvironment( args, env )
    return calc( ast.body, extended_env )
end

function calc( ast::Id, env::Environment )
    if env == mtEnv()
        throw( LispError( "WARGH! Couldn't find symbol!" ) )
    end
    for e in env.args
        if e.name == ast.name
            return e.value
        end
    end
    return calc( ast, env.parent )
end

function calc( ast::FunDef, env::Environment )
    return ClosureVal( ast.formal_parameter, ast.fun_body, env )
end

function calc( ast::FunApp, env::Environment )

    the_closure = calc( ast.fun_expr, env )

    if typeof( the_closure ) != ClosureVal
        throw( LispError( "Tried to call non-closure!" ) )
    end

    if length(the_closure.param) != length(ast.arg_expr)
        throw( LispError( "Number of parameters is not equal" ) )
    end

    args = ArgMapping[]
    for i in 1:length(ast.arg_expr)
        push!( args, ArgMapping( the_closure.param[i], calc( ast.arg_expr[i], env ) ) )
    end
    new_env = CEnvironment( args, the_closure.env )

    return calc( the_closure.body, new_env )
end

function calc( ast::Array{FunApp}, env::Environment )
    rval = FunApp[]
    for fa in ast
        push!( rval, parse(fa, env) )
    end
    return rval
end

end


