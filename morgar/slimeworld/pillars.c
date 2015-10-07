#include "std.h"

TWO_EXIT("players/morgar/slimeworld/ruins", "north",
	 "players/morgar/slimeworld/entry", "east",
	 "Ruins of a temple",
	 "You are in what must have once been a temple.  However, slime\n" +
         "has long since eaten away at the stone, leaving only a few pillars.\n", 1)

realm() {
    return("slime");
}
