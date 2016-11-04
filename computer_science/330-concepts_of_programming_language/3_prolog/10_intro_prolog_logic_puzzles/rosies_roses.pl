customer(hugh).
customer(ida).
customer(jeremy).
customer(leroy).
customer(stella).

rose(cottage_beauty).
rose(golden_sunset).
rose(mountain_bloom).
rose(pink_paradise).
rose(sweet_dreams).

event(anniversary).
event(charity_auction).
event(retirement).
event(senior_prom).
event(wedding).

item(balloons).
item(candles).
item(chocolates).
item(place_cards).
item(streamers).


solve :-
    rose(Hrose), rose(Irose),
    rose(Jrose), rose(Lrose), 
    rose(Srose),
    all_different([Hrose, Irose, Jrose, Lrose, Srose]),

    event(Hevent), event(Ievent), 
    event(Jevent), event(Levent), 
    event(Sevent),
    all_different([Hevent, Ievent, Jevent, Levent, Sevent]),

    item(Hitem), item(Iitem),
    item(Jitem), item(Litem),
    item(Sitem),
    all_different([Hitem, Iitem, Jitem, Litem, Sitem]),

    Quadruples = [ [hugh, pink_paradise, Hevent, Hitem],
                    [ida, Irose, Ievent, Iitem],
                    [jeremy, Jrose, senior_prom, Jitem],
                    [leroy, Lrose, retirement, Litem], 
                    [stella, Srose, Sevent, Sitem] ],

    % 1
    member([_, _, _, _], Quadruples),
    ( \+ member([stella, flowers, wedding, _], Quadruples),
        member([stella, cottage_beauty, _, _], Quadruples) ),

    % 2
    ( \+ member([hugh, _, charity_auction, _], Quadruples),
        \+ member([hugh, _, wedding, _], Quadruples) ),

    % 3
    member([_, _, anniversary, streamers], Quadruples),
    member([_, _, wedding, balloons], Quadruples),

    % 4
    member([_, sweet_dreams, _, chocolates], Quadruples),
    \+ member([jeremy, mountain_bloom, _, _], Quadruples),

    % 5
    member([_, _, senior_prom, candles], Quadruples),

    tell(hugh, pink_paradise, Hevent, Hitem),
    tell(ida, Irose, Ievent, Iitem),
    tell(jeremy, Jrose, senior_prom, Jitem),
    tell(leroy, Lrose, retirement, Litem),
    tell(stella, Srose, Sevent, Sitem).


all_different([H | T]) :- member(H, T), !, fail.
all_different([_ | T]) :- all_different(T).
all_different([_]).
 
tell(A, B, C, D) :-
    write(A), write(' bought '), write(B), 
    write(' and '), write(C), 
    write(' for the '), write(D), nl.
