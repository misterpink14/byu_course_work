-module(name_server).
%%% The Name_server defines a portable name space. It allows processes to register
%% themselves under atoms, which then allows others to access their services.
%%
-behavior(gen_server).

-export([start_link/0, start/0, register/2, register/3, resolve/2, resolve_with_fail/2]).

-export([init/1, handle_call/3, handle_cast/2,
          handle_info/2, code_change/3, terminate/2]).

%%Starts a name server, and return {ok, PID}.
start_link() ->
  gen_server:start_link(name_server,[],  []).

start() ->
  gen_server:start(name_server, [], []).

%% register youself with the given name server with the given name.
%% if the name is already taken it is overwritten.
%% returns ok
register(Ns, Name) ->
  gen_server:call(Ns, {register, Name}).

%% Same as Regsiter/2 except it is an asycronous call, and takes an explicit pid.
register(Ns, Name, Pid) ->
  gen_server:cast(Ns, {register, Name, Pid}).

%% returns the pid associated with the Name, if the Name is not registered,
%% it returns false.
resolve(Ns, Name) ->
  gen_server:call(Ns, {resolve, Name}).

%% same as resolve but will exit with failure if name is not registered
resolve_with_fail(NameServer, Name) ->
  case resolve(NameServer, Name) of
    false ->
      exit(io:fwrite("~s Not registered with NameServer",  [Name]));
    Pid ->
      Pid
  end.

%%gen_server functions

init(_) ->
  {ok, {orddict:new(), orddict:new()}}.

handle_call({register, Name}, {Pid, _Tag}, {NamesToPid, RefToName} ) ->
  Ref = monitor(process, Pid),
  NR = orddict:store(Ref, Name, RefToName),
  NN = orddict:store(Name, Pid, NamesToPid),
  {reply, ok, {NN, NR}};

handle_call({resolve, Name}, _From, {NamesToPid, RefToName}) ->
  case orddict:is_key(Name, NamesToPid) of
    true ->
      {reply, orddict:fetch(Name, NamesToPid), {NamesToPid, RefToName}};
    false ->
      {reply, false, {NamesToPid, RefToName}}
  end;

handle_call(_, _, State) ->
  {reply, ok, State}.

handle_cast({register, Name, Pid}, {NamesToPid, RefToName} ) ->
  Ref = monitor(process, Pid),
  NR = orddict:store(Ref, Name, RefToName),
  NN = orddict:store(Name, Pid, NamesToPid),
  {noreply, {NN, NR}};

handle_cast(_, State) ->
  {noreply, State}.

handle_info({'DOWN', Ref, _, _, _}, {NamesToPid, RefToName}) ->
  Name = orddict:fetch(Ref, RefToName),
  NR = orddict:erase(Name, RefToName),
  NN= orddict:erase(Name, NamesToPid),
  {noreply, {NN, NR}};

handle_info(_, State) ->
  {noreply, State}.

code_change(_OldVsn, State, _Extra) ->
  {ok, State}.

terminate(_Reason, _State) ->
  [].
