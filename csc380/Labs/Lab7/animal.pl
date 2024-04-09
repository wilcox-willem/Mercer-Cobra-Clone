animal(dog)  :- is_true('has fur'), is_true('says woof').
animal(cat)  :- is_true('has fur'), is_true('says meow').
animal(duck) :- is_true('has feathers'), is_true('says quack').
animal(mouse) :- is_true('is small'), is_true('says squeak').
animal(giraffe) :- is_true('is tall'), is_true('says brrr').
animal(bear) :- is_true('is big'), is_true('says growl').
animal(goose) :- is_true('has feathers'), is_true('says honk').


is_true(Q) :-
        format("~w?\n", [Q]),
        read(yes).

