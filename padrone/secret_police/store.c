/* secret_police/store.c */

#include "std.h"

object rope;

#undef EXTRA_RESET
#define EXTRA_RESET extra_reset();

extra_reset() {
    if (!rope || !present(rope, this_object())) {
	rope = clone_object("obj/rope");
        move_object(rope, this_object());
    }
} /* extra_reset */

ONE_EXIT("players/padrone/secret_police/backroom", "east",
	  "The store room for the shop",
	  "You are in the store room for this shop. It is remarkably empty.\n", 1)
