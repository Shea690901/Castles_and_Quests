#include "std.h"
#include "../config.h"

#undef EXTRA_INIT
#define EXTRA_INIT  extra_init();

extra_init() {
    add_action("do_exit", "exit");
    add_action("do_exit", "out");
} /* extra_init */

do_exit() {
    this_player()->move_player("out#players/padrone/inside/courtyard");
    return 1;
}

ONE_EXIT("players/padrone/inside/courtyard", "southwest",
	 "Empty office",
	 "You are in an empty office in Padrone's Castle.\n" +
	 "Maybe Padrone will put something here later.\n" +
	 "Maybe someone else will rent it.\n", 1)
