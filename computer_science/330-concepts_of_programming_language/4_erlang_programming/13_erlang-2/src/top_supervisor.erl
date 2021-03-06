% I ONLY DID PART 1
-module(top_supervisor).
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

    DbChild = {db_supervisor, {db_supervisor, start_link, [Env]},
                   Restart, Shutdown, supervisor, [db_supervisor]},
    CSChild = {custservice, {custservice, start_link, [Env]},
                   Restart, Shutdown, worker, [custservice]},

    {ok, {SupFlags, [CSChild, DbChild]}}.