delete(X,[X|R],R).
delete(X,[Y|R],[Y|R1]):-delete(X,R,R1).