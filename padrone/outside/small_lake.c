#include "std.h"

#undef EXTRA_INIT
#define EXTRA_INIT add_action("dive", "dive");

TWO_EXIT("players/padrone/outside/north_shore", "north",
	 "players/padrone/outside/nice_place", "south",
	 "Small lake",
	 "You are swimming in a small, beautiful lake in the forest.\n" +
	 "The lake is surrounded by tall trees, but to the south you\n" +
	 "notice a clearing that looks extraordinarily nice.\n" +
	 "The lake itself looks very deep.\n", 1)

dive() {
    object ob;

    ob = first_inventory(this_player());
    while(ob) {
	if (ob->can_put_and_get()) {
	    this_player()->move_player("down#players/padrone/outside/lake_bottom");
	    return 1;
	}
	ob = next_inventory(ob);
    }
    write("You can't breathe under water!\n");
    write("You should try to get some portable air supply!\n");
    return 1;
} /* dive */
