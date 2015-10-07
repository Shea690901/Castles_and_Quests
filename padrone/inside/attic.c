#include "std.h"

object paper;

#undef EXTRA_RESET
#define EXTRA_RESET extra_reset(arg);

extra_reset(arg) {
    if (!paper || !present(paper, this_object())) {
	paper = clone_object("players/padrone/obj/thing");
	paper->set_name("paper");
	paper->set_alias("piece of paper");
	paper->set_short("A piece of paper");
	paper->set_long("This is a small piece of paper, with something written on it.\n");
	paper->set_can_get(1);
	paper->set_weight(1);
	paper->set_value(1);
	paper->set_read("The writing on the paper has a strangely other-worldly quality about it.\n" +
			"It says \"Email: padrone@lysator.liu.se\".\n");
	move_object(paper, this_object());
    }
} /* extra_reset */

ONE_EXIT("players/padrone/inside/stairs2", "down",
	 "Attic",
	 "You are in the attic.\n" +
	 "This is a spacious, airy loft. It is very empty.\n", 1)
