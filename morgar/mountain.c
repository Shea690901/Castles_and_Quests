#include "std.h"

object treasure;

#undef EXTRA_RESET
#define EXTRA_RESET extra_reset();

extra_reset() {
    if (!treasure) {
        treasure = clone_object("obj/treasure");
        call_other(treasure, "set_id", "pretty rock");
        call_other(treasure, "set_alias", "rock");
        call_other(treasure, "set_short", "A pretty rock");
        call_other(treasure, "set_weight", 1);
        call_other(treasure, "set_value", 15);
        move_object(treasure, this_object());
    }
}

THREE_EXIT("players/morgar/cave","down",
         "players/morgar/hills2","north",
         "players/morgar/dragon","up",
         "Mountain",
         "A gold dragon has its lair further up the mountain.\n", 1)
