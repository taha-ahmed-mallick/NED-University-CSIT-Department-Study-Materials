
% Students(SID, Name, Major)
student(1, 'Alice', cs).
student(2, 'Bob', math).
student(3, 'Charlie', cs).
student(4, 'Diana', physics).

% Courses(SID, Course, Grade)
course(1, compilers, a).
course(1, algorithms, b).
course(2, calculus, a).
course(3, compilers, c).
course(4, quantum, b).


% SELECT
select_student_major(Major, SID, Name) :-
    student(SID, Name, Major).

% PROJECT
project_student_name(Name) :-
    student(_, Name, _).

% JOIN
student_course_join(Major, Course, Name, Grade) :-
    student(SID, Name , Major),
    course(SID, Course, Grade).

set1(a).
set1(b).
set2(b).
set2(c).

% UNION ; call() for dynamic predicate passing
union_sets(Rel1, Rel2, X) :-
    call(Rel1, X);
    call(Rel2, X).

% SET DIFFERENCE
set_difference(Rel1, Rel2, X) :-
    call(Rel1, X),
    \+ call(Rel2, X).

% CARTESIAN PRODUCT
cartesian(Rel1, Rel2, X-Y) :-
    call(Rel1, X),
    call(Rel2, Y).

% ?- P = even, call(P, X).
even(2).
even(4).
odd(1).
odd(3).
