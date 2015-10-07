#include "std.h"

object the_bird;

#undef EXTRA_RESET
#define EXTRA_RESET extra_reset();

extra_reset() {
    if (!the_bird || !living(the_bird)) {
	the_bird = clone_object("obj/monster");
	the_bird->set_name("bird");
	the_bird->set_alias("small bird");
	the_bird->set_level(1);
	the_bird->set_ep(60);
	the_bird->set_hp(10);
	the_bird->set_ac(2);
	the_bird->set_wc(4);
	the_bird->set_al(50);
	the_bird->set_short("A small bird");
	the_bird->set_long("This is a small bird. Who knows what it can be called?\n" +
			   "It looks very nice and friendly.\n");
	move_object(the_bird, this_object());
    }
} /* extra_reset */

TWO_EXIT("players/padrone/outside/nw", "north",
	 "players/padrone/outside/sw", "south",
	 "West of Padrone's Castle",
	 "This is a small path that goes all the way around Padrone's Castle.\n" +
	 "The western wall of the castle looms above you in its stony greyness.\n" +
	 "To the west, there is nothing but the impenetrable trees of the deep\n" +
	 "and dark forest.\n", 1)
