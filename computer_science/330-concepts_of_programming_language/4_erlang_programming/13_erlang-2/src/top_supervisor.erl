-module(top_supervisor).
-behaviour(supervisor).

-export([start_link/1, init/1]).

start_link(Env) ->
    supervisor:start_link(?MODULE, [Env]).

init(Env) ->
    RestartStrategy = rest_for_one,
    MaxRestarts = 10,
    MaxSecondsBetweenRestarts = 10,

    SupFlags = {RestartStrategy,
                MaxRestarts,
                MaxSecondsBetweenRestarts},

    Restart = permanent,
    Shutdown = 2000,
    Type = worker,

    DCSupChild = {datacenter_sup, {datacenter_sup, start_link, [Env]},
                   Restart, Shutdown, Type, [datacenter_sup]},
    DBChild = {database, {database, start_link, [Env]},
                   Restart, Shutdown, Type, [database]},

    {ok, {SupFlags, [DCSupChild, DBChild]}}.