-module(custservice).
%%%The customer service module ignores all requests sent to it and returns a
%%% message indicating everyone is busy.
-behavior(gen_server).

-export([start_link/1, place_request/2]).
-export([init/1, handle_call/3, handle_cast/2,
          handle_info/2, code_change/3, terminate/2]).

-include("defines.hrl").

%%Starts the customer service server.
%%NameServer, is the Name space server this module uses to register itself
start_link(NameServer) ->
  gen_server:start_link(?MODULE, NameServer,[]).

%%takes an cust service server, and a message and places a cust service request
place_request(Server, Msg) ->
  gen_server:call(Server, {placeRequest, Msg}).


% gen_server functions
init(NameServer) ->
  io:fwrite("Customer Service started ~n"),
  gen_server:cast(NameServer, {register, ?CUSTMOD, self()}),
%  process_flag(trap_exit, true),
  {ok, []}.

handle_call({placeRequest, _Msg}, _From, State) ->
  R = random:uniform(?CHANCE),
  if
    R == 2 ->
      {stop, "ERROR", {error, moduleDown}, State};
    true ->
      {reply, "All Customer Service agents are busy, Sorry,", State}
  end.

handle_cast(_, State) ->
  {stop,"ERROR", State}.

handle_info(_, State) ->
  {stop, "ERROR", State}.

code_change(_OldVsn, State, _Extra) ->
  {ok, State}.

terminate(_Reason, _) ->
  {ok, error}.
