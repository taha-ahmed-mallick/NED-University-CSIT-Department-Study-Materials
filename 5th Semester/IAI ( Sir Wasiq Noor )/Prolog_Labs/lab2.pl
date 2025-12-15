ring(Person, Number) :- location(Person, Place), phone_number(Place, Number).
location(Person, Place) :- at(Person, Place).
location(Person,Place) :- visiting(Person, Someone), location(Someone, Place).

phone_number(rm303g, 5767).
phone_number(rm303a, 5949).
at(dr_jones, rm303g).
at(dr_mike, rm303a).
visiting(dr_mike, dr_jones).
