[user].

go:-
write('Enter your name: '),
read(Name),
recommend(Phone),
write_list([' can get ',Phone,' . ']),nl.

go:-
write('Phone for your specification'),nl,
write('cannot be found.'),nl.

check_Price(Price):-
write('Enter Price : '),
read(Pricee),
Pricee>=Price.

check_Camera(Cam):-
write('Do you want quad Camera?(yes/no)'),
read(Cam),
Cam=yes.

check_Battery(Battery):-
write('Do you want a 6000mAh Battery?'),
read(Battery),
Battery=yes.


check_Storage(Storage):-
write('Enter the Storage space(64/128/256) :'),
read(Storage),
Storage>64.


check_Ram(Ram):-
write('Enter the Ram(4/8/12) :'),
read(Ram),
Ram>4.


recommend('Galaxy S22'):-
%check_Price(95000),
check_Camera(Cam),
\+check_Battery(Battery),
check_Storage(Storage),
check_Ram(Ram).

recommend('Galaxy F13'):-
% \+check_Price(10400),
\+check_Camera(Cam),
check_Battery(Battery),
\+check_Storage(Storage),
\+check_Ram(Ram).

recommend('Galaxy A72'):-
% \+check_Price(29000),
check_Camera(Cam),
\+check_Battery(Battery),
check_Storage(Storage),
check_Ram(Ram).

recommend('Galaxy M32'):-
% \+check_Price(11000),
check_Camera(Cam),
check_Battery(Battery),
\+check_Storage(Storage),
\+check_Ram(Ram).

recommend('Galaxy Z Fold 3'):-
%check_Price(95500),
\+check_Camera(Cam),
\+check_Battery(Battery),
check_Storage(Storage),
check_Ram(Ram).

write_list([]).
write_list([X|Rest]):-
write(X),
write_list(Rest).

response(Reply):-
get_single_char(Code),
put_code(Code),nl,
char_code(Reply,Code).