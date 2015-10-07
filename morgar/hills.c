#include "std.h"
object fox;

#undef EXTRA_RESET
#define EXTRA_RESET extra_reset();

extra_reset() {
    if (!fox || !living(fox)) {
        fox = clone_object("obj/monster");
	call_other(fox, "set_name", "red tailed fox");
	call_other(fox, "set_alias", "fox");
	call_other(fox, "set_level", 2);
	call_other(fox, "set_hp", 40);
	call_other(fox, "set_al", -50);
	call_other(fox, "set_aggressive", 1);
	call_other(fox, "set_short", "A fox");
	call_other(fox, "set_long", "A red tailed fox is here.\n");
	move_object(fox, this_object());
    }
}

FOUR_EXIT("players/morgar/field","north",
	 "players/morgar/hills2","south",
	 "players/morgar/hills3","east",
	 "players/morgar/hills4","west",
         "Rolling hills",
         "You are in some rolling hills.  To the north you can see\n" +
         "a grassy field, while the hills continue in the other\n" +
         "directions.\n", 1)
