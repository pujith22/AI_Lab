% Check whether a number is perfect or not

perfect(X):- perf(X, 0).

perf(X, S):-
    X =:= S*S.

perf(X, S):- 
	X > S*S, 
	T is S + 1, 
	perf(X, T).

perf(X, S):- 
	X < S*S, 
	fail.


% Check the members of a list for Perfect Numbers

checkPerfect(X, [X|R]):- perfect(X).

checkPerfect(X, [Y|R]):- checkPerfect(X, R).


% Finds Nth Fibonacci Number

fibo(0, 1).
fibo(1, 1).

fibo(X, N):-
    N > 1,
    N1 is N - 1,
    N2 is N - 2,
    fibo(F1, N1),
    fibo(F2, N2),
    X is F1 + F2.
    

% Prints N Fibonacci Numbers

printFib(X, Y, N):- pFib(0, 1, N).

pFibo(X, Y, N):-
    N > 0,
    X1 is Y,
    Y1 is X + Y,
    N1 is N - 1,
    write(X),
    write(' '),
    pFibo(X1, Y1, N1).
    

% Check the members of a list for Fibonacci Numbers

checkFib(H, [H|R]):-
    FibVal is (5*H*H) + 4,
    perfect(FibVal);
    FibVal is (5*H*H) - 4,
    perfect(FibVal).
    
checkFib(H, [Y|R]):-
    checkFib(H, R).