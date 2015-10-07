#include "std.h"

object vampire;

extra_reset() {
    object treasure;
    if (!vampire || !living(vampire)) {
	vampire = clone_object("obj/monster");
	call_other(vampire, "set_name", "vampire");
	call_other(vampire, "set_alias", "undead");
	call_other(vampire, "set_level", 17);
	call_other(vampire, "set_short", "A vampire");
	call_other(vampire, "set_wc", 20);
	call_other(vampire, "set_ac", 7);
	call_other(vampire, "set_al", -500);
	call_other(vampire, "set_aggressive", 1);
	move_object(vampire, this_object());
	treasure = clone_object("obj/treasure");
	call_other(treasure, "set_id", "ring");
	call_other(treasure, "set_alias", "gold ring");
	call_other(treasure, "set_short", "A gold ring");
	call_other(treasure, "set_weight", 1);
	call_other(treasure, "set_value", 2000);
	move_object(treasure, vampire);
    }
}

#undef EXTRA_RESET
#define EXTRA_RESET\
    extra_reset();

ONE_EXIT("players/morgar/slimeworld/crypt4", "south",
	 "In a dank, dark crypt",
	 "You are in the crypt under the ruined temple.  There are several\n" +
         "empty coffins lying around.\n", 0)

realm() {
    return("slime");
}
