#include "std.h"

object treasure;

#undef EXTRA_RESET
#define EXTRA_RESET extra_reset();

extra_reset() {
    if (!treasure) {
        treasure = clone_object("obj/treasure");
        call_other(treasure, "set_id", "emerald");
        call_other(treasure, "set_alias", "gem");
        call_other(treasure, "set_short", "A small emerald");
        call_other(treasure, "set_weight", 1);
        call_other(treasure, "set_value", 100);
        move_object(treasure, this_object());
    }
}

ONE_EXIT("players/morgar/mountain","up",
         "Cave",
         "You are in a damp cave.\n", 0)
