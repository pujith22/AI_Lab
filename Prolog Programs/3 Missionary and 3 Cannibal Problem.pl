solve :- path([3,3,east],[0,0,west],[[3,3,east]],MoveList), nl,nl,printMoveList(MoveList).

printMoveList([]) :- nl, nl.

printMoveList([[A,B,Desc]|T]) :- write('Final State: '),write(B),write(' '),write('After action: '),write(Desc),nl,printMoveList(T).

path([A,B,C],[A,B,C],_,[]).

path([A,B,C],[D,E,F],Visited,Moves) :- 	move([A,B,C],[I,J,K],Description), safe([I,J,K]), \+ 
										member([I,J,K],Visited), path([I,J,K],[D,E,F],[[I,J,K]|Visited],MoreMoves), 
										Moves = [[[A,B,C],[I,J,K],Description] | MoreMoves].

move([A,B,east],[C,B,west],'1 cannibal cross the river') :- A > 0, C is A - 1.

move([A,B,east],[C,B,west],'2 cannibals cross the river') :- A > 1, C is A - 2.

move([A,B,east],[C,D,west], '1 cannibal and 1 missionary cross the river') :- A > 0, B > 0, C is A - 1, D is B - 1.

move([A,B,east],[A,D,west], '1 missionary cross the river') :- B > 0, D is B - 1.

move([A,B,east],[A,D,west], '2 missionaries cross the river') :- B > 1, D is B - 2.

move([A,B,west],[C,B,east], '1 cannibal come back') :- A < 3, C is A + 1.

move([A,B,west],[C,B,east], '2 cannibals come back') :- A < 2, C is A + 2.

move([A,B,west],[C,D,east], '1 cannibal and 1 missionary come back') :- A < 3, B < 3, C is A + 1, D is B+1.

move([A,B,west],[A,D,east], '1 missionary come back') :- B < 3, D is B + 1.

move([A,B,west],[A,D,east], '2 missionaries come back') :- B < 2, D is B + 2.

safe([A,B,_]) :- (A =< B ; B = 0), C is 3 - A, D is 3 - B, (C =< D ;  D = 0).