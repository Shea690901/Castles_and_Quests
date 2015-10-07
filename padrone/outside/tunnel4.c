#include "std.h"

#undef EXTRA_MOVE1
#define EXTRA_MOVE1	\
	write("The tunnel is too narrow to turn around in. You must continue east.\n");	\
    	return 1;

#undef EXTRA_MOVE2
#define EXTRA_MOVE2	\
	write("The tunnel is getting narrower, and the water is moving faster here.\n");	\
	write("You are carried away by the moving water, and you cannot control\n" +	\
	      "where you are going!\n");

TWO_EXIT("players/padrone/outside/tunnel3", "west",
	 "room/sea_bottom", "east",
	 "Water-filled tunnel",
	 "You are in a dark water-filled tunnel.\n", 0)
