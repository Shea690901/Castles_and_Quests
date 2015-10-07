#include "std.h"

object mirror;

ONE_EXIT("players/morgar/mazeworld/maze1", "south",
	 "Dead end corridor",
	 "You at the end of an north-south corridor.  The air glows faintly here.\n", 1)

realm() {
    return("maze");
}
