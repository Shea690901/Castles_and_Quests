/* On Genesis, this room is connected to Mariols' area */

#include "std.h"
#include "config.h"

#ifdef GENESIS

THREE_EXIT("players/padrone/outside/back_yard", "north",
	   "players/padrone/garbage_heap", "east",	/* Not "outside" */
	   "players/mariols/airfield", "south",
	   "Very dense bushes",
	   "You are among some particularly dense and troublesome bushes.\n" +
	   "A nasty smell is coming from the east.\n", 1)

#else
  /* Not GENESIS, i. e. NANNY or EXPORT */

TWO_EXIT("players/padrone/outside/back_yard", "north",
	 "players/padrone/garbage_heap", "east",	/* Not "outside" */
	 "Very dense bushes",
	 "You are among some particularly dense and troublesome bushes.\n" +
	 "A nasty smell is coming from the east.\n", 1)

#endif
