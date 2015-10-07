#include "std.h"

#undef EXTRA_RESET
#define EXTRA_RESET\
    if (!present("globule"))\
        move_object(clone_object("players/morgar/slimeworld/globule"), this_object());

THREE_EXIT("players/morgar/slimeworld/desolate_2n", "north",
	 "players/morgar/slimeworld/desolate_2s", "south",
	 "players/morgar/slimeworld/desolate", "west",
	 "The slime plain",
	 "You are in a vast plain, covered with dried slime.  The plain\n" +
         "seems to stretch on and on, with nothing of note except for the\n" +
         "stuff near the mirror to the west.\n", 1)

realm() {
    return("slime");
}
