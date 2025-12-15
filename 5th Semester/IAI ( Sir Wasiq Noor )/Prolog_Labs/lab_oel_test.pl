
q1:-
    write('Enter x , y and z : '),
    read(X), read(Y), read(Z),
    V1 is Y * Y * Y * Z,
    V2 is X * X,
    W is V2 + V1,
    write('w = '), write(W), nl.

q2(J, X, P):-
    V3 is J * J,
    P is V3 / X.

q3:-
  write('Enter a Number: '),
  read(X),
  forall(
     between(6, 10, I),
     (
       Res is X * I,
       write(X), write(' x ' ), write(I), write(' = '), write(Res), nl
     )
  ).
