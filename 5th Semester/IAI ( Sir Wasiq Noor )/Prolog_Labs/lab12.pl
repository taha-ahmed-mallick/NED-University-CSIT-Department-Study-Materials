% Muhammad Obaid
% CT-23025  Section-A (Lab-12)

country_save :-
    write('Enter country names one by one. Type "done." when finished.'), nl,
    open('sample.txt', write, Stream),
    write_countries(Stream),
    close(Stream),
    nl, write('Countries saved. Now reading...'), nl,
    open('sample.txt', read, ReadStream),
    read_countries(ReadStream),
    close(ReadStream).

write_countries(Stream) :-
    write('Enter country: '),
    read_line_to_string(user_input, Country),
    ( Country == "done" -> true
    ; write(Stream, ''''), write(Stream, Country), write(Stream, '''.'), nl(Stream),
      write_countries(Stream)
    ).

read_countries(Stream) :-
    read(Stream, Country),
    ( Country == end_of_file -> true
    ; write('Country: '), write(Country), nl,
      read_countries(Stream)
    ).


read_from_file:-
    open('hogwarts.txt', read, Stream),
    get_char(Stream,Char1),
    process_the_stream(Char1,Stream),
    close(Stream).

process_the_stream(end_of_file, _):- !.
process_the_stream(Char,Stream):-
    write(Char),
    get_char(Stream,Char2),
    process_the_stream(Char2,Stream).

save_output :-
    write('Write any number to save. Type done to finish'), nl,
    open('pr.txt', write, Stream),
    write_nums(Stream),
    close(Stream), nl,
    write('Saved nums are:'), nl,
    open('pr.txt', read, ReadStream),
    read_nums(ReadStream),
    close(ReadStream).

write_nums(Stream) :-
    write('Enter num: '),
    read_line_to_string(user_input, X),

    (   string_lower(X, Lower), Lower == "done"
    ->  true
    ;   \+ number_string(_, X), !;

        write(Stream, ''''),
        write(Stream, X),
        write(Stream, '''.'),
        nl(Stream),
        write_nums(Stream)
    ).

read_nums(Stream) :-
    read(Stream, X),
    (   X == end_of_file
    ->  true
    ;   write('X = '), write(X), nl,
        read_nums(Stream)
    ).
