

%reversing module taken from learnprolognow.
accRev([H|T],A,R):-  accRev(T,[H|A],R).
accRev([],A,A).
rev(L,R):-  accRev(L,[],R). 



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
