#include "std.h"

object crystal_ball, guard;

#undef EXTRA_RESET
#define EXTRA_RESET  extra_reset(arg);

#undef EXTRA_LONG
#define EXTRA_LONG  extra_long();

extra_reset(arg) {
    if (!guard) {
	guard = clone_object("obj/monster");
	guard->set_name("guard");
	guard->set_level(1);
	guard->set_male();
	guard->set_hp(50);
	guard->set_al(50);
	guard->set_short("A guard");
	guard->set_long("This is a guard dressed in a grey uniform.\n" +
			"He used to guard the museum, and has not received his new orders yet.\n");
	guard->set_aggressive(0);

	move_object(call_other("players/padrone/outside/front_yard", "make_ticket"), guard);
	move_object(guard, this_object());
    }
    if (!crystal_ball || !present(crystal_ball)) {
	crystal_ball = clone_object("players/padrone/obj/crystal_ball");
	move_object(crystal_ball, this_object());
    }
} /* extra_reset */

extra_long() {
    write("You are in the Museum in Padrone's Castle.\n" +
	  "This is a small private museum, where tables, shelves and\n" +
	  "some glass show-cases have been used to exhibit valuable\n" +
	  "and interesting items.\n" +
	  "But, due to the high crime rate, these items are now\n" +
	  "stored in the Castle's treasury. They are no longer\n" +
	  "publicly displayed.\n");
    if (crystal_ball && present(crystal_ball))
	write("It looks like one of the items has been left here by mistake...\n");
}

ONE_EXIT("players/padrone/inside/gate_room", "west",
	 "Museum",
	 "", 1)

/* This function can be called from the crystal ball! */
stop_taking(what) {
    if (   what == crystal_ball && present(what, this_object())
	&& guard && present(guard, this_object())) {
	write("The guard stops you from taking " + what->short() + ".\n");
	say("Guard says: That is the property of the museum.\n");
	write("Guard says: That is the property of the museum.\n");
	return 1;
    }
    return 0;
} /* stop_taking */
