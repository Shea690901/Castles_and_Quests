#include "std.h"

object skeleton;

#undef EXTRA_RESET
#define EXTRA_RESET  extra_reset(arg);

extra_reset(arg) {
    if (!skeleton || !living(skeleton)) {
	skeleton = clone_object("obj/monster");
	skeleton->set_name("skeleton");
	skeleton->set_level(8);
	skeleton->set_hp(70);
	skeleton->set_wc(7);
	skeleton->set_al(-200);
	skeleton->set_short("A skeleton");
	skeleton->set_aggressive(1);
	move_object(skeleton, this_object());
    }
} /* extra_reset */

ONE_EXIT("players/padrone/tower/bedroom", "west",
	 "Wardrobe",
	 "You are inside a small, cluttered wardrobe,\n" +
	 "full of the Wizard's clothes.\n", 1)
