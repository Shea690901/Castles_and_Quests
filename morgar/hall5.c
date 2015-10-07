#include "std.h"

#undef EXTRA_INIT
#define EXTRA_INIT add_action("enter"); add_verb("enter");

#undef EXTRA_RESET
#define EXTRA_RESET extra_reset();

object mirror;

TWO_EXIT("players/morgar/hall4", "west",
	 "players/morgar/hallend", "east",
	 "Hall of Gateways",
	 "This is just west of the eastern end of the Hall of Gateways.\n", 1)

enter() {
    write("None of the mirrors here work.\n");
    return 1;
}

extra_reset() {

}
