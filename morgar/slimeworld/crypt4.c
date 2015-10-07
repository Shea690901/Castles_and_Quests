#include "std.h"

object skeleton, zombie;

extra_reset() {
    object treasure;
    if (!zombie || !living(zombie)) {
	zombie = clone_object("obj/monster");
	call_other(zombie, "set_name", "zombie");
	call_other(zombie, "set_alias", "undead");
	call_other(zombie, "set_level", 8);
        call_other(zombie, "set_hp", 70);
	call_other(zombie, "set_short", "A zombie");
	call_other(zombie, "set_wc", 7);
	call_other(zombie, "set_ac", 5);
	call_other(zombie, "set_al", -200);
	call_other(zombie, "set_aggressive", 1);
	move_object(zombie, this_object());
	treasure = clone_object("obj/treasure");
	call_other(treasure, "set_id", "chain");
	call_other(treasure, "set_alias", "gold chain");
	call_other(treasure, "set_short", "A gold chain");
	call_other(treasure, "set_weight", 1);
	call_other(treasure, "set_value", 200);
	move_object(treasure, zombie);
    }
    if (!skeleton || !living(skeleton)) {
        skeleton = clone_object("obj/monster");
        call_other(skeleton, "set_name", "skeleton");
        call_other(skeleton, "set_alias", "undead");
        call_other(skeleton, "set_level", 8);
        call_other(skeleton, "set_hp", 70);
        call_other(skeleton, "set_short", "A skeleton");
        call_other(skeleton, "set_wc", 7);
        call_other(skeleton, "set_ac", 5);
        call_other(skeleton, "set_al", -200);
        call_other(skeleton, "set_aggressive", 1);
        move_object(skeleton, this_object());
        treasure = clone_object("obj/treasure");
        call_other(treasure, "set_id", "ring");
        call_other(treasure, "set_alias", "gold ring");
        call_other(treasure, "set_short", "A gold ring");
        call_other(treasure, "set_weight", 1);
        call_other(treasure, "set_value", 200);
        move_object(treasure, skeleton);
    }
}

#undef EXTRA_RESET
#define EXTRA_RESET\
    extra_reset();

TWO_EXIT("players/morgar/slimeworld/crypt2", "south",
         "players/morgar/slimeworld/crypt5", "north",
	 "In a dank, dark crypt",
	 "You are in the crypt under the ruined temple.  There are several\n" +
         "empty coffins lying around.\n", 0)

realm() {
    return("slime");
}
