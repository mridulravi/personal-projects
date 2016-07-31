%PROBLEM 1

allguys(L) :- member([ashwin,_],L), member([ankush,_],L), member([krishna,_],L), member([umang,_],L), member([sanket,_],L).
allfloors(L) :- =(L, [[_,_],[_,_],[_,_],[_,_],[_,_]]),  member([_,1],L), member([_,2],L), member([_,3],L), member([_,4],L), member([_,5],L) .
notonthisfloor(P, N, L) :- member([P, X], L), \=(X, N).
notadjacent(S1, S2, L) :- member([S1,X],L), member([S2,Y],L), (abs(X-Y) > 1). 
livesabove(S1, S2, L) :-  member([S1,X],L), member([S2,Y],L), ((X-Y) > 0). 
constraints1(L) :- notonthisfloor(ankush, 1, L), notonthisfloor(ashwin, 5, L), notonthisfloor(umang,1, L), notonthisfloor(umang,5, L).
constraints2(L) :- notadjacent(umang, krishna, L), notadjacent(ankush, umang, L).
constraints3(L) :- livesabove(sanket, ankush, L).
occupancy(L) :- allguys(L), allfloors(L), constraints1(L), constraints2(L), constraints3(L), !.

%PROBLEM 3

nextmove(_,[],_,_).
nextmove(LPREV, LNEXT, XP, YP) :- =(LNEXT, [NP|LT]), movegen(XP,YP,LMOVES), member(NP, LMOVES), \+member(NP, LPREV), =(NP, pair(XN,YN)), append(LPREV, [NP], NEWLPREV), nextmove(NEWLPREV, LT, XN, YN).
movegen(X, Y, L) :- move1(X,Y,L1), move2(X,Y,L2), move3(X,Y,L3), move4(X,Y,L4), move5(X,Y,L5), move6(X,Y,L6), move7(X,Y,L7), move8(X,Y,L8), append(L1,L2,LI1), append(LI1,L3,LI2), append(LI2,L4,LI3), append(LI3,L5, LI4), append(LI4, L6, LI5), append(LI5, L7, LI6), append(LI6, L8, L).
move1(X,Y,L) :- ((>(X,5);>(Y,6))-> =(L,[]); X1 is X+2, Y1 is Y+1, =(L,[pair(X1,Y1)])).
move2(X,Y,L) :- ((>(X,5);<(Y,2))-> =(L,[]); X1 is X+2, Y1 is Y-1, =(L,[pair(X1,Y1)])).
move3(X,Y,L) :- ((<(X,3);>(Y,6))-> =(L,[]); X1 is X-2, Y1 is Y+1, =(L,[pair(X1,Y1)])).
move4(X,Y,L) :- ((<(X,3);<(Y,2))-> =(L,[]); X1 is X-2, Y1 is Y-1, =(L,[pair(X1,Y1)])).
move5(X,Y,L) :- ((>(X,6);>(Y,5))-> =(L,[]); X1 is X+1, Y1 is Y+2, =(L,[pair(X1,Y1)])).
move6(X,Y,L) :- ((>(X,6);<(Y,3))-> =(L,[]); X1 is X+1, Y1 is Y-2, =(L,[pair(X1,Y1)])).
move7(X,Y,L) :- ((<(X,2);>(Y,5))-> =(L,[]); X1 is X-1, Y1 is Y+2, =(L,[pair(X1,Y1)])).
move8(X,Y,L) :- ((<(X,2);<(Y,3))-> =(L,[]); X1 is X-1, Y1 is Y-2, =(L,[pair(X1,Y1)])).
tour(L) :- length(L,49), =(L, [pair(1,1)|LT]), nextmove([pair(1,1)], LT, 1, 1), write(L).

%PROBLEM 2

aisuncertain(A,B,C) :- \+bcyellow(B,C), \+bcred(B,C).
bcyellow(B,C) :- ==(B,yellow), ==(C,yellow).
bcred(B,C) :- ==(B,red), ==(C,red).
acyellow(A,C) :- ==(A,yellow), ==(C,yellow).
acred(A,C) :- ==(A,red), ==(C,red).
bisuncertain(A,B,C) :- \+acyellow(A,C), \+acred(A,C), aisuncertain(A,green,C), aisuncertain(A,yellow,C), aisuncertain(A,red,C).
p(A,B,C) :- member(A,[green, yellow, red]), member(B,[green, yellow, red]), member(C,[green, yellow, red]), aisuncertain(A,B,C), bisuncertain(A,B,C).
goal(Color,Combos) :- p(A,B,C), =(Color, C), =(Combos, [A,B,C]).

%PROBLEM 4

mremove([],L,L2) :- =(L2,L), !.
mremove([X],L,L2) :- mremove([], [X|L],L2).
mremove([X,X|Y],L,L2) :- mremove([X|Y],L,L2).
mremove([X1,X2|Y],L,L2) :- \=(X1,X2), mremove([X2|Y],[X1|L],L2).
rm(L1,L) :- mremove(L1,[],L), !.

reached(0,0,right,L2,L) :- =(L2,L).
reached(MISL,CANL,BOATLOC,L,L12) :- bagof(X, boatmove(MISL, CANL, BOATLOC, X),LMOVES), member(NMOVE, LMOVES), \+member(NMOVE, L), append(L, [NMOVE], L1), =(NMOVE,[M1,C1,BL1]), reached(M1,C1,BL1,L1,L12).
boatmove(ML, CL, BTL, X) :- (==(BTL,left) ->
	between(0,ML,ML1), between(0,CL,CL1), MR1 is 3-ML1, CR1 is 3-CL1,
	(ML-ML1+CL-CL1)=<2, (ML-ML1+CL-CL1)>0, (ML1 >= CL1 ; ==(ML1,0)), (MR1 >= CR1 ; ==(MR1,0)),
	=(X,[ML1, CL1, right])
;
	MR is 3-ML, CR is 3-CL, 
	between(0,MR,MR1), between(0,CR,CR1), ML1 is 3-MR1, CL1 is 3-CR1,
	(MR-MR1+CR-CR1)=<2,(MR-MR1+CR-CR1)>0, (MR1>=CR1 ; ==(MR1,0)), (ML1>=CL1 ; ==(ML1,0)),
	=(X,[ML1,CL1,left])
).
safe(L) :- bagof(X,reached(3,3,left,[[3,3,left]],X),LSOL), rm(LSOL, L1SOL), member(L,L1SOL), write(L).