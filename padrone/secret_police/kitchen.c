/* secret_police/kitchen.c */

#include "std.h"

object beer;

#undef EXTRA_RESET
#define EXTRA_RESET extra_reset();

extra_reset() {
    if (!present("beer", this_object())) {
	beer = clone_object("obj/drink");
	beer->set_value("beer#A bottle of beer#That feels good#0#12#2");
        move_object(beer, this_object());
    }
} /* extra_reset */

ONE_EXIT("players/padrone/secret_police/backroom", "west",
         "A kitchen behind the shop",
         "You are in a small kitchen behind the shop.\n" +
	 "It doesn't look like it's been used much lately.\n", 1)
