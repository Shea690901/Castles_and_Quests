/*
 *  tower/tower1.c
 *	On Nanny, we can go down from here, and "fall out of the game"!
 *	Latest change of this file: Jan 25, 1991.
 */

#include "std.h"
#include "../config.h"

/* This is to load the waiting room, since the door is created there: */
#undef EXTRA_RESET
#define EXTRA_RESET \
	if (!arg) call_other("players/padrone/inside/waitingroom", "short");

#ifdef NANNY

#undef EXTRA_MOVE2
#define EXTRA_MOVE2	extra_down(); return 1;

extra_down() {
    write("Could not load descr for players/padrone/inside/under_tower.c\n");
    write("Current object was obj/player95/, line 119\n");
    write("Anomaly in the fabric of world space.\n");
    move_object(this_player(), "players/padrone/my_void");
} /* extra_down */

TWO_EXIT("players/padrone/tower/tower2", "up",
	 "players/padrone/my_void", "down",
	 "Inside Padrone's private tower",
	 "You are at the bottom of Padrone's private tower.\n" +
	 "This is a circular room with walls and floor made of stone.\n" +
	 "It is dark and a bit damp, and you can see a stone staircase\n" +
	 "winding its way up through the darkness. Another staircase\n" +
	 "leads down into a dark hole in the floor.\n", 0)

#else

ONE_EXIT("players/padrone/tower/tower2", "up",
	 "Inside Padrone's private tower",
	 "You are at the bottom of Padrone's private tower.\n" +
	 "This is a circular room with both walls and floor made of stone.\n" +
	 "It is dark and a bit damp, and you can see a stone staircase\n" +
	 "winding its way up through the darkness.\n", 0)

#endif

