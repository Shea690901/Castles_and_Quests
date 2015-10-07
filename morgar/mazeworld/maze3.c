#include "std.h"

object mirror;

TWO_EXIT("players/morgar/mazeworld/maze7", "east",
         "players/morgar/mazeworld/entry", "west",
	 "Corridor",
	 "You are in an east-west corridor.  The air glows dimly here.\n", 1)

realm() {
    return("maze");
}
