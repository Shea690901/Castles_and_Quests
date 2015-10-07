/*
 *  load_mirrors.c
 *	Magic mirrors for Uglagrok's mirror maze.
 *	When this room is loaded, it puts all the magic mirros
 *	at their destinations.
 *	As soon as it has been loaded, this room can be destructed.
 *	If a mirror is destructed or moved, for example if the
 *	room was updated, it will not be put back.
 *  1991, May 3.
 */

#include "std.h"
#include "../config.h"

#undef EXTRA_RESET
#define EXTRA_RESET extra_reset(arg);

return_me() {
    return this_object();
}

put_mirror(l1, l2, dir) {
    object mirror;

    mirror = clone_object("players/padrone/maze/magic_mirror");
    mirror->setup(l1, "players/padrone/maze/" + l2, dir);
}

extra_reset(arg) {
    int mirror;

    if (arg)
	return;

    /* First, the mirrors that belong in my own rooms. Always load these. */

	put_mirror("players/padrone/inside/main_hall", "maze33", "east");
	put_mirror("players/padrone/tower/lab", "maze55", "south");
	put_mirror("players/padrone/walker/bedroom", "maze22", "south");
	put_mirror("players/padrone/maze/moses_wardrobe", "maze44", "west");
	put_mirror("players/padrone/maze/uglagroks_bathroom", "maze51", "south");
	
    /* These mirrors are put in OTHER's rooms, on Nanny ONLY. */

#ifdef NANNY
	put_mirror("players/ingis/wiz_room", "maze31", "east");
	put_mirror("players/charles/main_hall", "maze15", "north");
	put_mirror("players/ketchup/hut", "maze24", "south");
	put_mirror("players/akilles/dining_room", "maze12", "south");
	put_mirror("players/beatmaster/sewer4", "maze35", "west");
#endif

    /* And finally, these mirrors are put in OTHER's rooms, on Genesis ONLY. */

#ifdef GENESIS
	put_mirror("players/ingis/wiz_room", "maze31", "east");
	put_mirror("players/charles/main_hall", "maze15", "north");
#endif

} /* extra_reset */

ONE_EXIT("players/padrone/workroom", "out",
	 "Magic mirrors initialization room",
	 "This room is used only to initialize the magic mirrors.\n", 1)
