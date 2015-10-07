#include "std.h"

object mirror;

TWO_EXIT("players/morgar/mazeworld/maze8", "west",
         "players/morgar/mazeworld/entry", "east",
	 "Corridor",
	 "You are in an east-west corridor.  The air glows dimly here.\n", 1)

realm() {
    return("maze");
}
