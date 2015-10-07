#include "std.h"

#if 0 /* This passage was never finished by Quantos and players */
      /* would get stuck if they entered it. /Pell */
#undef EXTRA_INIT
#define EXTRA_INIT\
    extra_init();

extra_init() {
    add_action ("east"); add_verb ("east");
}

east() {
    write ("You stumble into a secret passage!\n");
    call_other (this_player(), "move_player", "east#players/quantos/under/side1");
    return 1;
}

#endif				/* Pell */

THREE_EXIT ("players/quantos/under/maze283", "north",
	    "players/quantos/under/maze281", "south",
	    "players/quantos/under/maze258", "west",
	    "In the labyrinth",
	    "You are in the labyrinth under the plateau.\n", 0)
