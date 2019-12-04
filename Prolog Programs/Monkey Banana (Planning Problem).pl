
% Monkey Banana Problem (Planning)


action(state(middle,onbox,middle,hasnot),grasp,state(middle,onbox,middle,has)).
action(state(P,onfloor,P,H),climb,state(P,onbox,P,H)).
action(state(P1,onfloor,P1,H),push(P1,P2),state(P2,onfloor,P2,H)).
action(state(P1,onfloor,B,H),walk(P1,P2),state(P2,onfloor,B,H)).
plan(State,State,[]).
plan(State1,Goalstate,[Action1|Rest]):- action(State1,Action1,State2),plan(State2,Goalstate,Rest).


% Query: plan(state(atdoor,onfloor,atwindow,hasnot),state(_,_,_,has),Plan).