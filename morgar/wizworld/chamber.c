#include "std.h"

#undef EXTRA_RESET

#define EXTRA_RESET extra_reset();

object treasure1, treasure2, treasure3;

FOUR_EXIT("players/morgar/wizworld/entry", "south",
         "players/morgar/wizworld/magicroom", "east",
	 "players/morgar/wizworld/chaos", "west",
	 "players/morgar/wizworld/maproom", "north",
	 "The council chamber",
	 "You are in the council chamber of the circle of wizards, where they\n" +
         "hold their meetings.  It is done in a style and grandeur that truly\n" +
         "befits the circle of wizards.  As in the entry, the walls are adorned\n" +
         "with paintings, and the ceiling is done in a fresco that, if anything,\n" +
         "exceeds the one in the entry.\n", 1)

extra_reset() {
    if (!present("ocean painting")) {
        treasure1 = clone_object("obj/treasure");
        call_other(treasure1, "set_id", "ocean painting");
        call_other(treasure1, "set_alias", "painting");
        call_other(treasure1, "set_short", "A painting of the sea, as seen from the village dock");
        call_other(treasure1, "set_weight", 100);
        call_other(treasure1, "set_value", 2000);
        move_object(treasure1, this_object());
    }
    if (!present("tower painting")) {
        treasure2 = clone_object("obj/treasure");
        call_other(treasure2, "set_id", "tower painting");
        call_other(treasure2, "set_alias", "painting");
        call_other(treasure2, "set_short", "A painting of the tower of the gates");
        call_other(treasure2, "set_weight", 100);
        call_other(treasure2, "set_value", 2500);
        move_object(treasure2, this_object());
    }
    if (!present("huge painting")) {
        treasure3 = clone_object("obj/treasure");
        call_other(treasure3, "set_id", "huge painting");
        call_other(treasure3, "set_alias", "painting");
        call_other(treasure3, "set_short", "A huge painting of the creation of the world");
        call_other(treasure3, "set_weight", 100);
        call_other(treasure3, "set_value", 3500);
        move_object(treasure3, this_object());
    }
}

realm() {
    return("wizard");
}
