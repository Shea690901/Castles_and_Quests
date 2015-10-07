#include "std.h"

THREE_EXIT("players/morgar/slimeworld/desolate", "south",
	 "players/morgar/slimeworld/desolate_2n", "east",
	 "players/morgar/slimeworld/mound", "west",
	 "The slime plain",
	 "You are in a vast plain, covered with dried slime.  The plain\n" +
         "seems to stretch on and on, with nothing of note except for a\n" +
         "small object on the horzon to the southeast, and the stuff near\n" +
         "the mirror to the southwest.\n", 1)

realm() {
    return("slime");
}
