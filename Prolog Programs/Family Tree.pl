father(rambabu,pujith).
father(rambabu,bharathi).
father(pullarao,rambabu).
father(baskerrao,jaya).
mother(jaya,pujith).
mother(jaya,bharathi).
mother(kumari,jaya).
male(rambabu).
male(pujith).
male(pullarao).
female(jaya).
female(bharathi).
female(satyavathi).
married(rambabu,jaya).
married(pullarao,satyavathi).
siblings(X,Y):- not(X=Y),father(Z,X),father(Z,Y),mother(P,X),mother(P,Y),married(Z,P).
grandfather(X,Y):-father(Z,Y),father(X,Z);mother(P,Y),father(X,P).