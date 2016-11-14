-module(order).
-behavior(gen_server).

-export([start_link/1, place_order/4, get_status/2, get_item_name/2]).
-export([init/1, handle_call/3, handle_cast/2,
          handle_info/2, code_change/3, terminate/2]).


-include("defines.hrl").

%%starts an order server returns {ok, Pid}.
start_link(NameServer) ->
  gen_server:start_link(?MODULE, NameServer, []).

%% Places an order for the user, returns true if order placement is sucessfull.
place_order(OrderServer, UserName, Item, Quantity) ->
  gen_server:call(OrderServer, {placeOrder, UserName, Item, Quantity}).

%% Retrieves shipping status of an order.
get_status(OrderServer, OrderNum) ->
  gen_server:call(OrderServer, {checkStatus, OrderNum}).

%%Retrieves the Name of the order.
get_item_name(OrderServer, OrderNum) ->
  gen_server:call(OrderServer, {getItem, OrderNum}).

%%gen_server functions
init(NameServer) ->
  io:fwrite("Order Started~n"),
  name_server:register(NameServer, ?ORDERMOD, self()),
  self() ! {start, NameServer},
  %process_flag(trap_exit, true),
  {ok, {[], []}}.

handle_call({placeOrder, UserName, ItemName, Quant}, _From, {UserNode, Db}) ->
  case utility:fail(?CHANCE) of
    true ->
      {stop, "ERROR",{error, moduleDown}, {UserNode, Db}};
    false ->
      case user:is_logged_in(UserNode, UserName) of
        true ->
          case database:create_order(Db, UserName, ItemName, Quant) of
            {error, Reason} ->
              {reply, {error, Reason}, {UserNode, Db}};
            true ->
              {reply, true, {UserNode, Db} }
          end;
        false ->
          {reply, {error, "User Not logged in"}, {UserNode, Db}}
      end
  end;

handle_call({checkStatus, OrderNum}, _From, {_UserNode, Db}) ->
  case utility:fail(?CHANCE) of
    true ->
      {stop, "ERROR", false, {_UserNode, Db}};
    false ->
      {_,_,_,_,Status} = database:get_order(Db, OrderNum),
      {reply, Status, {_UserNode, Db}}
    end;

handle_call({getItem, OrderNum}, _From, {_UserNode, Db}) ->
  case utility:fail(?CHANCE) of
    true ->
      {stop, "ERROR", false, {_UserNode, Db}};
    false ->
      {_,ItemName,_,_,_} = database:get_order(Db, OrderNum),
      {reply, ItemName, {_UserNode, Db}}
    end.

handle_cast(_, State) ->
  {stop, "Error", State}.


handle_info({start, NameServer}, _State) ->
  timer:sleep(500),
  Db = name_server:resolve_with_fail(NameServer, ?DBMOD),
  User = name_server:resolve_with_fail(NameServer, ?USERMOD),
  {noreply, {User, Db}};

handle_info(_, State) ->
  {stop, "ERROR", State}.

code_change(_OldVsn, State, _Extra) ->
  {ok, State}.

terminate(_, _) ->
  {ok, error}.
