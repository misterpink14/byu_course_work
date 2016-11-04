% A Sudoku solver.  The basic idea is for each position,
% check that it is a digit with `digit`.  Then verify that the digit
% chosen doesn't violate any constraints (row, column, and cube).
% If no constraints were violated, proceed further.  If a constraint
% was violated, then backtrack to the last digit choice and move from
% there (the Prolog engine should handle this for you automatically).
% If we reach the end of the board with this scheme, it means that
% the whole thing is solved.
 
% YOU SHOULD FILL IN THE SOLVE PROCEDURE, DOWN BELOW.
 
digit(1).
digit(2).
digit(3).
digit(4).
digit(5).
digit(6).
digit(7).
digit(8).
digit(9).
 
numBetween(Num, Lower, Upper) :-
    Num >= Lower,
    Num =< Upper.
 
% cubeBounds: (RowLow, RowHigh, ColLow, ColHigh, CubeNumber)
cubeBounds(0, 2, 0, 2, 0).
cubeBounds(0, 2, 3, 5, 1).
cubeBounds(0, 2, 6, 8, 2).
cubeBounds(3, 5, 0, 2, 3).
cubeBounds(3, 5, 3, 5, 4).
cubeBounds(3, 5, 6, 8, 5).
cubeBounds(6, 8, 0, 2, 6).
cubeBounds(6, 8, 3, 5, 7).
cubeBounds(6, 8, 6, 8, 8).
 
% Given a board and the index of a column of interest (0-indexed),
% returns the contents of the column as a list.
% columnAsList: (Board, ColumnNumber, AsRow)
columnAsList([], _, []).
columnAsList([Head|Tail], ColumnNum, [Item|Rest]) :-
    nth0(ColumnNum, Head, Item),
    columnAsList(Tail, ColumnNum, Rest).
 
% given which row and column we are in, gets which cube
% is relevant.  A helper ultimately for `getCube`.
% cubeNum: (RowNum, ColNum, WhichCube)
cubeNum(RowNum, ColNum, WhichCube) :-
    cubeBounds(RowLow, RowHigh, ColLow, ColHigh, WhichCube),
    numBetween(RowNum, RowLow, RowHigh),
    numBetween(ColNum, ColLow, ColHigh).
 
% Drops the first N elements from a list.  A helper ultimately
% for `getCube`.
% drop: (InputList, NumToDrop, ResultList)
drop([], _, []):-!.
drop(List, 0, List):-!.
drop([_|Tail], Num, Rest) :-
    Num > 0,
    NewNum is Num - 1,
    drop(Tail, NewNum, Rest).
 
% Takes the first N elements from a list.  A helper ultimately
% for `getCube`.
% take: (InputList, NumToTake, ResultList)
take([], _, []):-!.
take(_, 0, []):-!.
take([Head|Tail], Num, [Head|Rest]) :-
    Num > 0,
    NewNum is Num - 1,
    take(Tail, NewNum, Rest).
 
% Gets a sublist of a list in the same order, inclusive.
% A helper for `getCube`.
% sublist: (List, Start, End, NewList)
sublist(List, Start, End, NewList) :-
    drop(List, Start, TempList),
    NewEnd is End - Start + 1,
    take(TempList, NewEnd, NewList).
 
% Given a board and cube number, gets the corresponding cube as a list.
% Cubes are 3x3 portions, numbered from the top left to the bottom right,
% starting from 0.  For example, they would be numbered like so:
%
% 0  1  2
% 3  4  5
% 6  7  8
%
% getCube: (Board, CubeNumber, ContentsOfCube)
getCube(Board, Number, AsList) :-
    cubeBounds(RowLow, RowHigh, ColLow, ColHigh, Number),
    sublist(Board, RowLow, RowHigh, [Row1, Row2, Row3]),
    sublist(Row1, ColLow, ColHigh, Row1Nums),
    sublist(Row2, ColLow, ColHigh, Row2Nums),
    sublist(Row3, ColLow, ColHigh, Row3Nums),
    append(Row1Nums, Row2Nums, TempRow),
    append(TempRow, Row3Nums, AsList).
 
% Validate given information about a board peice
checkBoardPiece(Cell, Row, Col, Cube) :-
    nonvar(Cell); var(Cell), digit(Cell), is_set(Row), is_set(Col), is_set(Cube).
 
% Given a board, solve it in-place.
% After calling `solve` on a board, the board should be fully
% instantiated with a satisfying Sudoku solution.
solve(Board) :- 
    length(Board, 9),

    [Row_0, Row_1, Row_2, Row_3, Row_4, Row_5, Row_6, Row_7, Row_8] = Board,

    [S00, S01, S02, S03, S04, S05, S06, S07, S08] = Row_0,
    [S10, S11, S12, S13, S14, S15, S16, S17, S18] = Row_1,
    [S20, S21, S22, S23, S24, S25, S26, S27, S28] = Row_2,
    [S30, S31, S32, S33, S34, S35, S36, S37, S38] = Row_3,
    [S40, S41, S42, S43, S44, S45, S46, S47, S48] = Row_4,
    [S50, S51, S52, S53, S54, S55, S56, S57, S58] = Row_5,
    [S60, S61, S62, S63, S64, S65, S66, S67, S68] = Row_6,
    [S70, S71, S72, S73, S74, S75, S76, S77, S78] = Row_7,
    [S80, S81, S82, S83, S84, S85, S86, S87, S88] = Row_8,

    getCube(Board, 0, Cube_0), getCube(Board, 1, Cube_1), getCube(Board, 2, Cube_2),
    getCube(Board, 3, Cube_3), getCube(Board, 4, Cube_4), getCube(Board, 5, Cube_5),
    getCube(Board, 6, Cube_6), getCube(Board, 7, Cube_7), getCube(Board, 8, Cube_8),

    columnAsList(Board, 0, Col_0), columnAsList(Board, 1, Col_1), columnAsList(Board, 2, Col_2),
    columnAsList(Board, 3, Col_3), columnAsList(Board, 4, Col_4), columnAsList(Board, 5, Col_5),
    columnAsList(Board, 6, Col_6), columnAsList(Board, 7, Col_7), columnAsList(Board, 8, Col_8),

    checkBoardPiece(S00, Row_0, Col_0, Cube_0),
    checkBoardPiece(S01, Row_0, Col_1, Cube_0),
    checkBoardPiece(S02, Row_0, Col_2, Cube_0),
    checkBoardPiece(S03, Row_0, Col_3, Cube_1),
    checkBoardPiece(S04, Row_0, Col_4, Cube_1),
    checkBoardPiece(S05, Row_0, Col_5, Cube_1),
    checkBoardPiece(S06, Row_0, Col_6, Cube_2),
    checkBoardPiece(S07, Row_0, Col_7, Cube_2),
    checkBoardPiece(S08, Row_0, Col_8, Cube_2),
    checkBoardPiece(S10, Row_1, Col_0, Cube_0),
    checkBoardPiece(S11, Row_1, Col_1, Cube_0),
    checkBoardPiece(S12, Row_1, Col_2, Cube_0),
    checkBoardPiece(S13, Row_1, Col_3, Cube_1),
    checkBoardPiece(S14, Row_1, Col_4, Cube_1),
    checkBoardPiece(S15, Row_1, Col_5, Cube_1),
    checkBoardPiece(S16, Row_1, Col_6, Cube_2),
    checkBoardPiece(S17, Row_1, Col_7, Cube_2),
    checkBoardPiece(S18, Row_1, Col_8, Cube_2),
    checkBoardPiece(S20, Row_2, Col_0, Cube_0),
    checkBoardPiece(S21, Row_2, Col_1, Cube_0),
    checkBoardPiece(S22, Row_2, Col_2, Cube_0),
    checkBoardPiece(S23, Row_2, Col_3, Cube_1),
    checkBoardPiece(S24, Row_2, Col_4, Cube_1),
    checkBoardPiece(S25, Row_2, Col_5, Cube_1),
    checkBoardPiece(S26, Row_2, Col_6, Cube_2),
    checkBoardPiece(S27, Row_2, Col_7, Cube_2),
    checkBoardPiece(S28, Row_2, Col_8, Cube_2),
    checkBoardPiece(S30, Row_3, Col_0, Cube_3),
    checkBoardPiece(S31, Row_3, Col_1, Cube_3),
    checkBoardPiece(S32, Row_3, Col_2, Cube_3),
    checkBoardPiece(S33, Row_3, Col_3, Cube_4),
    checkBoardPiece(S34, Row_3, Col_4, Cube_4),
    checkBoardPiece(S35, Row_3, Col_5, Cube_4),
    checkBoardPiece(S36, Row_3, Col_6, Cube_5),
    checkBoardPiece(S37, Row_3, Col_7, Cube_5),
    checkBoardPiece(S38, Row_3, Col_8, Cube_5),
    checkBoardPiece(S40, Row_4, Col_0, Cube_3),
    checkBoardPiece(S41, Row_4, Col_1, Cube_3),
    checkBoardPiece(S42, Row_4, Col_2, Cube_3),
    checkBoardPiece(S43, Row_4, Col_3, Cube_4),
    checkBoardPiece(S44, Row_4, Col_4, Cube_4),
    checkBoardPiece(S45, Row_4, Col_5, Cube_4),
    checkBoardPiece(S46, Row_4, Col_6, Cube_5),
    checkBoardPiece(S47, Row_4, Col_7, Cube_5),
    checkBoardPiece(S48, Row_4, Col_8, Cube_5),
    checkBoardPiece(S50, Row_5, Col_0, Cube_3),
    checkBoardPiece(S51, Row_5, Col_1, Cube_3),
    checkBoardPiece(S52, Row_5, Col_2, Cube_3),
    checkBoardPiece(S53, Row_5, Col_3, Cube_4),
    checkBoardPiece(S54, Row_5, Col_4, Cube_4),
    checkBoardPiece(S55, Row_5, Col_5, Cube_4),
    checkBoardPiece(S56, Row_5, Col_6, Cube_5),
    checkBoardPiece(S57, Row_5, Col_7, Cube_5),
    checkBoardPiece(S58, Row_5, Col_8, Cube_5),
    checkBoardPiece(S60, Row_6, Col_0, Cube_6),
    checkBoardPiece(S61, Row_6, Col_1, Cube_6),
    checkBoardPiece(S62, Row_6, Col_2, Cube_6),
    checkBoardPiece(S63, Row_6, Col_3, Cube_7),
    checkBoardPiece(S64, Row_6, Col_4, Cube_7),
    checkBoardPiece(S65, Row_6, Col_5, Cube_7),
    checkBoardPiece(S66, Row_6, Col_6, Cube_8),
    checkBoardPiece(S67, Row_6, Col_7, Cube_8),
    checkBoardPiece(S68, Row_6, Col_8, Cube_8),
    checkBoardPiece(S70, Row_7, Col_0, Cube_6),
    checkBoardPiece(S71, Row_7, Col_1, Cube_6),
    checkBoardPiece(S72, Row_7, Col_2, Cube_6),
    checkBoardPiece(S73, Row_7, Col_3, Cube_7),
    checkBoardPiece(S74, Row_7, Col_4, Cube_7),
    checkBoardPiece(S75, Row_7, Col_5, Cube_7),
    checkBoardPiece(S76, Row_7, Col_6, Cube_8),
    checkBoardPiece(S77, Row_7, Col_7, Cube_8),
    checkBoardPiece(S78, Row_7, Col_8, Cube_8),
    checkBoardPiece(S80, Row_8, Col_0, Cube_6),
    checkBoardPiece(S81, Row_8, Col_1, Cube_6),
    checkBoardPiece(S82, Row_8, Col_2, Cube_6),
    checkBoardPiece(S83, Row_8, Col_3, Cube_7),
    checkBoardPiece(S84, Row_8, Col_4, Cube_7),
    checkBoardPiece(S85, Row_8, Col_5, Cube_7),
    checkBoardPiece(S86, Row_8, Col_6, Cube_8),
    checkBoardPiece(S87, Row_8, Col_7, Cube_8),
    checkBoardPiece(S88, Row_8, Col_8, Cube_8).

% ---- PUT CODE HERE ---
% ---- PUT CODE HERE ---
 
% Prints out the given board.
printBoard([]).
printBoard([Head|Tail]) :-
        write(Head), write(' '), nl,
        printBoard(Tail).
 
test1(Board) :-
        Board = [[2, _, _, _, 8, 7, _, 5, _],
                 [_, _, _, _, 3, 4, 9, _, 2],
                 [_, _, 5, _, _, _, _, _, 8],
                 [_, 6, 4, 2, 1, _, _, 7, _],
                 [7, _, 2, _, 6, _, 1, _, 9],
                 [_, 8, _, _, 7, 3, 2, 4, _],
                 [8, _, _, _, _, _, 4, _, _],
                 [3, _, 9, 7, 4, _, _, _, _],
                 [_, 1, _, 8, 2, _, _, _, 5]],
        solve(Board),
        printBoard(Board).
 
test2(Board) :-
        Board = [[_, _, _, 7, 9, _, 8, _, _],
                 [_, _, _, _, _, 4, 3, _, 7],
                 [_, _, _, 3, _, _, _, 2, 9],
                 [7, _, _, _, 2, _, _, _, _],
                 [5, 1, _, _, _, _, _, 4, 8],
                 [_, _, _, _, 5, _, _, _, 1],
                 [1, 2, _, _, _, 8, _, _, _],
                 [6, _, 4, 1, _, _, _, _, _],
                 [_, _, 3, _, 6, 2, _, _, _]],
        solve(Board),
        printBoard(Board).

