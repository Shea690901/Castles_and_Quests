#include "std.h"

object mirror;

TWO_EXIT("players/morgar/mazeworld/maze5", "north",
         "players/morgar/mazeworld/entry", "south",
	 "Corridor",
	 "You are in a north-south corridor.  The air glows dimly here.\n", 1)

realm() {
    return("maze");
}
