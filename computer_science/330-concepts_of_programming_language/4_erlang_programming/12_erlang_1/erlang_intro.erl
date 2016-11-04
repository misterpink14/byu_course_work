-module(erlang_intro).
-export([fib/1, area/2, sqrList/1, calcTotals/1, map/2, quickSortServer/0]).
-import(math, [pi/0]).
-import(random, [uniform/1]).
-import(lists, [nth/2]).

% --------------------------------------
fib(0) ->
    0;
fib(1) ->
    1;
fib(2) ->
    1;
fib(N) -> 
    fib(N-1) + fib(N-2).

% --------------------------------------
area(rectangle, ShapeInfo) ->
    {Length, Width} = ShapeInfo,
    Length * Width;
area(square, ShapeInfo) ->
    {Length} = ShapeInfo,
    Length * Length;
area(circle, ShapeInfo) ->
    {Diameter} = ShapeInfo,
    pi() * (Diameter / 2) * (Diameter / 2);
area(triangle, ShapeInfo) ->
    {Base, Height} = ShapeInfo,
    (Base * Height) / 2.

% --------------------------------------
sqrList(List) ->
    [X * X || X <- List].

% --------------------------------------
calcTotals(List) ->
    [{I, Q * P} || {I, Q, P} <- List].

% --------------------------------------
map(Function, List) ->
    [Function(X) || X <- List].

% --------------------------------------
quickSortServer() ->
    receive
        "casa" -> 
            io:format("house~n"), 
            loop();
        
        "blanca" -> 
            io:format("white~n"), 
            loop();
        
        _ -> 
            io:format("I don't understand.~n"), 
            loop()
    end.

% USAGE:
% c(erlang_intro). 