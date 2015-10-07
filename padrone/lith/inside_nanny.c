#include "../../../room/std.h"

#undef EXTRA_MOVE1
#define EXTRA_MOVE1	extra_out();

extra_out() {
    write("You crawl out from the cabinet, and are astonished to notice\n" +
	  "that you fall out on the floor beside a computer...\n");
} /* extra_out */

ONE_EXIT("players/padrone/lith/lysator", "out",
	 "Inside a small dark cabinet",
	 "You are inside a small dark cabinet.\n" +
	 "It is hot, and the noise level is deafening. A lot of small,\n" +
	 "flashing red lights make it possible to see, and you notice\n" +
	 "a hatch that seems to lead out from this uncomfortable place.\n", 1)
