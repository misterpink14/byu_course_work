-module(info).
%%% The info module is used to get information about products. It will return a
%%% List of all products, and furhter information about a product. It relies on
%%% the database being active.
-behavior(gen_server).

-export([start_link/1, get_items/1, get_info/2]).

-export([init/1, handle_call/3, handle_cast/2,
          handle_info/2, code_change/3, terminate/2]).


-include("defines.hrl").

%% starts an info server
start_link(NameServer) ->
  gen_server:start_link(?MODULE, NameServer, []).


%% returns a list of items
get_items(Info) ->
  gen_server:call(Info, getItems).

%% returns a info about the items.
get_info(Info, Item) ->
  gen_server:call(Info, {getInfo, Item}).



%%Gen Server Functions
init(NameServer) ->
  io:fwrite("Info Started~n"),
  name_server:register(NameServer, ?INFOMOD, self()),
  self() ! {start, NameServer},
%  process_flag(trap_exit, true),
  {ok, []}.

handle_call(getItems, _From, Db) ->
  case utility:fail(?CHANCE) of
    true ->
      {stop, "ERROR", {error, moduleDown}, Db};
    false ->
      {reply, database:get_items(Db), Db}
  end;

handle_call({getInfo, Item}, _From, Db) ->
  case utility:fail(?CHANCE) of
    true ->
      {stop, "ERROR",{error, moduleDown}, Db};
    false ->
      {reply, database:get_item_info(Db, Item), Db}
  end.

handle_cast(_, State) ->
    {stop, "ERROR", State}.

handle_info({start, NameServer}, _State) ->
  timer:sleep(500),
  Pid = name_server:resolve_with_fail(NameServer, ?DBMOD),
  {noreply, Pid};

handle_info(_, State) ->
  {stop, "ERROR",{error, moduleDown}, State}.

code_change(_OldVsn, State, _Extra) ->
  {ok, State}.

terminate(_Reason, _) ->
  {ok, error}.
