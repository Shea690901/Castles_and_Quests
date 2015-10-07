#include "std.h"

#undef EXTRA_RESET
#define EXTRA_RESET extra_reset();

extra_reset() {
    object bottle;

    if (!present("wine", this_object())) {
	bottle = clone_object("obj/drink");
	bottle->set_value("wine#A bottle of wine labelled Chateau du Padrone 1801#Wow! You almost faint#20#200#8");
	move_object(bottle, this_object());
    }
}


ONE_EXIT("players/padrone/inside/dark_pass2", "east",
	 "Wine cellar",
	 "This is a small, dark room.\n" +
	 "It seems that it was used to store expensive wine bottles,\n" +
	 "but now it has been abandoned.\n", 0)
