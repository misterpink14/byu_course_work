module RudInt
using Error
using Lexer

#
# ----------------- OWL Lang -----------------
#
abstract OWL
 
type Num <: OWL
    n::Real
end

type Unaryop <: OWL
    op::Function
    s::OWL
end
 
type Binop <: OWL
    op::Function
    lhs::OWL
    rhs::OWL
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

function parse( expr::Array{Any} )
    op_symb = expr[1]

    try
        func = binFuncs[op_symb]

        if length(expr) == 3
            return Binop( func, parse(expr[2]), parse(expr[3]) )

        elseif op_symb == :-
            throw( LispError( "invalid operator $op_symb" ) )
        end
    catch error
        t = typeof(error)

        try
            func = unaryFuncs[op_symb]
            if length(expr) == 2
                return Unaryop( func, parse(expr[2]) )
            end
        catch error
            if isa(error, KeyError)
                throw( LispError( "invalid operator $op_symb" ) )
            end
        end
    end
    l = length(expr)
    throw(LispError( "invalid parameter count $l for $op_symb" ))
end

#
# ----------------- Calc -----------------
#
function calc( owl::Num )
  return owl.n
end

function calc( owl::Unaryop )
    return owl.op( calc(owl.s) )
end

function calc( owl::Binop )
    return owl.op( calc(owl.lhs), calc(owl.rhs) )
end

end