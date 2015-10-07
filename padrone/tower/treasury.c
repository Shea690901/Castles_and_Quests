#include "std.h"
#include "../../../obj/door.h"

object obj_1, obj_2;	/* Used by the MAKE_DOORS macro */

#undef EXTRA_RESET
#define EXTRA_RESET extra_reset(arg);

extra_reset(arg) {

    if (!arg) {
	/* First reset */

	MAKE_DOORS("players/padrone/tower/treasury", "north",
		   "players/padrone/tower/vault", "south",
		   "maximum-security", "vaultdoor",
		   "This is a door made of steel and mithril, several inches thick.\n",
		   1, 1, 1)
	return;
    }

    obj_1->set_closed(1);
    obj_1->set_locked(1);
    obj_1->set_both_status();
} /* extra_reset */


TWO_EXIT("players/padrone/tower/rambo_room", "south",
	 "players/padrone/tower/vault", "north",
	 "Treasury",
	 "You are standing just outside the great door\n" +
	 "leading to the vault where the treasure is stored.\n" +
	 "You notice that the floor has been engraved with anti-teleport runes.\n", 1)

/* This room is teleport-safe */
realm() { return "NT"; }
