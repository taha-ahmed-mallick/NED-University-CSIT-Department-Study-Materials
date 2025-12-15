%    Muhammad_Obaid
%    CT-23025     ( Lab-3 )

male(babar).
male(talib).
female(parveen).
female(lubna).
%parent(parveen,babar).
%parent(talib,babar).
%parent(talib,lubna).
%parent(parveen,lubna).

mother(X,Y):-parent(X,Y),female(X).
father(X,Y):-parent(X,Y),male(X).
sister(S,B):-parent(X,S),parent(X,B),female(S),S\=B.
brother(B,S):-parent(X,S),parent(X,B),male(B),S\=B.


%    Muhammad_Obaid
%    CT-23025     ( Lab-3 )

parent(1,2).
parent(1,3).
parent(2,4).
parent(3,5).
parent(4,6).
parent(5,7).
parent(6,8).
parent(7,9).
parent(8,10).
parent(9,11).
parent(2,12).
parent(12,13).
parent(13,14).
parent(14,15).

sibling(A,B):-parent(X,A),parent(X,B),A\=B.
cousin(A,B):-parent(X,A),parent(Y,B),sibling(X,Y).
sec_cousin(A,B):-parent(X,A),parent(Y,B),cousin(X,Y).
third_cousin(A,B):-parent(X,A),parent(Y,B),sec_cousin(X,Y).
fourth_cousin(A,B):-parent(X,A),parent(Y,B),third_cousin(X,Y).

grandparent(A,B):-parent(X,B),parent(A,X).
great_grandparent(A,B):-parent(X,B),grandparent(A,X).
ancestor(A,B):-parent(X,B),great_grandparent(A,X).












