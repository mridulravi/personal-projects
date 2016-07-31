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
                            