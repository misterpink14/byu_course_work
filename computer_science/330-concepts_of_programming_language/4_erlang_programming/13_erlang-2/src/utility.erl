-module(utility).

-export([fail/1]).

fail(Chance) ->
  R = random:uniform(Chance),
  if
    R == 2 ->
      true;
    true ->
      false
  end.
