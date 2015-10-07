#include "std.h"

#undef EXTRA_INIT
#define EXTRA_INIT add_action("enter"); add_verb("enter");

#undef EXTRA_RESET
#define EXTRA_RESET extra_reset();

object mirror;

ONE_EXIT("players/morgar/hall5","west",
	 "Hall of Gateways",
	 "This is the eastern end of the Hall of Gateways.\n\n" +
	 "The Hall contains many mirror-like portals to other worlds.\n" +
	 "Each of these portals borders on a different world.  A Hint of\n" +
	 "the nature of a world may be seen by looking at a mirror, and the\n" +
	 "world portrayed therein my be explored by entering the mirror\n" +
	 "Note, however that many of the mirrors are broken.\n", 1)

enter() {
    write("None of the mirrors here work.\n");
    return 1;
}

extra_reset() {
    if (!mirror) {
        mirror = clone_object("players/morgar/mirror");
        call_other(mirror, "roomset", this_object());
        move_object(mirror, "players/morgar/mazeworld/entry");
    }
}
