-module(database).
%%% the database manages all the tables. There are three tables, Users, Orders,
%%% and Items. With the format:
%%Item Table
%%%{Name, Description, Price, InStock}

%%User TableName
%%%{UserName, Password, Orders[]}

%%Orders Table
%%%{OrderNum, ItemName, UserName, Quantit, Status(Ordered, shipped, completed)}
-behavior(gen_server).

-export([start_link/1, get_item_info/2, get_items/1,
          is_valid_user/3, add_user/3, get_user_orders/2,
          create_order/4, get_orders/1, get_order/2, add_stock/3,
           add_order_to_user/3,update_order_status/3 ]).

-export([init/1, handle_call/3, handle_cast/2,
          handle_info/2, code_change/3, terminate/2]).

-include("defines.hrl").

%%starts a db node.
start_link(NameServer) ->
  gen_server:start_link(?MODULE, NameServer, []).

%% returns information about the item
get_item_info(Db, Item) ->
  gen_server:call(Db, {info, Item}).

%% returns a list of all items.
get_items(Db) ->
  gen_server:call(Db, {getItems}).

%% returns a boolean indicating if the credentials are valid.
is_valid_user(Db, UserName, Password) ->
  gen_server:call(Db, {logon, UserName, Password}).

%%Creates a new User.
add_user(Db, UserName, Password) ->
  gen_server:call(Db, {newUser, UserName, Password}).

%%Returns a list of all the users orders.
get_user_orders(Db, UserName) ->
  gen_server:call(Db, {getUserOrders, UserName}).

%%Creates a new order and adds it to the order DB.
create_order(Db, UserName, Item, Amount) ->
  gen_server:call(Db, {placeOrder, UserName, Item, Amount}).

%%returns all ordres.
get_orders(Db) ->
  gen_server:call(Db, {getOrders}).

%Returns the order givne by the specified orderNumber.
get_order(Db, OrderNum) ->
  gen_server:call(Db, {getOrder, OrderNum}).

%% adds Amount the quanity of that item.
add_stock(Db, Item, Amount) ->
  gen_server:cast(Db, {addStock, Item, Amount}).

%% attaches an order id to the given user.
add_order_to_user(Db, UserName, OrderNum) ->
  gen_server:cast(Db, {addOrder, UserName, OrderNum}).

%%changes the orders status to the one given.
update_order_status(Db, OrderNum, NewStatus) ->
  gen_server:cast(Db, {updateOrder, OrderNum, NewStatus}).



init(NameServer) ->
  io:fwrite("Database Started~n"),
  name_server:register(NameServer, ?DBMOD, self()),
  {ok, ItemT} = ets:file2tab("itemDb"),
  {ok, UserT} = ets:file2tab("userDb"),
  {ok, OrdersT} = ets:file2tab("orderDb"),
  [ {_, _, _, N, _} |_] = ets:lookup(OrdersT, -1),
%  process_flag(trap_exit, true),
  {ok, {ItemT, UserT, {OrdersT,N}}}.



%%Item
handle_call({info, ID}, _From, {ItemT, UserT, OrdersT}) ->
  [Reply| _Rest] = ets:lookup(ItemT, ID),
  failCall(?CHANCE, Reply, {ItemT, UserT, OrdersT});


handle_call({getItems}, _From, {ItemT, UserT, OrdersT}) ->
  Reply = keys(ItemT),
  failCall(?CHANCE, Reply, {ItemT, UserT, OrdersT});



%%User
handle_call({logon, UserName, Password}, _ , {ItemT, UserT, OrdersT}) ->
  case ets:match(UserT,{UserName, Password, '_'}) of
    [] ->
      failCall(?CHANCE, false, {ItemT, UserT, OrdersT});
    _Else ->
      failCall(?CHANCE, true, {ItemT, UserT, OrdersT})
    end;

handle_call({newUser, UserName, Password}, _, {ItemT, UserT, OrdersT}) ->
  case ets:match(UserT, {UserName, Password, '_'}) of
    [] ->
      case utility:fail(?CHANCE) of
        true ->
          {stop, "ERROR", {error, moduleDown}, {ItemT, UserT, OrdersT}};
        false ->
          ets:insert(UserT, {UserName, Password,[]}),
          {reply, true, {ItemT, UserT, OrdersT}}
        end;
    _Else ->
      failCall(?CHANCE, {error, "User Exists"}, {ItemT, UserT, OrdersT})
    end;

handle_call({getUserOrders, UserName}, _, {ItemT, UserT, OrdersT}) ->
  [{_, _, Orders}] = ets:lookup(UserT, UserName),
  failCall(?CHANCE, Orders, {ItemT, UserT, OrdersT});

%%Order
handle_call({placeOrder, UserName, ItemName, Quantity}, _From, {ItemT, UserT, {OrderT, NextNum}}) ->
  [{N, D, P, InStock}] = ets:lookup(ItemT, ItemName),
%%%{UserName, Password, Orders[]}
  [{_, Pass, User_Orders}] = ets:lookup(UserT, UserName),
  if
    InStock < Quantity ->
      {reply, {error, "Not enough Items in stock"}, {ItemT, UserT, {OrderT, NextNum}}};
    true ->
      case utility:fail(?CHANCE) of
        true ->
          {stop, "ERROR", {error, moduleDown}, {ItemT, UserT, {OrderT, NextNum}}};
        false ->
          ets:insert(OrderT, {NextNum, ItemName, UserName, Quantity, ordered}),
          ets:insert(ItemT, {N,D,P, InStock - Quantity}),
          ets:insert(UserT, {UserName, Pass, [NextNum| User_Orders]}),
          {reply, true, {ItemT, UserT, {OrderT, NextNum + 1}}}
      end
  end;

handle_call({getOrders}, _From, {Item, UserT, {OrderT, NextNum}}) ->
  Return = ets:tab2list(OrderT),
  failCall(?CHANCE, Return, {Item, UserT, {OrderT, NextNum}});

handle_call({getOrder, OrderNum}, _From, {Item, UserT, {OrderT, NextNum}}) ->
  [Order] = ets:lookup(OrderT, OrderNum),
  failCall(?CHANCE, Order, {Item, UserT, {OrderT, NextNum}}).


%%     CASTS
%Item
handle_cast({addStock, ItemName, Quantity}, {ItemT, UserT, OrdersT} ) ->
  [{N, D, P, InStock}] = ets:lookup(ItemT, ItemName),
  case utility:fail(?CHANCE) of
    true ->
        {stop, "ERROR", {ItemT, UserT, OrdersT}};
    false ->
      ets:insert(ItemT, {N,D,P,InStock + Quantity}),
      {noreply, {ItemT, UserT, OrdersT}}
  end;

%User

%Order
handle_cast({addOrder, UserName, Order},  {Item, UserT, OrderT}) ->
  [{Name, Password, Orders}] = ets:lookup(UserT, UserName),
  case utility:fail(?CHANCE) of
    true ->
      {stop, "ERROR", {Item, UserT, OrderT}};
    false ->
      ets:insert(UserT, {Name, Password, [Order|Orders]}),
      {noreply, {Item, UserT, OrderT}}
  end;

handle_cast({updateOrder, Number, Status}, {Item, UserT, {OrderT, NextNum}}) ->
  case utility:fail(?CHANCE) of
    true ->
      {stop, "ERROR", {Item, UserT, {OrderT, NextNum}}};
    false ->
      [{OrderNum, ItemName, UserName, Quant, _}] =
        ets:lookup(OrderT, Number),
      ets:insert(OrderT, {OrderNum, ItemName, UserName, Quant, Status}),
      {noreply, {Item, UserT, {OrderT, NextNum}}}
  end;

handle_cast(_,State) ->
  {noreply, State}.

handle_info(_, State) ->
  {noreply, State}.

code_change(_OldVsn, State, _Extra) ->
  {ok, State}.


terminate(_Reason, {ItemT, UserT, {OrdersT,N}}) ->
  ets:tab2file(ItemT, "itemDb"),
  ets:tab2file(UserT, "userDb"),
  ets:tab2file(OrdersT, "orderDb"),
  ets:insert(OrdersT, {-1, "Admin", "Admin", N, completed}).

%%% helper functions
%% Keys retrieves all the keys from a given table.
keys(TableName) ->
  FirstKey = ets:first(TableName),
  keys(TableName, FirstKey, [FirstKey]).

keys(_, '$end_of_table', ['$end_of_table'|Acc]) ->
  Acc;

keys(TableName, CurrentKey, Acc) ->
  NextKey = ets:next(TableName, CurrentKey),
  keys(TableName, NextKey, [NextKey|Acc]).



%% tests if a call should fail.
failCall(Chance, Reply, State) ->
  case utility:fail(Chance) of
    true ->
      {stop, "ERROR", {error, moduleDown}, State};
    false ->
      {reply, Reply, State}
  end.
