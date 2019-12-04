% N-Queens Problem

perm([X|Y], Z):- 
    perm(Y, W), 
    takeout(X, Z, W).
    
perm([],[]).

takeout(X, [X|R], R).

takeout(X, [F|R], [F|S]):- 
    takeout(X,R,S).

solve(P):-
     perm([1,2,3,4], P), 
     combine([1,2,3,4], P, S, D),
     all_diff(S),
     all_diff(D).

combine([X1|X], [Y1|Y], [S1|S], [D1|D]):-
     S1 is X1 + Y1,
     D1 is X1 - Y1,
     combine(X, Y, S, D).
     
combine([], [], [], []).

all_diff([X|Y]):- 
    \+member(X,Y), 
    all_diff(Y).

all_diff([X]).