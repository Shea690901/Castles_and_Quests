#include "std.h"

THREE_EXIT("players/morgar/slimeworld/pillars", "south",
	 "players/morgar/slimeworld/mound", "east",
	 "players/morgar/slimeworld/crypt", "down",
	 "Ruins of a temple",
	 "You are in what was once a temple.  However, slime has long since\n" +
         "eaten away at the stone, leaving decayed ruins.\n", 1)

realm() {
    return("slime");
}
