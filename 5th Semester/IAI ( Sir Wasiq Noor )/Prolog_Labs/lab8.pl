% Muhammad Obaid
% CT-23025   Section-A  (Lab-8)

member(X, [X|_]).
member(X, [_|Tail]) :- member( X , Tail ). %Member of tail anywhere.
% member( [_, [1,2,3]] ). means that list has atleast one element as _
% is an anonymous variable, also called a don’t-care variable.

% member(_,[_]). Is there some element that is a member of some list?

%length([],0). % Wrong as length is builtin-predicate.
list_length([],0).
list_length([_|Tail], N):- list_length(Tail, N1), N is N1 + 1.

list_print([]).
list_print([H|T]):- write(H), nl, list_print(T). % Give 'T' not [T] as then it would keep on printing [] as empty list of empty list.

reverse_print([]).
reverse_print([H|T]):- reverse_print(T), format('~w ',[H]).
