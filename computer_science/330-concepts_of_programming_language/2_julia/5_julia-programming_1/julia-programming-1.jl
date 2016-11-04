# filename: julia-programming-1.jl

# -------------------- SHAPE -------------------- #

abstract Shape
 
type Position
  x::Real
  y::Real
end
 
type Circ <: Shape
  center::Position
  radius::Real
end
 
type Square <: Shape
  upper_left::Position
  length::Real
end
 
type Rect <: Shape
  upper_left::Position
  width::Real
  height::Real
end

# -------------------- FUNCTIONS -------------------- #

function area( shape::Circ )
    return pi * shape.radius * shape.radius
end

function area( shape::Square )
    return shape.length * shape.length
end

function area( shape::Rect )
    return shape.width * shape.height
end


function in_shape(sh::Circ, pos::Position)
    return ((pos.x - sh.center.x) * (pos.x - sh.center.x) + (pos.y - sh.center.y) * (pos.y - sh.center.y)) <= (sh.radius * sh.radius)
end

function in_shape(sh::Square, pos::Position)
    if sh.upper_left.x > pos.x
        return false
    end
    if sh.upper_left.y > pos.y
        return false
    end
    if sh.upper_left.x + sh.length < pos.x
        return false
    end
    if sh.upper_left.y + sh.length < pos.y
        return false
    end
    return true
end

function in_shape(sh::Rect, pos::Position)
    if sh.upper_left.x > pos.x
        return false
    end
    if sh.upper_left.y > pos.y
        return false
    end
    if sh.upper_left.x + sh.width < pos.x
        return false
    end
    if sh.upper_left.y + sh.height < pos.y
        return false
    end
    return true
end

# println(area( Circ( Position(1,2), 10 )))
# println(area( Square( Position(1,2), 10 )))
# println(area( Rect( Position(1,2), 10, 20 )))

# println(in_shape(Circ( Position(1,2), 10 ), Position(2,3)))
# println(in_shape(Square( Position(1,2), 10 ), Position(2,3)))
# println(in_shape(Rect( Position(1,2), 10, 20), Position(2,3)))

# -------------------- PIXEL -------------------- #

type Pixel
  r::Real
  b::Real
  g::Real
end

# -------------------- FUNCTIONS -------------------- #

function greyscale(pict::Array{Pixel,2})
    return map(x -> Pixel((x.r + x.b + x.g) / 3, (x.r + x.b + x.g) / 3, (x.r + x.b + x.g) / 3), pict)
end


function invert(picture::Array{Pixel,2})
    return map(x -> Pixel(255 - x.r, 255 - x.b, 255 - x.g), picture)
end

# -------------------- TREEITEM -------------------- #

abstract TreeItem
 
type Person <: TreeItem
  name::AbstractString
  birthyear::Integer
  eyecolor::Symbol
  father::TreeItem
  mother::TreeItem
end
 
type Unknown <: TreeItem
end

# -------------------- FUNCTIONS -------------------- #

function count_persons(tree)
    count = 0
    if typeof(tree) == Person
        count = count + count_persons(tree.father)
        count = count + count_persons(tree.mother)
    else
        return 0
    end
    return count + 1
end

function count_age(tree)
    count = 0
    if typeof(tree) == Person
        count = count + count_age(tree.father)
        count = count + count_age(tree.mother)
    else
        return 0
    end
    return count + 2016 - tree.birthyear
end

function average_age(tree)
    return count_age(tree) / count_persons(tree)
end

function tree_map(f, tree)
    if typeof(tree) == Person
        t = Person(tree.name, tree.birthyear, tree.eyecolor, tree.father, tree.mother)
        t.father = tree_map(f, t.father)
        t.mother = tree_map(f, t.mother)
        return f(t)
    else
        return Unknown()
    end
end

function add_last_name(name::AbstractString, tree)
    return tree_map(x -> Person(x.name * name, x.birthyear, x.eyecolor, x.father, x.mother), tree)
end

function eye_colors(tree)
    l = []
    if typeof(tree) == Person
        append!(l, [tree.eyecolor])
        append!(l, eye_colors(tree.father))
        append!(l, eye_colors(tree.mother))
    else
        return []
    end
    return l
end

# println(count_persons(Person("Ben", 2016, :red, Person("John", 2014, :orange, Unknown(), Unknown()), Unknown())))
# println(count_age(Person("Ben", 2016, :red, Person("John", 2014, :orange, Unknown(), Unknown()), Unknown())))
# println(average_age(Person("Ben", 2016, :red, Person("John", 2014, :orange, Unknown(), Unknown()), Unknown())))
# println(tree_map(x -> Person("Joe", x.birthyear, x.eyecolor, x.father, x.mother), Person("Ben", 2016, :red, Person("John", 2014, :orange, Unknown(), Unknown()), Unknown())))
# println(add_last_name("Thompson", Person("Ben", 2016, :red, Person("John", 2014, :orange, Unknown(), Unknown()), Unknown())))
# println(eye_colors(Person("Ben", 2016, :red, Person("John", 2014, :orange, Unknown(), Unknown()), Unknown())))