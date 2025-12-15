fruit(apple).
fruit(orange).
fruit(mango).
fruit(banana).
fruit(grapes).

likes(jack, X):- fruit(X) , X \= banana.
likes_2(jack, X) :- fruit(X), \+ X = banana.

likes_3(jack, X):- X = banana, !, fail. % Must do this base-case 1st as prolog runs in order hence will give true.
likes_3(jack, X):- fruit(X).
