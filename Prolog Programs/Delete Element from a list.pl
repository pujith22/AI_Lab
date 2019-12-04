delete(X,[X|R],R).
delete(X,[Y|R],[Y|R1]):-delete(X,R,R1).

%query: delete([2,[3,4,2,5],L).