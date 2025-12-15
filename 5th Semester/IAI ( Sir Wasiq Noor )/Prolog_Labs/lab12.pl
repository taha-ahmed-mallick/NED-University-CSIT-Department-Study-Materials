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