#include "std.h"

#undef EXTRA_RESET

#define EXTRA_RESET extra_reset();

object mirror, treasure1, treasure2, treasure3;

TWO_EXIT("players/morgar/wizworld/chamber", "north",
	 "players/morgar/wizworld/courtyard", "south",
	 "A magnificent entry chamber",
	 "You are in a magnificent entry chamber, decorated in a baroque\n" +
         "manner.  Several exquisite paintings line the walls, and there is\n" +
         "a fresco on the ceiling.  In addition, the whole is carpeted with\n" +
         "an expensive carpet.\n" +
         "The meeting chamber is to the north, and a courtyard is to the south.\n", 1)

extra_reset() {
    if (!mirror) {
        mirror = clone_object("players/morgar/mirror");
        call_other(mirror, "roomset", this_object());
        move_object(mirror, "players/morgar/hall2");
    }
    /* make these like mirrors.... */
    if (!present("nature painting")) {
        treasure1 = clone_object("obj/treasure");
        call_other(treasure1, "set_id", "nature painting");
        call_other(treasure1, "set_alias", "painting");
        call_other(treasure1, "set_short", "A painting of the field outside of the tower of the gates");
        call_other(treasure1, "set_weight", 100);
        call_other(treasure1, "set_value", 1500);
        move_object(treasure1, this_object());
    }
    if (!present("storm painting")) {
        treasure2 = clone_object("obj/treasure");
        call_other(treasure2, "set_id", "storm painting");
        call_other(treasure2, "set_alias", "painting");
        call_other(treasure2, "set_short", "A painting of a thunderstorm");
        call_other(treasure2, "set_weight", 100);
        call_other(treasure2, "set_value", 2000);
        move_object(treasure2, this_object());
    }
    if (!present("large painting")) {
        treasure3 = clone_object("obj/treasure");
        call_other(treasure3, "set_id", "large painting");
        call_other(treasure3, "set_alias", "painting");
        call_other(treasure3, "set_short", "A huge painting of a battle scene");
        call_other(treasure3, "set_weight", 100);
        call_other(treasure3, "set_value", 2500);
        move_object(treasure3, this_object());
    }
}

realm() {
    return("wizard");
}
