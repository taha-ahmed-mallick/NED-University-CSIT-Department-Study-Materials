age(aslam, 11).
age(asif, 13).
age(afsheen, 17).
age(manal, 16).
age(manal2, 16).
age(amir, 30).
age(falak, 33).
age(sobia, 40).
age(sheheryar, 44).
age(rehan, 52).
age(erum, 64).

older_than(X, Y) :- age(X, AgeX), age(Y, AgeY), AgeX > AgeY.
younger_than(X, Y) :- age(X, AgeX), age(Y, AgeY), AgeX < AgeY.
same_age(X, Y) :- age(X, AgeX), age(Y, AgeY), AgeX == AgeY.