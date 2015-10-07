#include "std.h"

FOUR_EXIT("players/morgar/slimeworld/desolate_n", "north",
	 "players/morgar/slimeworld/desolate_s", "south",
	 "players/morgar/slimeworld/desolate_2", "east",
	 "players/morgar/slimeworld/entry", "west",
	 "The slime plain",
	 "You are in a vast plain, covered with dried slime.  The plain\n" +
         "seems to stretch on and on, with nothing of note except for a\n" +
         "small object on the horzon to the east, and the stuff near the\n" +
         "mirror to the west.\n", 1)

realm() {
    return("slime");
}
