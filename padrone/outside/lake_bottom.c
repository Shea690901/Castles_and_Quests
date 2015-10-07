#include "std.h"

object fish;

#undef EXTRA_RESET
#define EXTRA_RESET  extra_reset();

extra_reset() {

    if (!fish || !living(fish)) {
	fish = clone_object("obj/monster");
	fish->set_name("small fish");
	fish->set_alias("fish");
	fish->set_level(1);
	fish->set_ep(60);
	fish->set_hp(20);
	fish->set_wc(1);
	fish->set_ac(5);
	fish->set_al(0);
	fish->set_short("A small fish");
	fish->set_long("A small fish, swimming happily in the clear water of the lake.\n");
	move_object(fish, this_object());
    }
}

TWO_EXIT("players/padrone/outside/small_lake", "up",
	 "players/padrone/outside/tunnel1", "down",
	 "Bottom of small lake",
	 "You are under the water. There is sunshine coming down from above.\n" +
	 "You notice a hole in the bottom of the lake.\n", 1)
