multiply(X, Y, Result) :-
    Result is X * Y.
    %Result = X * Y. % This is will concat both results. LIKE 5*5

ex1_output :-
    write('Enter 1st number: '),
    read(X),
    write('Enter 2nd number: '),
    read(Y),
    write('Choose an operation (+/*): '),
    read(Operation),

    (Operation = '+' ->
        Result is X + Y,
        write(X), write(' plus '), write(Y), write(' is '), write(Result), nl,
        write('X = '), write(Result), nl;
     Operation = '*' ->
        multiply(X, Y, Result),
        write(X), write(' multiply by '), write(Y), write(' is '), write(Result), nl,
        write('X = '), write(Result), nl;
     write('Invalid operation'), nl).

ex2_table(Number) :-
    forall(
        between(1, 10, Counter),
        (
            Result is Number * Counter,
            format('~w * ~w = ~w~n', [Number, Counter, Result])
        )
    ).

ex3_details :-
    write('Enter your name: '),
    %read(Name),
    read_line_to_string(user_input, Name),
    write('Enter your roll.no: '),
    %read(R_No),
    read_line_to_string(user_input, R_No),
    format('Name: ~w~nRoll No: ~w~n',[Name, R_No]).

% Operator Usage
%   =        Unification   X = '+' Works for variables or matching atoms
%   ==   Strict equality (no variable binding) X == '+' Succeeds only if already exactly equal 
%   =:= Numeric equality (after evaluation) 5 + 2 =:= 7 Only for numbers / arithmetic is Arithmetic evaluation & assignment R is 5 + 2 Evaluates math expressions