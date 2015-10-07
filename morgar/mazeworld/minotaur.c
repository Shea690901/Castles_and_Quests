#include "std.h"

object minotaur;

extra_reset() {
    object treasure;
    if (!minotaur || !living(minotaur)) {
	minotaur = clone_object("obj/monster");
	call_other(minotaur, "set_name", "minotaur");
	call_other(minotaur, "set_alias", "bull");
	call_other(minotaur, "set_level", 15);
        call_other(minotaur, "set_hp", 150);
	call_other(minotaur, "set_short", "A minotaur");
	call_other(minotaur, "set_wc", 18);
	call_other(minotaur, "set_ac", 4);
	call_other(minotaur, "set_al", -300);
	call_other(minotaur, "set_aggressive", 1);
	move_object(minotaur, this_object());
    }
}

#undef EXTRA_RESET
#define EXTRA_RESET\
    extra_reset();

ONE_EXIT("players/morgar/mazeworld/maze10", "up",
	 "In the pit of the minotaur",
	 "You are in a pit, which is obviously the home of a minotar.\n", 0)

realm() { return "maze"; }
