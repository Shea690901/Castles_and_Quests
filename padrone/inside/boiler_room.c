#include "std.h"

#undef EXTRA_LONG
#define EXTRA_LONG if (extra_long(str)) return;

#undef EXTRA_INIT
#define EXTRA_INIT write("Puh! It's really hot in here!\n");

id(str) {
    return str == "machine" || str == "enormous machine" || str == "boiler";
}

extra_long(str) {
    if (id(str)) {
	write("This is an enormous machine, in which tons and tons of coal\n" +
	      "is burnt in order to heat the castle.\n");
	write("There is no use for it yet, though.\n");
	return 1;
    }
    else
	return 0;
} /* extra_long */

TWO_EXIT("players/padrone/inside/dark_pass2", "west",
	 "players/padrone/inside/coal_cellar", "south",
	 "Boiler room",
	 "The heat in this room is overwhelming!\n" +
	 "You are in the castle's boiler room, where tons and tons of coal is burnt\n" +
	 "in an enormous machine in order to heat the castle.\n", 0)
