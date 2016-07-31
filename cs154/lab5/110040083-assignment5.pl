

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%           Problem-1
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%


not_on_5(X,[X,_,_,_,_]).
not_on_5(X,[_,X,_,_,_]).
not_on_5(X,[_,_,X,_,_]).
not_on_5(X,[_,_,_,X,_]).

not_on_1(X,[_,X,_,_,_]).
not_on_1(X,[_,_,X,_,_]).
not_on_1(X,[_,_,_,X,_]).
not_on_1(X,[_,_,_,_,X]).

not_adjacent(X,Y,[_,_,X,_,Y]).
not_adjacent(X,Y,[_,X,_,_,Y]).
not_adjacent(X,Y,[X,_,_,_,Y]).
not_adjacent(X,Y,[_,X,_,Y,_]).
not_adjacent(X,Y,[X,_,_,Y,_]).
not_adjacent(X,Y,[X,_,Y,_,_]).
not_adjacent(X,Y,[_,_,Y,_,X]).
not_adjacent(X,Y,[_,Y,_,_,X]).
not_adjacent(X,Y,[_,Y,_,X,_]).
not_adjacent(X,Y,[Y,_,X,_,_]).
not_adjacent(X,Y,[Y,_,_,X,_]).
not_adjacent(X,Y,[Y,_,_,_,X]).

above(X,Y,[Y,X,_,_,_]).
above(X,Y,[Y,_,X,_,_]).
above(X,Y,[Y,_,_,X,_]).
above(X,Y,[Y,_,_,_,X]).
above(X,Y,[_,Y,X,_,_]).
above(X,Y,[_,Y,_,X,_]).
above(X,Y,[_,Y,_,_,X]).
above(X,Y,[_,_,Y,X,_]).
above(X,Y,[_,_,Y,_,X]).
above(X,Y,[_,_,_,Y,X]).

occupency(B) :- B = [[_,1],[_,2],[_,3],[_,4],[_,5]],
              not_on_5([ashwin,_],B),
              not_on_1([ankush,_],B),
              not_on_5([umang,_],B),
              not_on_1([umang,_],B),
              not_adjacent([umang,_],[krishna,_],B),
              not_adjacent([umang,_],[ankush,_],B),
              above([sanket,_],[ankush,_],B),
              member([sanket,_],B),
              member([ankush,_],B),
              member([ashwin,_],B),
              member([umang,_],B), 
              member([krishna,_], B),
              member([_,1],B),
              member([_,2],B),
              member([_,3],B),
              member([_,4],B), 
              member([_,5],B).



%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%           Problem-2
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%


% Each Combination is represented as [A,B,C]
% where A,B,C are the respective colors.

auncertain([_,X,Y]) :-  (X=green , Y=red) ;
                          (X=green , Y=yellow) ;
                          (X=green , Y=green) ;
                          (X=red , Y=yellow) ;
                          (X=red , Y=green) ;
                          (X=yellow , Y=red) ;
                          (X=yellow , Y=green).

buncertain([X,_,Y]) :-  ((X=green , Y=red) ;
                          (X=green , Y=yellow) ;
                          (X=green , Y=green) ;
                          (X=red , Y=yellow) ;
                          (X=red , Y=green) ;
                          (X=yellow , Y=red) ;
                          (X=yellow , Y=green)),
			  (auncertain([X,green,Y]),
			   auncertain([X,yellow,Y]),
			   auncertain([X,red,Y])).



goal(Color,Combinations) :-
	                   Combinations = [_,_,Color],
                           auncertain(Combinations),
                           buncertain(Combinations).



%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%           Problem-3
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%


accRev([H|T],A,R):-  accRev(T,[H|A],R).
accRev([],A,A).
rev(L,R):-  accRev(L,[],R). 

limit(X,Y) :- X > 0 , Y > 0 ,  X < 8 , Y < 8.

move(pair(R,C),pair(X,Y)) :- X is R + 2 , Y is C + 1 , limit(X,Y).
move(pair(R,C),pair(X,Y)) :- X is R + 2 , Y is C - 1 , limit(X,Y).
move(pair(R,C),pair(X,Y)) :- X is R - 2 , Y is C + 1 , limit(X,Y).
move(pair(R,C),pair(X,Y)) :- X is R - 2 , Y is C - 1 , limit(X,Y).
move(pair(R,C),pair(X,Y)) :- X is R + 1 , Y is C + 2 , limit(X,Y).
move(pair(R,C),pair(X,Y)) :- X is R + 1 , Y is C - 2 , limit(X,Y).
move(pair(R,C),pair(X,Y)) :- X is R - 1 , Y is C + 2 , limit(X,Y).
move(pair(R,C),pair(X,Y)) :- X is R - 1 , Y is C - 2 , limit(X,Y).


help(A,L,[A|L]).
help(CurrPos,CurrList,R) :- move(CurrPos,NextPos),
                            not(member(NextPos,CurrList)),
                            help(NextPos,[CurrPos|CurrList],R).

tour(Res) :- length(R, 49),
             help(pair(1,1),[],R),
             rev(R,Res),
	     write(Res).
             

 
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%           Problem-4
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%            


limits(Mleft,Cleft,Mright,Cright) :-
                                     Mleft>=0,
                                     Cleft>=0, 
                                     Mright>=0, 
                                     Cright>=0,
                                     (Mright>=Cright ; Mright=0),
                                     (Mleft>=Cleft ; Mleft=0).



shift([Mleft,Cleft,right,Mright,Cright],[Mleft2,Cleft,left,Mright2,Cright]):-
                                                                               Mleft2 is Mleft+1,
                                                                               Mright2 is Mright-1,
                                                                               limits(Mleft2,Cleft,Mright2,Cright).

shift([Mleft,Cleft,right,Mright,Cright],[Mleft,Cleft2,left,Mright,Cright2]):-
                                                                               Cleft2 is Cleft+2,
                                                                               Cright2 is Cright-2,
                                                                               limits(Mleft,Cleft2,Mright,Cright2).

shift([Mleft,Cleft,right,Mright,Cright],[Mleft,Cleft2,left,Mright,Cright2]):-
                                                                               Cleft2 is Cleft+1,
                                                                               Cright2 is Cright-1,
                                                                               limits(Mleft,Cleft2,Mright,Cright2).

shift([Mleft,Cleft,right,Mright,Cright],[Mleft2,Cleft,left,Mright2,Cright]):-
                                                                               Mleft2 is Mleft+2,
                                                                               Mright2 is Mright-2,
                                                                               limits(Mleft2,Cleft,Mright2,Cright).


shift([Mleft,Cleft,right,Mright,Cright],[Mleft2,Cleft2,left,Mright2,Cright2]):-
                                                                               Mleft2 is Mleft+1, 
                                                                               Cleft2 is Cleft+1,
                                                                               Cright2 is Cright-1,
                                                                               Mright2 is Mright-1,
                                                                               limits(Mleft2,Cleft2,Mright2,Cright2).


shift([Mleft,Cleft,left,Mright,Cright],[Mleft,Cleft2,right,Mright,Cright2]):-
                                                                               Cleft2 is Cleft-2,
                                                                               Cright2 is Cright+2,
                                                                               limits(Mleft,Cleft2,Mright,Cright2).

shift([Mleft,Cleft,left,Mright,Cright],[Mleft2,Cleft,right,Mright2,Cright]):-
                                                                               Mleft2 is Mleft-1,
                                                                               Mright2 is Mright+1,
                                                                               limits(Mleft2,Cleft,Mright2,Cright).

shift([Mleft,Cleft,left,Mright,Cright],[Mleft,Cleft2,right,Mright,Cright2]):-
                                                                               Cleft2 is Cleft-1,
                                                                               Cright2 is Cright+1,
                                                                               limits(Mleft,Cleft2,Mright,Cright2).

shift([Mleft,Cleft,left,Mright,Cright],[Mleft2,Cleft,right,Mright2,Cright]):-
                                                                               Mleft2 is Mleft-2,
                                                                               Mright2 is Mright+2,
                                                                               limits(Mleft2,Cleft,Mright2,Cright). 

shift([Mleft,Cleft,left,Mright,Cright],[Mleft2,Cleft2,right,Mright2,Cright2]):-
                                                                               Cleft2 is Cleft-1,
                                                                               Mright2 is Mright+1,
                                                                               Cright2 is Cright+1,
                                                                               Mleft2 is Mleft-1,
                                                                               limits(Mleft2,Cleft2,Mright2,Cright2).




helper([Mleft1,Cleft1,B1,Mright1,Cright1],[Mleft2,Cleft2,B2,Mright2,Cright2],Final) :- 
                                     shift([Mleft1,Cleft1,B1,Mright1,Cright1],[Mleft3,Cleft3,B3,Mright3,Cright3]),
                                     not(member([Mleft3,Cleft3,B3],Final)),
                                     helper([Mleft3,Cleft3,B3,Mright3,Cright3],[Mleft2,Cleft2,B2,Mright2,Cright2],[[Mleft3,Cleft3,B3]|Final]).



helper([Mleft,Cleft,B,Mright,Cright],[Mleft,Cleft,B,Mright,Cright],Final) :-
                                                                              length(Result, 12),
	                                                                      rev(Result,Final),
	                                                                      write(Result).


helpere(True).


safe(Ans) :-helper([3,3,left,0,0],[0,0,right,3,3],[[3,3,left]]),
            helpere(Ans).
