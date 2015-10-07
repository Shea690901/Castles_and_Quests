#include "std.h"

#undef EXTRA_RESET
#define EXTRA_RESET extra_reset();

object fountain;

ONE_EXIT("players/morgar/wizworld/entry", "north",
	 "The courtyard",
	 "This is a large courtyard, just outside of the hall of wizards.\n", 1)

extra_reset() {
    if (!present("fountain")) {
        fountain = clone_object("players/morgar/wizworld/fountain");
        move_object(fountain, this_object());
    }
}

realm() { return("wizard"); }
