#include "std.h"

#undef EXTRA_MOVE1
#define EXTRA_MOVE1	\
	write("The tunnel is too narrow to turn around in. You must continue east.\n");	\
    	return 1;

TWO_EXIT("players/padrone/outside/tunnel1", "west",
	 "players/padrone/outside/tunnel3", "east",
	 "Water-filled tunnel",
	 "You are in a dark water-filled tunnel.\n", 0)
