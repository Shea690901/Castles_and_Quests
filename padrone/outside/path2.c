#include "std.h"

object squirrel;

#undef EXTRA_RESET
#define EXTRA_RESET extra_reset();

extra_reset() {
    if (!squirrel || !living(squirrel)) {
	squirrel = clone_object("obj/monster");
	squirrel->set_name("squirrel");
	squirrel->set_level(1);
	squirrel->set_ep(60);
	squirrel->set_hp(10);
	squirrel->set_ac(2);
	squirrel->set_wc(4);
	squirrel->set_al(50);
	squirrel->set_short("A squirrel");
	squirrel->set_long("This is a small, furry squirrel.\n" +
			   "It looks very nice and friendly.\n");
	move_object(squirrel, this_object());
    }
} /* extra_reset */

TWO_EXIT("players/padrone/outside/path1", "north",
	 "players/padrone/outside/crossing", "south",
	 "A small path",
	 "You are on a small path winding through the bushes.\n", 1)
