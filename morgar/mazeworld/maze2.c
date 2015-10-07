#include "std.h"

object mirror;

TWO_EXIT("players/morgar/mazeworld/maze6", "east",
         "players/morgar/mazeworld/entry", "north",
	 "Turn in corridor",
	 "You are in a north-east corridor junction.  The air glows dimly here.\n", 1)

realm() {
    return("maze");
}
