#include "std.h"

THREE_EXIT("players/morgar/slimeworld/desolate", "north",
	 "players/morgar/slimeworld/desolate_2s", "east",
	 "players/morgar/slimeworld/pool", "west",
	 "The slime plain",
	 "You are in a vast plain, covered with dried slime.  The plain\n" +
         "seems to stretch on and on, with nothing of note except for a\n" +
         "small object on the horzon to the northeast, and the stuff near\n" +
         "the mirror to the northwest.\n", 1)

realm() {
    return("slime");
}
