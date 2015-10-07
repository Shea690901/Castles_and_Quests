/* waitingroom.c -- Nanny version, with an exit to the surgeon's room! */

#include "std.h"
#include "../../../obj/door.h"

object obj_1, obj_2;	/* Used by the MAKE_DOORS macro */

#undef EXTRA_RESET
#define EXTRA_RESET  extra_reset(arg);

extra_reset(arg) {
    if(!arg) {
	/* First reset */

	MAKE_DOORS("players/padrone/inside/waitingroom", "south",
		   "players/padrone/tower/tower1", "north",
		   "crystal", "towerdoor",
		   "This is the door leading from the waiting room to Padrone's private tower.\n" +
		   "It is a thick and solid wooden door, and it has a sign saying 'PRIVATE'.\n",
		   1, 1, 1)
	return;
    }

    obj_1->set_closed(1);
    obj_1->set_locked(1);
    obj_1->set_both_status();
}

TWO_EXIT("players/padrone/inside/main_hall", "west",
	 "players/padrone/inside/cons", "east",
	 "Waiting room",
	 "This is the waiting room, where people who want help or advice\n" +
	 "from the mighty Wizard sit and wait until they are admitted\n" +
	 "to the consultation room to the east.\n" +
	 "Through the door to the west you can see the main hall,\n" +
	 "but there is also a small door to the south.\n" +
	 "There is a sign on that door saying 'PRIVATE!'.\n", 1)
