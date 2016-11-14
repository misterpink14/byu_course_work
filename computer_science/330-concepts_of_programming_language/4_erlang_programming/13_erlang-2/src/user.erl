-module(user).
%%% the user Module manages users. It keeps track of who is logged on, and logs
%%% Users out when there client goes down. It is also used to create new users
%%% and acess the state of a users orders, It checks to see if users are logged in
-behavior(gen_server).

-export([start_link/1, logon/4, create_user/3, is_logged_in/2, get_order_status/2 ]).
-export([init/1, handle_call/3, handle_cast/2,
          handle_info/2, code_change/3, terminate/2]).

-include("defines.hrl").

%% Starts a User Server
start_link(NameServer) ->
  gen_server:start_link(?MODULE, NameServer, []).

%% Logs the user on, Caller PID assumed to be pid of user
% logon(UserServer, Username, Password) ->
%   gen_server:call(UserServer, {logon, Username, Password, self()}).

%%Logs the user on, takes explicit PID.
logon(UserServer, Username, Password, Pid) ->
  gen_server:call(UserServer, {logon, Username, Password, Pid}).

%% Creates a new User.
create_user(UserServer, UserName, Password) ->
  gen_server:call(UserServer, {newUser, UserName, Password}).

%% Tests if user is logged in. returns a boolean.
is_logged_in(UserServer, UserName) ->
  gen_server:call(UserServer, {isLoggedIn, UserName}).

%%Returns a list of strings describing the status of each order the User has placed.
%%User must be logged in for this to succeed
get_order_status(UserServer, UserName) ->
  gen_server:call(UserServer, {getOrders, UserName}).

%%% gen_server Functions
init(NameServer) ->
  io:fwrite("User Started~n"),
  name_server:register(NameServer, ?USERMOD, self()),
  self() ! {start, NameServer},
%  process_flag(trap_exit, true),
  {ok, {{orddict:new(), ordsets:new() }, {[], []}}}.


%%calls
handle_call({logon, UserName, Password, UserPID}, _From, {{UserDict, Users}, {Db, Order}}) ->
  case database:is_valid_user(Db, UserName, Password) of
    true ->
      case ordsets:is_element(UserName, Users) of
        true ->
          {reply, {error, "User currently logged in"}, {{UserDict, Users}, {Db, Order}}};
        false ->
          Ref = erlang:monitor(process, UserPID),
          NewUserDict = orddict:store(Ref, UserName, UserDict),
          NewUsers = ordsets:add_element(UserName, Users),
          {reply, true, {{NewUserDict, NewUsers}, {Db, Order}}}
      end;
    false ->
      {reply, {error, "No such User"}, {{UserDict, Users}, {Db, Order}}}
  end;

handle_call({newUser, UserName, Password}, _From, {Users, {Db, Order}}) ->
  case utility:fail(?CHANCE) of
    true ->
      {stop, "ERROR", {error, moduleDown}, {Users, {Db, Order}}};
    false ->
      {reply, database:add_user(Db, UserName, Password), {Users, {Db, Order}}}
  end;

handle_call({isLoggedIn, UserName}, _From, {{UserDict, Users}, Db}) ->
  case utility:fail(?CHANCE) of
    true ->
      {stop, "ERROR", false, {{UserDict, Users}, Db}};
    false ->
      {reply, ordsets:is_element(UserName, Users), {{UserDict, Users}, Db}}
  end;

handle_call({getOrders, UserName}, _From, {{UserDict, Users}, {Db, Order}}) ->
  case utility:fail(?CHANCE) of
    true ->
      {stop, "ERROR", {error, moduleDown}, {{UserDict, Users}, {Db, Order}}};
    false->
      case ordsets:is_element(UserName, Users) of
        true ->
          Orders = database:get_user_orders(Db, UserName),
          {reply, orders(Orders, Order), {{UserDict, Users}, {Db, Order}}};
        false ->
          {reply, {error, "User Not Logged In"}, {{UserDict, Users}, {Db, Order}}}
      end
  end;

handle_call(_, _From, State) ->
  {stop, "ERROR", State}.

%%casts
handle_cast(_, State) ->
  {stop, "ERROR", State}.

%% INfo
handle_info({'DOWN', Ref, _, _, _}, {{UserDict, Users}, Db}) ->
  case utility:fail(?CHANCE) of
    true ->
      {stop, "ERROR", {UserDict, Users}};
    false ->
      UserName = orddict:fetch(Ref, UserDict),
      Nu = ordsets:del_element(UserName, Users),
      NUD= orddict:erase(Ref, UserDict),
      {noreply, {{NUD, Nu}, Db}}
    end;

handle_info({start, NameServer}, {Users, _}) ->
  timer:sleep(500),
  Db = name_server:resolve_with_fail(NameServer, ?DBMOD),
  Order = name_server:resolve_with_fail(NameServer, ?ORDERMOD),
  {noreply, {Users, {Db, Order}}};

handle_info(_, State) ->
  {stop, "ERROR", State}.


code_change(_OldVsn, State, _Extra) ->
  {ok, State}.

terminate(_,_) ->
  {ok, error}.

%%% Helper functions.

% gets status of each order from a list of order Numbers.
orders(List, Db) ->
  orders(List, Db, []).

orders([This|Rest], Db, ACC) ->
  Name = order:get_item_name(Db, This),
  Status = atom_to_list(order:get_status(Db, This)),
  NL = Name ++ " is " ++ Status,
  orders(Rest, Db, [NL|ACC]);

orders([], _, ACC) ->
  ACC.
