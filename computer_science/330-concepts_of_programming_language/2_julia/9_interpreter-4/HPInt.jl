import Base # For type comparisions

module TransInt

using Error
using Lexer
using Images
using Cairo

export parse, analyze, calc, NumVal, ClosureVal, MatrixVal

abstract OWL
abstract RetVal
abstract Environment

#
# ----------------- File Functions -----------------
#
function simple_load( img_path::AbstractString )
  im = Images.load( img_path );
  tmp = Images.separate(im);
  d = Images.data( tmp );
  d = d[:,:,1];  # just the r channel
  d = convert( Array{Float32,2}, d );
  return d
end

function simple_save( output::Array, img_path::AbstractString )
    output[ output .> 1.0 ] = 1.0
    output[ output .< 0.0 ] = 0.0
    tmpc = convert( Array{UInt32,2}, floor(output*255.0) )
    tmp_output =  tmpc + tmpc*256 + tmpc*65536 + 0xff000000
    c2 = CairoImageSurface( transpose(tmp_output), Cairo.FORMAT_ARGB32 )
    write_to_png( c2, img_path )
    return 42
end

#-------------------------------------------------------------

function render_text( text_str::AbstractString, xpos, ypos )

  data = Matrix{UInt32}( 256, 256 );
  c = CairoImageSurface( data, Cairo.FORMAT_ARGB32 );
  cr = CairoContext( c );

  set_source_rgb( cr, 1., 1., 1. );
  rectangle( cr, 0., 0., 256., 256. );
  fill( cr );

  set_source_rgb( cr, 0, 0, 0 );
  select_font_face( cr, "Sans", Cairo.FONT_SLANT_NORMAL,
                    Cairo.FONT_WEIGHT_BOLD );
  set_font_size( cr, 90.0 );

  move_to( cr, xpos, ypos );
  show_text( cr, text_str );

  # tmp is an Array{UInt32,2}
  tmp = cr.surface.data;

  # grab just the blue channel, and convert the array to an array of floats
  tmp2 = convert( Array{Float32,2}, tmp & 0x000000ff ) / 255.0;
  tmp2 = convert( Array{Float32,2}, tmp2 );

  return tmp2
end

#-------------------------------------------------------------

function emboss( img::Array )
  f = [ -2. -1. 0.
        -1.  1. 1.
         0.  1. 1. ];
  f = convert( Array{Float32,2}, f );

  es = conv2( f, img );
  es = es[1:256,1:256];
  return es    
end

#-------------------------------------------------------------

function drop_shadow( img::Array )
  foo = convert( Array{Float32,2}, gaussian2d(5.0,[25,25]) );
  foo = foo / maximum(foo);
  ds = conv2( foo, img );
  ds = ds[13:256+12,13:256+12];
  ds = ds / sum(foo);
  return ds
end

#-------------------------------------------------------------

# assumes img is black-on-white
function inner_shadow( img::Array )
  foo = convert( Array{Float32,2}, gaussian2d(5.0,[25,25]) );
  foo = foo / maximum(foo);
  is = conv2( foo, 1.0-img );
  is = is[8:251+12,8:251+12];
  is = is / sum(foo);
  is = max( is, img );
  return is
end

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
    :mod => mod,
    :min => min,
    :max => max )

matrixFuncs = Dict(
    :* => .*,
    :/ => ./ )

unaryFuncs = Dict(
    :collatz => collatz,
    :- => Negative )

imgFuncs = Dict(
    :emboss => emboss,
    :drop_shadow => drop_shadow,
    :inner_shadow => inner_shadow )

#
# ----------------- Reserved ----------------- <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<=============
#
reservedSymbols = Dict(
    :+ => true,
    :- => true,
    :* => true,
    :/ => true,
    :mod => true,
    :collatz => true,
    :if0 => true,
    :with => true,
    :lambda => true,
    :and => true,
    :OWL => true,
    :simple_load => true,
    :simple_save => true,
    :render_text => true,
    :emboss => true,
    :drop_shadow => true,
    :inner_shadow => true,
    :min => true,
    :max => true )

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

type RenderText <: OWL
    s::AbstractString
    x::OWL
    y::OWL
end

type ImageManip <: OWL
    f::Symbol # for emboss, drop_shadow, inner_shadow
    img::OWL
end

type SimpleLoad <: OWL
    path::AbstractString
end

type SimpleSave <: OWL
    output::OWL
    path::AbstractString
end

type MyMatrix <: OWL
    n::Array{Float32,2}
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

type MatrixVal <: RetVal
    n::Array{Float32,2}
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

function parse( expr::Array{Float32,2} )
    println("MyMatrix")
    return MyMatrix( expr )
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
                                if haskey( reservedSymbols, bind[1] )
                                    throw( LispError("Symbol is reserved") )
                                end
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
                        if haskey( reservedSymbols, s )
                            throw( LispError("Symbol is reserved") )
                        end
                        used[s] = true
                    end
                end

                if typeof(expr[2]) != Array{Any,1}
                    throw( LispError("Expecting Array{Symbol}") )
                end

                return FunDef( expr[2], parse(expr[3]) )
            end
        elseif op_symbol == :render_text
            if length(expr) == 4
                if !(typeof(expr[2]) <: AbstractString)
                    throw( LispError("Invalid type for $op_symbol") )
                end
                return RenderText( expr[2], parse( expr[3] ), parse( expr[4] ) )
            end
        elseif op_symbol == :emboss || op_symbol == :drop_shadow || op_symbol == :inner_shadow
            if length(expr) == 2
                return ImageManip( op_symbol, parse( expr[2] ) )
            end
        elseif op_symbol == :simple_load
            if length(expr) == 2
                if !(typeof(expr[2]) <: AbstractString)
                    throw( LispError("Invalid type for $op_symbol") )
                end
                return SimpleLoad( expr[2] )
            end
        elseif op_symbol == :simple_save
            if length(expr) == 3
                if !(typeof(expr[3]) <: AbstractString)
                    throw( LispError("Invalid type for $op_symbol") )
                end
                return SimpleSave( parse(expr[2]), expr[3] )
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

function analyze( ast::MyMatrix )
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
        lhs = analyze( ast.operands[1] )
        rhs = analyze( ast.operands[2] )
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

    if (typeof(lhs) == Num || typeof(lhs) == MyMatrix) && (typeof(rhs) == Num || typeof(rhs) == MyMatrix)
        return Num( binFuncs[ast.op](lhs.n, rhs.n) )
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

function analyze( ast::RenderText )
    return RenderText( ast.s, analyze( ast.x ), analyze( ast.y ) )
end

function analyze( ast::ImageManip )
    return ImageManip( ast.f, analyze( ast.img ) )
end

function analyze( ast::SimpleLoad )
    return ast
end

function analyze( ast::SimpleSave )
    return SimpleSave( analyze(ast.output), ast.path )
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

function calc( ast::Array{Float32,2}, env::Environment )
  return MatrixVal( ast )
end

function calc( ast::MyMatrix, env::Environment )
  return MatrixVal( ast.n )
end

function calc( ast::MatrixVal, env::Environment )
  return ast
end

function calc( ast::Binop, env::Environment )
    sleft = @spawn calc( ast.lhs, env )
    sright = @spawn calc( ast.rhs, env )

    left = fetch(sleft)
    right = fetch(sright)

    if typeof( left ) != NumVal && typeof( left ) != MatrixVal
        throw( LispError( "Expecting NumVal" ) )
    end
    if typeof( right ) != NumVal && typeof( right ) != MatrixVal
        throw( LispError( "Expecting NumVal" ) )
    end

    if typeof(left) == MatrixVal && typeof(right) == MatrixVal && (ast.op == :* || ast.op == :/)
        return MatrixVal( matrixFuncs[ast.op](left.n, right.n) )
    elseif typeof(left) == NumVal && typeof(right) == NumVal
        return NumVal( binFuncs[ast.op](left.n, right.n) )
    else
        if ast.op == :/
            return MatrixVal( left.n / right.n)
        else
            return MatrixVal( binFuncs[ast.op](left.n, right.n) )
        end
    end
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
        if typeof(env.parent) == mtEnv
            throw( LispError("WARGH! Couldn't find symbol!") )
        end
        return calc( ast, env.parent )
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
        push!( rval, calc(fa, env) )
    end
    return rval
end

function calc( ast::RenderText, env::Environment )
    sx = @spawn calc(ast.x, env)
    sy = @spawn calc(ast.y, env)

    x = fetch(sx)
    y = fetch(sy)
    
    if typeof(x) != NumVal || typeof(y) != NumVal
        throw( LispError("Expected Numval for RenderText") )
    end

    return calc( render_text( ast.s, x.n, y.n ), env )
end

function calc( ast::ImageManip, env::Environment )
    img = calc( ast.img, env )
    if typeof(img) != MatrixVal
        throw( LispError( "Expected a MatrixVal for an ImageManip" ) )
    end
    return calc( imgFuncs[ast.f](img.n), env )
end

function calc( ast::SimpleLoad, env::Environment )
    return calc( simple_load(ast.path), env )
end

function calc( ast::SimpleSave, env::Environment )
    img = calc(ast.output, env)
    if typeof(img) != MatrixVal
        throw( LispError( "Expected a MatrixVal for an SimpleSave" ) )
    end
    return NumVal( simple_save( img.n, ast.path ))
end

end
