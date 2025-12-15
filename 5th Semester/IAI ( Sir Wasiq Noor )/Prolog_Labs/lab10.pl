% Muhammad Obaid
% CT-23025    Section-A  (Lab-10)


check_num( N , pos ):- N > 0 , !. % cut: commit to this branch
check_num( N , neg ):- N < 0 , !.
check_num( N , zero ):- N == 0, !.



