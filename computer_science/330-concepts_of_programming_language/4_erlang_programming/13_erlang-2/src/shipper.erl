-module(shipper).
%%defiens a shipping subroutine, that will ship items, and buy new items.

-export([start_link/1, start/1]).

-define(ORDERINT, 1501).
-define(SHIPINT, 1045).
-define(MAXORDER, 30).

-include("defines.hrl").

%%Starts the Shipper, returns {ok, PID}.
start_link(NameServer) ->
  Pid = spawn_link(?MODULE, start, [NameServer]),
  {ok, Pid}.

start(NameServer) ->
  io:fwrite("Shipper Started~n"),
  self() ! {start, NameServer},
  name_server:register(NameServer, ?SHIPMOD, self()),

  timer:send_interval(?ORDERINT, order),
  timer:send_interval(?SHIPINT, ship),
  loop([]).


loop(Db) ->
  receive
    order ->
      order(Db),
      loop(Db);
    ship ->
      ship(Db),
      loop(Db);
    {start, NameServer} ->
      timer:sleep(500),
      NDb = name_server:resolve_with_fail(NameServer, ?DBMOD),
      loop(NDb)
  end.

order(Db) ->
  case utility:fail(?CHANCE) of
    true ->
      exit("ERROR");
    false ->
      order(database:get_items(Db), Db)
  end.

order([Item | Rest], Db) ->
  A = database:get_item_info(Db, Item),
  case A of
    {_, _, _, InStock} ->
      if
        InStock == 0 ->
          Order = random:uniform(?MAXORDER),
          database:add_stock(Db, Item, Order);
        true ->
          []
      end;
    _ -> 
      []
  end,
  order(Rest, Db);

order([], _) -> true.



ship(Db) ->
  case utility:fail(?CHANCE) of
    true ->
      exit("ERROR");
    false ->
      ship(database:get_orders(Db), Db)
  end.

ship([{Num, _, _, _, Status}|Rest], Db) ->
  case Status of
    ordered ->
      database:update_order_status(Db, Num, shipped);
    shipped ->
      database:update_order_status(Db, Num, completed);
    completed ->
      []
  end,
  ship(Rest, Db);

  ship([], _Db) -> true.
