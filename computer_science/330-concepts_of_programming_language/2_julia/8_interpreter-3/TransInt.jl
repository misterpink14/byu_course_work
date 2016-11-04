import Base # For type comparisions

module TransInt

using Error
using Lexer

export parse, analyze, calc, NumVal, ClosureVal

abstract OWL
abstract RetVal
abstract Environment

#
# ----------------- Helper Functions -----------------
#
function Negative( n::Int64 )
    return 0 - Int64(n)
end

function Divide( x::Int64, y::Int64 )
    if y == 0
        throw(LispError( "Cannot divide by zero" ))

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
# ----------------- Reserved -----------------
#
reservedSymbols = Dict(
    :Id => true,
    :Num => true,
    :Unaryop => true,
    :And => true,
    :Plus => true,
    :Binop => true,
    :If0 => true,
    :With => true,
    :FunDef => true,
    :FunApp => true,
    : => true,
    )

#
# ----------------- Types -----------------
#
# OWL
type Id <: OWL
    name::Symbol
end

type Num <: OWL
    n::Int64
end

type Unaryop <: OWL
    op::Symbol
    s::OWL
end

type And <: OWL
    operands::Array{OWL}
end

type Plus <: OWL
    operands::Array{OWL}
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

type With <: OWL
    binding::Dict{Symbol,OWL}
    body::OWL
end

type FunDef <: OWL
    formal_parameter::Array{Symbol}
    fun_body::OWL # with
end

type FunApp <: OWL # Lambda
    fun_expr::OWL
    arg_expr::Array{OWL}
end

# RetVal
type NumVal <: RetVal
    n::Int64
end

type ClosureVal <: RetVal
    param::Array{Symbol}
    body::OWL
    env::Environment  
end

# Environment
type mtEnv <: Environment
end

type CEnvironment <: Environment
    args::Dict{Symbol,RetVal}
    parent::Environment
end

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

    if typeof(expr[1]) == Symbol
        op_symbol = expr[1]

        if haskey( unaryFuncs, op_symbol )
            if length(expr) == 2
                return Unaryop( op_symbol, parse(expr[2]) )
            elseif op_symbol == :- && length(expr) == 3
                return Binop( op_symbol, parse(expr[2]), parse(expr[3]) )
            end

        elseif op_symbol == :+
            if length(expr) > 2
                operands = Array{OWL,1}()
                for i in 2:length(expr)
                    push!( operands, parse(expr[i]) )
                end

                return Plus( operands )
            end

        elseif haskey( binFuncs, op_symbol )
            if length( expr ) == 3
                lhs = parse(expr[2])
                rhs = parse(expr[3])
                return Binop( op_symbol, lhs, rhs )
            end

        elseif op_symbol == :and
            if length( expr ) > 2
                operands = Array{OWL,1}()
                for i in 2:length(expr)
                    push!( operands, parse(expr[i]) )
                end

                return And( operands )
            end

        elseif op_symbol == :if0
            if length( expr ) == 4
                cond = parse( expr[2] )
                z_b  = parse( expr[3] )
                nz_b = parse( expr[4] )
                return If0( cond, z_b, nz_b )
            end

        elseif op_symbol == :with
            if length( expr ) == 3
                binding = Dict{Symbol,OWL}()
                if typeof( expr[2] ) == Array{Any,1}
                    try
                        for bind in expr[2]
                            if haskey( binding, bind[1] )
                                throw( LispError("Cannot redefine binding name") )
                            elseif typeof( bind[1] ) == Symbol
                                binding[bind[1]] = parse( bind[2] )
                            else
                                throw( LispError("Looking for Symbol") )
                            end
                        end
                    catch Error
                        throw( LispError("Invalid parameter type for $op_symbol") )
                    end
                    body = parse( expr[3] )
                    return With( binding, body )
                else
                    throw( LispError("Invalid type for $op_symbol") )
                end
            end

        elseif op_symbol == :lambda
            if length( expr ) == 3 || length( expr ) == 2
                used = Dict()
                if length(expr[2]) > 0
                    for s in expr[2]
                        if haskey( used, s )
                            throw( LispError("Id already exists") )
                        end
                        used[s] = true
                    end
                end

                if typeof(expr[2]) != Array{Any,1}
                    throw( LispError("Expecting Array{Symbol}") )
                end

                return FunDef( expr[2], parse(expr[3]) )
            end
        else
            throw( LispError("Invalid symbol $op_symbol") )
        end

        throw( LispError("Invalid number of expressions for $op_symbol") )
    else
        args = OWL[]
        if length(expr) > 1
            for i in 2:length(expr)
                push!( args, parse(expr[i]) )
            end
        end
        return FunApp( parse(expr[1]), args )

    end
    throw( LispError("Parsing failed") )

end

function parse( expr::Any )
  throw( LispError("Invalid type $expr") )
end

#
# ----------------- Analyze -----------------
#
function analyze( ast::OWL )
    throw( LispError("Unknown node!") )
end

function analyze( ast::Num )
    return ast
end

function analyze( ast::Id )
    return ast
end

function analyze( ast::And )
    if length(ast.operands) == 1
        cond = ast.operands[1]
        return If0( cond, Num( 0 ), Num( 1 ) )
    end

    cond = ast.operands[1]

    nonzero_branch = Array{OWL,1}()
    for i in 2: length( ast.operands )
        push!( nonzero_branch, ast.operands[i] )
    end

    nonzero_branch = And( nonzero_branch )
    return analyze( If0( cond, Num( 0 ), nonzero_branch ) )
end

function analyze( ast::Plus )
    if length(ast.operands) == 2
        lhs = ast.operands[1]
        rhs = ast.operands[2]
        return Binop( :+, lhs, rhs )
    end

    lhs = ast.operands[1]
    operands = Array{OWL,1}()
    for i in 2: length( ast.operands )
        push!( operands, ast.operands[i] )
    end

    rhs = Plus( operands )
    return analyze( Binop( :+, lhs, rhs ) )
end

function analyze( ast::Binop )
    lhs = analyze( ast.lhs )
    rhs = analyze( ast.rhs )

    if typeof(lhs) == Num && typeof(rhs) == Num
        return Num( binFuncs[ast.op](lhs.n, lhs.n) )
    else
        return Binop( ast.op, lhs, rhs )
    end
    
end

function analyze( ast::Unaryop )
    s = analyze( ast.s )

    if typeof(s) == Num
        if ast.op == :collatz && s.n < 0
            throw( LispError( "Number must be Real for collatz to work" ) )
        end
        return Num( unaryFuncs[ast.op](s.n) )
    else
        return Binop( s )
    end
    
end

function analyze( ast::With )
    fd = FunDef( collect( keys( ast.binding ) ), analyze( ast.body ) )

    arg_expr = Array{OWL,1}()
    for bind in ast.binding
        push!( arg_expr,  analyze( bind[2] ) )
    end
    return FunApp( fd, arg_expr)
end

function analyze( ast::FunDef )
    return FunDef( ast.formal_parameter, analyze( ast.fun_body) )
end

function analyze( ast::FunApp )
    f_exp = analyze( ast.fun_expr )
    arg_expr = Array{OWL,1}()
    for arg in ast.arg_expr
        push!( arg_expr, analyze( arg ) )
    end
    return FunApp( f_exp, arg_expr)
end

function analyze( ast::If0 )

    cond = analyze(ast.condition)
    if typeof( cond ) == Num
        if cond.n == 0
            return analyze(ast.zero_branch)
        else
            return analyze(ast.nonzero_branch)            
        end

    else
        return If0( cond, analyze(ast.zero_branch), analyze(ast.nonzero_branch) )
    end
end

#
# ----------------- Calc -----------------
#
function calc( ast::OWL )
  return calc( ast, mtEnv() )
end

function calc( ast::Num, env::Environment )
  return NumVal( ast.n )
end

function calc( ast::Binop, env::Environment )
    left = calc( ast.lhs, env )
    if typeof( left ) != NumVal
        throw( LispError( "Expecting NumVal" ) )
    end

    right = calc( ast.rhs, env )
    if typeof( right ) != NumVal
        throw( LispError( "Expecting NumVal" ) )
    end

    return NumVal( binFuncs[ast.op](left.n, right.n) )
end

function calc( ast::Unaryop, env::Environment )
    s = calc( ast.s, env )
    if typeof( s ) != NumVal
        throw( LispError( "Expecting NumVal" ) )
    end
    if ast.op == :collatz && s.n < 0
        throw( LispError( "Number must be Real for collatz to work" ) )
    end

    return NumVal( unaryFuncs[ast.op](s.n) )
end

function calc( ast::If0, env::Environment )
    cond = calc( ast.condition, env )
    if cond.n == 0
        return calc( ast.zero_branch, env )
    else
        return calc( ast.nonzero_branch, env )
    end
end

function calc( ast::Id, env::Environment )
    if env != mtEnv() && haskey( env.args, ast.name )
       return env.args[ast.name]
    else
        throw( LispError("WARGH! Couldn't find symbol!") )
    end
end

function calc( ast::With, env::Environment )

    throw( LispError("YOU SHOULDN'T BE IN calc WITH!") )

    args = Dict{Symbol,RetVal}()
    for name in ast.binding
        args[name[1]] = calc( name[2], env )
    end

    extended_env = CEnvironment( args, env )
    return calc( ast.body, extended_env )
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

    args = Dict{Symbol, RetVal}()
    for i in 1:length(ast.arg_expr)
        key = the_closure.param[i]
        val = calc( ast.arg_expr[i], env)
        args[key] = val
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










# macro tnum()
#        return :(testnum += 1)
# end
# using Lexer
# using Error

# testnum = 0
# function testNum(num)
#   return string(num) * ". "
# end

# function parseT(str)
#   TransInt.parse(Lexer.lex(str))
# end

# function analyze(str)
#   TransInt.analyze(parseT(str))
# end

# function interpret(str)
#   TransInt.calc(analyze(str))
# end

# function removeNL(str)
#   replace(string(str), "\n", "")
# end

# function testErr(f, param, num)
#   try
#     println(testNum(num) *  removeNL(f(param)))
#   catch Y
#     if (typeof(Y) != Error.LispError)
#       println(testNum(num) * removeNL(Y))
#     else
#       println(testNum(num) * "Error")
#     end
#   end
# end

# function testPass(f, param, num)
#   try
#     f(param)
#     println(testNum(num) * "Pass")
#   catch Y
#     println(testNum(num) * removeNL(Y))
#   end
# end

# function testAns(f, param, num)
#   try
#     println(testNum(num) *  removeNL(f(param)))
#   catch Y
#     println(testNum(num) * removeNL(Y))
#   end
# end

# function testContains(f, param, reg, num)
#   try
#     answer = string(ismatch(reg, removeNL(f(param))))
#     println(testNum(num) * answer)
#   catch Y
#     println(testNum(num) * removeNL(Y))
#   end
# end



# testPass(parseT, "(+ 1 2 3 4 5)", @tnum())
# testContains(analyze, "(+ 1 2 3 4 5)", r"Binop", @tnum())
# testAns(interpret, "(+ 1 2 3 4 5)", @tnum())
# testAns(interpret, "(and (+ 4 0) (- 3 3) (* 4 3))", @tnum())


# testPass(parseT, "(and 1 2 3 3)", @tnum())
# testPass(parseT, "(and (and 1 2) a)", @tnum())
# testPass(parseT, "(+ 1 2 3 4)", @tnum())
# testPass(parseT, "(+ (+ 1 2 3) 2)", @tnum())

# testContains(analyze, "(with ((x 1)) x)", r"with", @tnum())
# testContains(analyze, "(and 1 2 3)", r"And", @tnum())

# testAns(interpret, "(and 1 2)", @tnum())
# testAns(interpret, "(+ 1 2 3)", @tnum())
# testAns(interpret, "(* (and 1 2 3) (+ 1 2 3))", @tnum())