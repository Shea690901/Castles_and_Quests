#include "std.h"

#undef EXTRA_RESET

#define EXTRA_RESET extra_reset();

object mirror;

FOUR_EXIT("players/morgar/slimeworld/mound", "north",
	 "players/morgar/slimeworld/pool", "south",
	 "players/morgar/slimeworld/desolate", "east",
	 "players/morgar/slimeworld/pillars", "west",
	 "A sloping path",
	 "You are on a path sloping down to the south.  There are large\n" +
	 "numbers of slimy trails here.\n", 1)

extra_reset() {
    if (!mirror) {
        mirror = clone_object("players/morgar/mirror");
        call_other(mirror, "roomset", this_object());
        move_object(mirror, "players/morgar/hall");
    }
}

realm() {
    return("slime");
}
