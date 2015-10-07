#include "std.h"

#undef EXTRA_LONG
#define EXTRA_LONG if (extra_long(str)) return;

id(str) {
    return str == "coal" || str == "heap" || str == "heap of coal";
}

extra_long(str) {
    if (id(str)) {
	write("This is a heap of coal.\n");
	write("There is no use for it yet, though.\n");
	return 1;
    }
    else
	return 0;
} /* extra_long */

THREE_EXIT("players/padrone/inside/boiler_room", "north",
	   "players/padrone/inside/dark_pass1", "west",
	   "players/padrone/outside/back_yard", "up",
	   "Coal cellar",
	   "This is a big and not very clean room full of coal.\n" +
	   "Obviously this castle needs a lot of heating...\n" +
	   "You hear strange sounds from the north,\n" +
	   "and there is sunlight falling down through a door leading up to the south.\n" +
	   "There is a door leading west.\n", 0)
