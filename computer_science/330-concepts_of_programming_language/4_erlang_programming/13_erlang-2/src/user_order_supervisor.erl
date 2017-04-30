-module(user_order_supervisor).
-behaviour(supervisor).

-export([start_link/1, init/1]).

start_link(Env) ->
    supervisor:start_link(?MODULE, Env).

init(Env) ->
    RestartStrategy = one_for_one,
    MaxRestarts = 10,
    MaxSecondsBetweenRestarts = 10,

    SupFlags = {RestartStrategy,
                MaxRestarts,
                MaxSecondsBetweenRestarts},

    Restart = permanent,
    Shutdown = 2000,
    Type = worker,

    UserChild = {user, {user, start_link, [Env]},
                   Restart, Shutdown, Type, [user]},
    OrderChild = {order, {order, start_link, [Env]},
                   Restart, Shutdown, Type, [order]},

    {ok, {SupFlags, [UserChild, OrderChild]}}.