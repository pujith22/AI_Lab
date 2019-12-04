hole(1,4).
hole(2,2).
hole(4,3).

maze(A,B,N,M,Z):-A=:=N,B=:=M,write('Done!'),nl,write(Z),!.
maze(A,B,N,M,Z):-K is A+1,K=<N,\+hole(K,B),maze(K,B,N,M,[(K,B)|Z]).
maze(A,B,N,M,Z):-K is B+1,K=<M,\+hole(A,K),maze(A,K,N,M,[(A,K)|Z]).