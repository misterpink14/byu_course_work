-module(subdb_supervisor).
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

    UserOrderChild = {user_order_supervisor, {user_order_supervisor, start_link, [Env]},
                   Restart, Shutdown, supervisor, [user_order_supervisor]},
    InfoChild = {info, {info, start_link, [Env]},
                   Restart, Shutdown, worker, [info]},
    ShipperChild = {shipper, {shipper, start_link, [Env]},
                   Restart, Shutdown, worker, [shipper]},

    {ok, {SupFlags, [InfoChild, ShipperChild, UserOrderChild]}}.