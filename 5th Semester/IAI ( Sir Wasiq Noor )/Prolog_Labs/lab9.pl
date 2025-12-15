list_concat([], L2, L2). %Result should be 'L2' if it is alone NOT Res.
list_concat([H|T], L2, [H|ResTail]):- list_concat(T, L2, ResTail).

interm(0,zero).
interm(1,one).
interm(2,two).
interm(3,three).
interm(4,four).
interm(5,five).
interm(6,six).
interm(7,seven).
interm(8,eight).
interm(9,nine).
inwords([], []).
inwords([H|Tail], [T|Z]):- interm(H, T), inwords(Tail, Z).

%del(X, [X], []). % Tail/Last deletion
del(X, [X|L] , L). % Head/Any deletion. Will work without 1st case also as it will cover both.
del(X, [Y|Tail], [Y|L1]):- del(X, Tail, L1). %Found 'Y' so ignore.

delAll(_, [], []).
delAll(X, [X|L], Res):- delAll(X, L ,Res).
delAll(X, [Y|L], [Y|L2]):- delAll(X, L, L2), !.

% list_append(A, [A | T], [A | T]) :- !. % if head already A, stop
% avoiding duplicates, copy same oldList.
list_append(A, [H | T], [H | R]) :- list_append(A, T, R), !. %! avoid using Enter key another time.
list_append(A, [], [A]).

%built-in deterministic
%insert_head(X, T , T):- memberchk(X, T), !. % Avoid dups.
insert_head(X, T, [X|T]). %Mistake 'X' should be the new-head NOW.

list_insert(A, L, R):- del(A, R, L). %A will be inserted into L giving R if deleting A from R gives L.It will give all permutations if 1st base case of del is removed without last empty duplicate. USE ';' for more answers.

list_reverse([], []).
% list_reverse([H|T], Rev) :- list_reverse(T, RevT), list_concat(RevT,
% [H], Rev). % Reverse the tail T and store that reversed list in RevT.
% Using [Rev|T] will have head as X (still unbound)

% reverse using append as insert all at last from tail.
list_reverse([H|T], Rev):- list_reverse(T, RevT), list_append(H, RevT, Rev).