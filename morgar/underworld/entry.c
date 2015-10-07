#include "std.h"

#undef EXTRA_RESET

#define EXTRA_RESET extra_reset();

object mirror;

ONE_EXIT("players/morgar/underworld/brink", "west",
         "A dark cavern",
         "You are at the eastern end of a large underground cavern, which is\n" +
         "completely dark.  In the distace you can hear an eerie drip, drip,\n" +
         "drip of water.  The ceiling stretches up out of thre reach of your\n" +
         "light source\n", 0)

extra_reset() {
    if (!mirror) {
        mirror = clone_object("players/morgar/mirror");
        call_other(mirror, "roomset", this_object());
        move_object(mirror, "players/morgar/hall4");
    }
}

realm() { return("under"); }
