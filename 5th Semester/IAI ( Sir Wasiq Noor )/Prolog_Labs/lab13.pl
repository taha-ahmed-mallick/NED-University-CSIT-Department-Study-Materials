bubble_sort(InputList, SortList) :-
    swap(InputList, List),
    !,
    printlist(List), nl,
    bubble_sort(List, SortList).

bubble_sort(SortList, SortList). % This condition so that in the end true is returned.

swap( [X, Y | List], [Y, X | List] ) :-  X > Y.
swap( [Z | List], [Z | List1] ) :- swap(List, List1).

printlist( [] ) :- !.
printlist( [H | T]) :- write(H), write(','), printlist(T).


insertion_sort([], []).
insertion_sort([H|T], Sorted) :-
    insertion_sort(T, SortedTail),
    insert(H, SortedTail, Sorted),
    printlist(Sorted), nl.


insert(X, [], [X]) :- !.
insert(X, [H|T], [X , H|T]) :- X =< H, !.
insert(X, [H|T], [H|T1]) :-
    insert(X, T, T1).


selection_sort([], []).
selection_sort(List, [Min|SortedTail]) :-
    select_min(List, Min, Rest),
    selection_sort(Rest, SortedTail), !.

select_min([X], X, []).
select_min([H|T], Min, [H|Rest]) :-
    select_min(T, MinT, Rest),
    MinT < H, !,                                   % If tail's min is smaller, keep H in Rest
    Min = MinT.
select_min([H|T], H, T).                           % Otherwise H is the minimum
