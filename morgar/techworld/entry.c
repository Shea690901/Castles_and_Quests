#include "std.h"

#undef EXTRA_RESET

#define EXTRA_RESET extra_reset();

object mirror;

ONE_EXIT("players/morgar/techworld/blockage", "north",
	 "An abandoned alley",
	 "You are at the southern end of an alley in what appears to be the\n" +
         "ruins of a once great technological city.  All around you skyscrapers\n" +
         "rise up to the sky.  However, the doors and garages around you are\n" +
         "all either boarded up or welded shut.  Large amounts of rubble clog\n" +
         "the alley.\n", 1)

extra_reset() {
    if (!mirror) {
        mirror = clone_object("players/morgar/mirror");
        call_other(mirror, "roomset", this_object());
        move_object(mirror, "players/morgar/hall3");
    }
}

realm() { return("tech"); }
