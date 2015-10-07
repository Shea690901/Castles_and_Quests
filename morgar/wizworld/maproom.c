#include "std.h"

#undef EXTRA_RESET
#define EXTRA_RESET extra_reset();

object map;

ONE_EXIT("players/morgar/wizworld/chamber", "south",
	 "The map room",
	 "You are in a room that is intended to contain a map of the entire\n" +
         "world.  However, due to the extensive creation by the various wizards,\n" +
         "the map is often far from complete and sometimes in error.\n", 1)

extra_reset() {
    if (!present("world map")) {
        map = clone_object("obj/treasure");
        call_other(map, "set_id", "world map");
        call_other(map, "set_alias", "map");
        call_other(map, "set_short", "A map of the world");
        call_other(map, "set_weight", 30);
        call_other(map, "set_value", 2000);
        call_other(map, "set_long",
"The map looks roughly like this:\n\n" +
"      + *\n" +
"      + +\n" +
"      ++++\n" +
"       +++\n" +
"   +++++++++\n" +
"       |||\n" +
"       +++*      *+ +\n" +
" +      |         |+++  +   *\n" +
" +      +         | |   |   |\n" +
" +-+-+--+-+-*-+-+-+-+---+-+-+-*\n" +
"   +    |           |   |\n" +
" ++++   +*          |   +\n" +
" | |    +          +*++\n" +
" +++    +           +\n" +
" +     +++\n" +
" *      *\n\n" +
"The *'s refer to other maps, most of which are not here\n");
        move_object(map, this_object());
    }
}

realm() { return("wizard"); }
