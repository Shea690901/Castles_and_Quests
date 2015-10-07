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
	call_other(rabbit, "set_level", 5);
	call_other(rabbit, "set_hp", 50);
	call_other(rabbit, "set_wc", 5);
	call_other(rabbit, "set_al", -150);
	call_other(rabbit, "set_short", "An evil rabbit");
	call_other(rabbit, "set_long", "An evil rabbit is here.\n");
	call_other(rabbit, "set_aggressive", 1);
	move_object(rabbit, this_object());
    }
}

extra_init() {
    add_action("wake"); add_verb("wake");
}

FOUR_EXIT("players/morgar/dreamworld/entry","north",
         "players/morgar/dreamworld/entry","south",
         "players/morgar/dreamworld/entry","east",
         "players/morgar/dreamworld/entry","west",
         "Dream field",
         "You are in a nightmare of a large, grassy field.\n" +
         "In the dream, the field seems larger, so that you\n" +
         "can't escape it.\n", 1)

wake() {
    write("You try valiantly to escape from your nightmare.\n");
    if (random(2)==0) {
        write("You wake up.\n");
        say(call_other(this_player(),"query_name") + " wakes up, and disappears.\n");
        move_object(this_player(), "players/morgar/field");
    } else {
        write("You almost wake up, but the dream has too strong of a hold on you.\n");
    }
    return 1;
}

realm() { return "dream"; }
