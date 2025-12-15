read_from_file(File):-
    open(File, read, Stream),
    get_char(Stream,Ch),
    process_the_stream(Ch,Stream),
    close(Stream).

process_the_stream(end_of_file, _):- !.

process_the_stream(Ch,Stream):-
    write(Ch),
    get_char(Stream,Ch2),
    process_the_stream(Ch2,Stream).


write_in_file(File, Val):-
    open(File, write, Stream),
    write(Stream, Val), nl(Stream),
    write('Saved in C:Documents/Prolog/'), write(File), nl ,
    close(Stream).


q1:-
    write('Enter value of X: '),
    read(X),
    write('Enter value of Y: '),
    read(Y),
    write('Enter value of Z: '),
    read(Z),
    solveQ1(X,Y,Z).

solveQ1(_,_,Z):-
    Z == 0 , write('Infinity occured!'), nl, !.

solveQ1(X,Y,Z):-
    number(X), number(Y), number(Z),
    R1 is X ^ ( Y ^ Z ),
    Res is R1 / Z,
    write_in_file('q1.txt', Res),
    read_from_file('q1.txt').


q2:-
    write('Enter value of X: '),
    read(X),
    write('Enter value of Y: '),
    read(Y),
    write('Enter value of Z: '),
    read(Z),
    solveQ2(X,Y,Z).

solveQ2(X,Y,Z):-
    number(X), number(Y), number(Z),
    Chk is X * Y * Z , Chk == 0 ,
    write('Infinity occured!'), nl, !.

solveQ2(X,Y,Z):-
    number(X), number(Y), number(Z),
    R1 is ( X ^ Y ) * ( Y ^ Z ) * ( Z ^ X ),
    R2 is X * Y * Z,
    Res is R1 / R2,
    write_in_file('q2.txt', Res),
    read_from_file('q2.txt').



