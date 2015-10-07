#include "std.h"


object slug1, slug2;

extra_reset() {
    if (!slug2 || !living(slug2)) {
	slug2 = clone_object("obj/monster");
	call_other(slug2, "set_name", "slime puddle");
	call_other(slug2, "set_alias", "puddle");
	call_other(slug2, "set_level", 14);
        call_other(slug2, "set_hp", 150);
	call_other(slug2, "set_short", "A puddle of slime");
	call_other(slug2, "set_wc", 12);
	call_other(slug2, "set_ac", 4);
	call_other(slug2, "set_al", -350);
	call_other(slug2, "set_aggressive", 1);
	move_object(slug2, this_object());
    }
    if (!slug1 || !living(slug1)) {
	slug1 = clone_object("obj/monster");
	call_other(slug1, "set_name", "slug");
	call_other(slug1, "set_alias", "slime slug");
	call_other(slug1, "set_level", 14);
        call_other(slug1, "set_hp", 150);
	call_other(slug1, "set_short", "A slime slug");
	call_other(slug1, "set_wc", 12);
	call_other(slug1, "set_ac", 4);
	call_other(slug1, "set_al", -350);
	call_other(slug1, "set_aggressive", 1);
	move_object(slug1, this_object());
    }
}

#undef EXTRA_RESET
#define EXTRA_RESET\
    extra_reset();

THREE_EXIT("players/morgar/slimeworld/entry", "north",
         "players/morgar/slimeworld/desolate_s", "east",
         "players/morgar/slimeworld/under", "in",
	 "Pit of the slime things",
	 "You are at a huge lake of slime, filled with disgusting things.\n" +
         "From here it is possible to go down into the slime.\n", 1)


realm() {
    return("slime");
}
