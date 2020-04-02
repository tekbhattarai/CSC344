

in_bound([A,B], [X,Y,Width,Height]) :-

 A >= X, A < X + Width,
 B =< Y, B > Y - Height.




move(X, Y, right, M, A, B, right, M):-
    B is Y,
	A is X+1.
move(X, Y, up, M, A, B, up, M):-
    A is X,
	B is Y+1.
move(X, Y, down, M, A, B, down, M):-
    A is X,
	B is Y-1.
move(X, Y, right, M, A, B, up, [[X,Y,/]|M]):-
    A is X,
	B is Y+1.
move(X, Y, right, M, A, B, down, [[X,Y,\]|M]):-
    A is X,
	B is Y-1.
move(X, Y, down, M, A, B, right, [[X,Y,\]|M]):-
    B is Y,
	A is X+1.
move(X, Y, up, M, A, B, right, [[X,Y,/]|M]):-
    B is Y,
	A is X+1.


% no base case
safe(_, []).
safe(C, [[X,Width,Height]|Tail]) :- \+in_bound(C, [X,10,Width,Height]),
	safe(C, Tail).
safe(C, [[X,Y,Width,Height]|Tail]) :- \+in_bound(C, [X,Y,Width,Height]),
	safe(C, Tail).



place_mirrors(H, Obstacles, X) :- 
    place_mirrors(1, H, H, Obstacles, [], [], right,X).

place_mirrors(12, Y, H, _, M, _, right, M):-
    Y = H,
    length(M,L),
    L < 9.

% check for loops
place_mirrors(X, Y, H, Obstacles, M, Path, Dir, XO) :-

in_bound([X,Y],[0,10,12,10]),
	 length(M,L),
         L < 9,
   
  move(X, Y, Dir, M, A, B, NewDir, NM),
        \+member([X,Y], Path),
	safe([X, Y], Obstacles),
	
  place_mirrors(A,B,H,Obstacles,NM,[[X, Y] | Path], NewDir, XO).











