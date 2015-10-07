#include "std.h"

#undef EXTRA_RESET

#define EXTRA_RESET extra_reset();

object mirror;

FOUR_EXIT("players/morgar/mazeworld/maze1", "north",
         "players/morgar/mazeworld/maze2", "south",
         "players/morgar/mazeworld/maze3", "east",
         "players/morgar/mazeworld/maze4", "west",
	 "Crossing paths",
	 "You are at a junction between a north-south passageway and an\n" +
         "east-west passageway.  The entire area is carved from stone, and\n" +
         "is lit by some strange magic that causes the air itself to glow.\n" +
         "The corridors are about nine feet high and twelve feet across,\n" +
         "and everything is constructed with a perfectly rectangular rectangular\n" +
         "Geometry.  The walls are a black basalt.\n", 1)

extra_reset() {
    if (!mirror) {
        mirror = clone_object("players/morgar/mirror");
        call_other(mirror, "roomset", this_object());
        move_object(mirror, "players/morgar/hallend");
    }
}

realm() {
    return("maze");
}
