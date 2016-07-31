signal(x1, 1).
signal(x2, 1).
signal(x3, 1).
signal(x4, 1).
signal(x5, 1).


/*****************************************************************/
%# this is for palindrome
%connected(x1,in(1,a1)).
%connected(x5,in(2,a1)).
%connected(x2,in(1,a2)).
%connected(x4,in(2,a2)).
%connected(out(a1), in(1,a3)).
%connected(out(a2), in(1,a4)).
%connected(out(a3),in(1,a5)).
%connected(out(a4),in(2,a5)).
%connected(out(a5),x6).

%no_of_inputs(a1,2).
%no_of_inputs(a2,2).
%no_of_inputs(a3,1).
%no_of_inputs(a4,1).
%no_of_inputs(a5,2).

%type(a1,'XOR').
%type(a2,'XOR').
%type(a3,'NOT').
%type(a4,'NOT').
%type(a5,'AND').

/*************************************************************/
/*
code for majority
*/
connected(x1,in(1,a1)).

connected(out(a1), in(1,a2)).
connected(out(a1), in(1,a3)).
connected(out(a1), in(1,a4)).
connected(out(a1), in(1,a5)).

connected(x1, in(1,a6)).
connected(x1, in(1,a7)).
connected(x1, in(1,a8)).
connected(x1, in(1,a9)).
connected(x1, in(1,a10)).
connected(x1, in(1,a11)).

connected(x5, in(4,a3)).
connected(x5, in(4,a4)).
connected(x5, in(4,a5)).
connected(x5, in(3,a8)).
connected(x5, in(2,a9)).
connected(x5, in(3,a11)).

connected(x2, in(2,a2)).
connected(x2, in(2,a3)).
connected(x2, in(2,a5)).
connected(x2, in(2,a6)).
connected(x2, in(3,a9)).
connected(x2, in(2,a10)).

connected(x3, in(3,a2)).
connected(x3, in(3,a3)).
connected(x3, in(2,a4)).
connected(x3, in(3,a6)).
connected(x3, in(2,a7)).
connected(x3, in(2,a11)).

connected(x4, in(4,a2)).
connected(x4, in(3,a4)).
connected(x4, in(3,a5)).
connected(x4, in(3,a7)).
connected(x4, in(2,a8)).
connected(x4, in(3,a10)).




connected(out(a2), in(1,a12)).
connected(out(a3), in(2,a12)).
connected(out(a4), in(3,a12)).
connected(out(a5), in(4,a12)).
connected(out(a6), in(5,a12)).
connected(out(a7), in(6,a12)).
connected(out(a8), in(7,a12)).
connected(out(a9), in(8,a12)).
connected(out(a10), in(9,a12)).
connected(out(a11), in(10,a12)).

connected(out(a12), x6).

no_of_inputs(a1,1).
no_of_inputs(a2,4).
no_of_inputs(a3,4).
no_of_inputs(a4,4).
no_of_inputs(a5,4).
no_of_inputs(a6,3).
no_of_inputs(a7,3).
no_of_inputs(a8,3).
no_of_inputs(a9,3).
no_of_inputs(a10,3).
no_of_inputs(a11,3).
no_of_inputs(a12,10).

type(a1,'NOT').
type(a2,'AND').
type(a3,'AND').
type(a4,'AND').
type(a5,'AND').
type(a6,'AND').
type(a7,'AND').
type(a8,'AND').
type(a9,'AND').
type(a10,'AND').
type(a11,'AND').
type(a12,'OR').


/*---------------------------------------------------------------*/

count_1s(X,0,Y, Acc) :- Y is Acc.
count_1s(X, N, Y, Acc) :- in(N, X, Val), ==(Val, 1), M is N-1, Acc1 is Acc+1, count_1s(X, M, Y, Acc1 ).
count_1s(X, N, Y, Acc) :- in(N, X, Val), ==(Val, 0),M is N-1, count_1s(X, M, Y, Acc).


/*----------------------------------------------------------------*/

signal(X,Val) :-connected(out(Y),X),
		out(Y,Val).

in(N,X,Val) :-  connected(Y, in(N,X)), 
		signal(Y,Val). 
		
in(N,X,Val) :-  connected(out(Y), in(N,X)), 
		out(Y,Val).		


/*in(N,X,Val) :- ( connected(in(N,X), out(Y)) ; connected(out(Y), in(N,X)) ), 
		out(Y,Val).*/

/*-----------------------------------------------------------------*/

out(X,Val) :- type(X, 'OR'), no_of_inputs(X,N) , >(N,1), count_1s(X, N , Y, 0), >(Y,0), Val is 1.
out(X,Val) :- type(X, 'OR'), no_of_inputs(X,N) , >(N,1), count_1s(X, N , Y, 0), ==(Y,0), Val is 0.

out(X,Val) :- type(X, 'NOT'), no_of_inputs(X,N) , ==(N,1), count_1s(X, N , Y, 0), ==(Y,0), Val is 1. 	
out(X,Val) :- type(X, 'NOT'), no_of_inputs(X,N) , ==(N,1), count_1s(X, N , Y, 0), ==(Y,1), Val is 0.

out(X,Val) :- type(X, 'AND'), no_of_inputs(X,N) , >(N,1), count_1s(X, N , Y, 0), ==(Y,N), Val is 1.
out(X,Val) :- type(X, 'AND'), no_of_inputs(X,N) , >(N,1), count_1s(X, N , Y, 0), <(Y,N), Val is 0.

out(X,Val) :- type(X, 'XOR'), no_of_inputs(X,N) , >(N,1), count_1s(X, N , Y, 0), Val is Y mod 2.


/*-----------------------------------------------------------------*/

/*not sure
type(X, 'OR'):- no_of_inputs(X,N) , 
		count_1s(X, N , Y, 0), 
		>(Y,0), 
		out(X,1).

*/


