#include "walker.h"

#include "std.h"
#include "../../../obj/door.h"

object obj_1, obj_2;	/* Used by the MAKE_DOORS macro */

#undef EXTRA_RESET
#define EXTRA_RESET  extra_reset(arg);

extra_reset(arg) {
    if(!arg) {
	/* First reset */

	MAKE_DOORS("players/padrone/walker/upper_hall", "north", "players/padrone/walker/vault", "south", "bullet-proof", "walkervault", "This is a solid-looking metal door.\nMaybe it leads to a vault of some sort?\nThere is a big sign on the door, saying \"NO ENTRANCE! KEEP OUT!\".\n", 1, 1, 1)
	return;
    }

    obj_1->set_closed(1);
    obj_1->set_locked(1);
    obj_1->set_both_status();
} /* extra_reset */

FOUR_EXIT("players/padrone/walker/bedroom", "east",
	  "players/padrone/walker/walkway", "south",
	  "players/padrone/walker/main_hall", "down",
	  "players/padrone/walker/loft", "up",
	  "Upper hall of the walking castle",
	  "You are in the upper hall of the walking castle.\n" +
	  "To the east you see a door leading into a bedroom,\n" +
	  "and to the south a walkway leads above the castle yard\n" +
	  "to a room with many windows.\n" +
	  "Stairs go up and down.\n", 1)
