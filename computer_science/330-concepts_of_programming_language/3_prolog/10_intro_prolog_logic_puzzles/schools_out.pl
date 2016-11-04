subject(english).
subject(gym).
subject(history).
subject(math).
subject(science).

teacher(ms_appleton).
teacher(ms_gross).
teacher(mr_knight).
teacher(mr_mcevoy).
teacher(ms_parnell).

activity(antiquing).
activity(camping).
activity(sightseeing).
activity(spelunking).
activity(water_skiing).

state(california).
state(florida).
state(maine).
state(oregan).
state(virginia).

solve :-
    subject(Asubject), subject(Gsubject),
    subject(Ksubject), subject(Msubject), 
    subject(Psubject),
    all_different([Asubject, Gsubject, Ksubject, Msubject, Psubject]),

    state(Astate), state(Gstate), 
    state(Kstate), state(Mstate), 
    state(Pstate),
    all_different([Astate, Gstate, Kstate, Mstate, Pstate]),

    activity(Aactivity), activity(Gactivity),
    activity(Kactivity), activity(Mactivity),
    activity(Pactivity),
    all_different([Aactivity, Gactivity, Kactivity, Mactivity, Pactivity]),

    Quadruples = [ [ms_appleton, Asubject, Astate, Aactivity],
                    [ms_gross, Gsubject, Gstate, Gactivity],
                    [mr_knight, Ksubject, Kstate, Kactivity],
                    [mr_mcevoy, Msubject, Mstate, Mactivity],
                    [ms_parnell, Psubject, Pstate, Pactivity] ],

    % 1
    ( member([ms_gross, math, _, _], Quadruples); 
            member([ms_gross, science, _, _], Quadruples) ),
    ( member([ms_gross, _, florida, antiquing], Quadruples); 
        (member([ms_gross, _, california, _], Quadruples), 
            \+ (member([ms_gross, _, california, antiquing], Quadruples))) ),

    % 2
    ( member([_, science, california, water_skiing], Quadruples); 
            member([_, science, florida, water_skiing], Quadruples) ),
    ( member([mr_mcevoy, history, maine, _], Quadruples); 
        member([mr_mcevoy, history, oregan, _], Quadruples) ),

    % 3
    ( member([ms_appleton, english, virginia, _], Quadruples); 
        member([ms_parnell, english, _, spelunking], Quadruples) ),

    % 4
    \+ member([_, gym, maine, sightseeing], Quadruples),

    % 5
    \+ member([ms_gross, _, _, camping], Quadruples),
    ( member([ms_gross, _, _, antiquing], Quadruples); 
        member([ms_appleton, _, _, antiquing], Quadruples); 
        member([ms_parnell, _, _, antiquing], Quadruples) ),

    tell(ms_appleton, Asubject, Astate, Aactivity),
    tell(ms_gross, Gsubject, Gstate, Gactivity),
    tell(mr_knight, Ksubject, Kstate, Kactivity),
    tell(mr_mcevoy, Msubject, Mstate, Mactivity),
    tell(ms_parnell, Psubject, Pstate, Pactivity).

all_different([H | T]) :- member(H, T), !, fail.
all_different([_ | T]) :- all_different(T).
all_different([_]).
 
tell(A, B, C, D) :-
    write(A), write(' teaches '), write(B), 
    write(' and is going to '), write(C), 
    write(' and is going '), write(D), nl.



