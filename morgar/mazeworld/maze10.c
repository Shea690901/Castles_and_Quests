#include "std.h"

object mirror;

TWO_EXIT("players/morgar/mazeworld/maze8", "north",
	 "players/morgar/mazeworld/minotaur", "down",
	 "Dead end corridor",
	 "You at the end of a north-south corridor.  There is a dark hole in\n" +
         "the floor here.\n", 0)

realm() {
    return("maze");
}
