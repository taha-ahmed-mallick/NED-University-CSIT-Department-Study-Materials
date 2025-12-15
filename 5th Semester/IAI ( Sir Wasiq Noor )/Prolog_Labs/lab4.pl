my_atom(abc123).
my_atom(patrick_123).
my_atom(gayle_333).
my_atom(camp_nou).
my_atom('Atom with Spaces').
my_atom([]).         % Empty list atom

my_num(42).
my_num(3.1415926535897932384626433832795).  % Write upto 16-fr.
my_num(-87).
my_num(07).
my_num(-10).

my_var(X) :- number(X), X > 0, X < 200.
% Other variables can be Y,X_1, MyVal.
%my_var(X) :- number(X), X < 0, X > -100.
%my_var(X) :- number(X), X =:= 0.
%my_var(X) :- number(X), X > 100, X < 150.
%my_var(X) :- number(X), X > 999, X < 5000.

person(name('Doue'), age(19)).
person(name('Jack'), age(25)).
person(name('Alison'), age(35)).
person(name('BobTheBuilder'), age(12)).
person(name('Emily'), age(29)).

book(title('The C++ Programming Language'), author('Bjarne Stroustrup'), year(2013)).
book(title('The Prisoner of Zenda'), author('Anthony Hope'), year(1894)).
book(title('Artificial Intelligence: A Modern Approach'), author('Stuart Russell'), year(2020)).
book(title('The Art of Computer Programming'), author('Donald Knuth'), year(1968)).
book(title('Clean Code'), author('Robert Martin'), year(2008)).


query_atom :-  write('ATOMS: '), nl, my_atom(Atom),  write('Atom: '), write(Atom), nl.
query_number :- write('NUMBERS: '), nl, my_num(Number), write('Number: '), write(Number), nl.
query_variable(X) :- write('VARIABLES: '), nl, my_var(X),write('Variable value: '), write(X), nl.
query_person :- write('PEOPLE (Structures): '), nl, person(name(Name), age(Age)),write('Person: '), write(Name), write(', Age: '), write(Age), nl.
query_book :- write('BOOKS (Structures): '), nl, book(title(Title), author(Author), year(Year)), write('Book: '), write(Title), write(', Author: '), write(Author), write(', Year: '), write(Year), nl.

query_person2 :-
    write('PEOPLE (Structures): '), nl,
    listing(person).

query_person3 :-
    write('PEOPLE (Structures): '), nl,
    person(Name, Age), %1st fetch then write.
    write(person(Name, Age)), nl.





