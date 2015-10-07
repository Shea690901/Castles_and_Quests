#include "std.h"

#undef EXTRA_MOVE1
#define EXTRA_MOVE1 \
    if (this_player()->query_name() != "Padrone") { \
	write("That door can only be used by the one who built it.\n"); \
	write("You seem to be stuck here. Sorry.\n"); \
	return 1; \
    }

ONE_EXIT("players/padrone/workroom", "down",
	 "Storage room",
	 "This is a special storage room inside Padrone's tower.\n" +
	 "Normally, it should be impossible to get here.\n", 1)
