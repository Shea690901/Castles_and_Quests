#include "std.h"
object rabbit;

#undef EXTRA_RESET
#define EXTRA_RESET extra_reset();

#undef EXTRA_INIT
#define EXTRA_INIT extra_init();

extra_reset() {
    if (!rabbit || !living(rabbit)) {
	object key, weapon;
        rabbit = clone_object("obj/monster");
	call_other(rabbit, "set_name", "rabbit");
	call_other(rabbit, "set_alias", "hare");
	call_other(rabbit, "set_level", 2);
	call_other(rabbit, "set_hp", 45);
	call_other(rabbit, "set_al", 50);
	call_other(rabbit, "set_short", "A small rabbit");
	call_other(rabbit, "set_long", "A small rabbit is here.\n");
	move_object(rabbit, this_object());
    }
}

extra_init() {
    add_action("relax"); add_verb("relax");
    add_action("relax"); add_verb("dream");
    add_action("relax"); add_verb("sleep");
}

TWO_EXIT("players/morgar/base","north",
	 "players/morgar/hills","south",
         "Grassy field",
         "You are in a large, grassy field.  It is very tempting\n" +
         "just to lie back in the tall grass and relax.\n", 1)

relax() {
    write("You are not tired.\n");
    return 1;
    write("You lie back and enjoy lying in the grasses for a while.\n");
    write("You fall asleep.\n");
    say(call_other(this_player(),"query_name") + " falls asleep in the tall grasses.\n");
    move_object(this_player(), "players/morgar/dreamworld/entry");
    return 1;
}
