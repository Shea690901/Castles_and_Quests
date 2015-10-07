#include "std.h"

object mirror;

ONE_EXIT("players/morgar/mazeworld/maze3", "west",
	 "Dead end corridor",
	 "You at the end of an east-west corridor.  The air glows faintly here.\n", 1)

realm() {
    return("maze");
}
