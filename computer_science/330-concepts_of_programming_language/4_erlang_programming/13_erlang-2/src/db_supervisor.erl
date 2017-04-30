-module(db_supervisor).
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

    SubChild = {subdb_supervisor, {subdb_supervisor, start_link, [Env]},
                   Restart, Shutdown, supervisor, [subdb_supervisor]},
    DbChild = {database, {database, start_link, [Env]},
                   Restart, Shutdown, worker, [database]},

    {ok, {SupFlags, [DbChild, SubChild]}}.