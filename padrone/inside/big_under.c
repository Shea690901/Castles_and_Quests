#include "std.h"

object down_room;

#undef EXTRA_RESET
#define EXTRA_RESET extra_reset(arg);

#undef EXTRA_MOVE2
#define EXTRA_MOVE2 \
	if (down_room) { \
		this_player()->move_player("down", down_room); \
		return 1; \
        } \
        else \
                write("How strange.\n");

TWO_EXIT("players/padrone/inside/dark_pass2", "south",
	 "players/padrone/inside/big_under", "down",
	 "Big underground room",
	 "This is a big underground room, excavated under the castle.\n" +
	 "It is empty, but the floor seems soft, and someone has dug a\n" +
	 "hole leading down.\n", 1)

extra_reset(arg) {
    if (!arg) {
	down_room = clone_object("players/padrone/dungeon/dungeon_room");
	down_room->reset2();
	down_room->set_coordinates(0, 0, 0);
	down_room->set_exit(0, this_object());
    }
} /* extra_reset */
