#include "std.h"

object mirror;

THREE_EXIT("players/morgar/mazeworld/maze4", "east",
	 "players/morgar/mazeworld/maze9", "north",
	 "players/morgar/mazeworld/maze10", "south",
	 "Corridor junction",
	 "You at the end of an east-west corridor.  The air glows faintly here.\n", 1)

realm() {
    return("maze");
}
