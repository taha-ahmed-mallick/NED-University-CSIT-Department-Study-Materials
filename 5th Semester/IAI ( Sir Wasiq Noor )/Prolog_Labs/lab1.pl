parent(a,b).
parent(a,c).
parent(p,q).
parent(p,e).
parent(z,a).
parent(z,p).
prerequisite(oops,pf).
prerequisite(dsa,oops).
prerequisite(cao,ldst).

sibling(X,Y):-parent(Z,X),parent(Z,Y),X\=Y.
cousin(X,Y):-parent(A,X),parent(B,Y),sibling(A,B).
grandparent(GP,GC):- parent(GP, P), parent(P, GC).
required_before(X, Y) :- prerequisite(X, Y).
required_before(X, Y) :- prerequisite(X, Z), required_before(Z, Y).
