#include "std.h"

object infoboard, note;

#undef EXTRA_RESET
#define EXTRA_RESET extra_reset(arg);

extra_reset(arg) {
    if (arg)
	return;

    note = clone_object("players/padrone/obj/thing");
    note->set_name("small note");
    note->set_alias("note");
    note->set_short("A small note has been nailed to the wall next to the information board");
    note->set_long("This is a small note on the wall.\n" +
		   "It must have been put there by Padrone for visitors to read.\n" +
		   "Why not read it?\n");
    note->set_read_file("/players/padrone/MESSAGE");
    note->set_can_get(0);
    move_object(note, this_object());

    infoboard = clone_object("players/padrone/obj/thing");
    infoboard->set_name("information board");
    infoboard->set_alias("board");
    infoboard->set_short("A big information board is standing here");
    infoboard->set_read_file("/players/padrone/inside/info_board.txt");
    infoboard->set_can_get(0);
    move_object(infoboard, this_object());
} /* extra_reset */

FOUR_EXIT("players/padrone/outside/front_yard", "north",
	  "players/padrone/inside/courtyard", "south",
	  "players/padrone/inside/tower1", "west",
	  "players/padrone/inside/museum", "east",
	  "Gate room",
	  "You are in a small room just inside the gate to the castle.\n" +
	  "You can leave through the gate north, out to the front yard,\n" +
	  "and south of here the castle yard is open to the sky.\n" +
	  "To the east there is a small private museum,\n" +
	  "and to the west you can enter the watchtower,\n" +
	  "which is one of the castle's two towers.\n", 1)
