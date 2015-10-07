#include "std.h"


object golem, wand;

#undef EXTRA_RESET
#define EXTRA_RESET extra_reset();

extra_reset() {
    if (!golem || !living(golem)) {
	golem = clone_object ("obj/monster");
	call_other (golem, "set_name", "golem");
	call_other (golem, "set_alias", "flesh golem");
	call_other (golem, "set_race", "construct");
	call_other (golem, "set_short", "A flesh golem");
	call_other (golem, "set_long",
		"A strong creature made of sewed-together bits of flesh.\n");
	call_other (golem, "set_level", 20);
	call_other (golem, "set_hp", 750);
	call_other (golem, "set_ep", 1050000);
	call_other (golem, "set_wc", 26);
	call_other (golem, "set_ac", 10);
	call_other (golem, "set_al", -350);
	call_other (golem, "set_aggressive", 1);
	move_object (golem, this_object());

	wand = clone_object ("players/quantos/wand_wonder");
	move_object (wand, golem);
    }
}
TWO_EXIT ("players/quantos/under/maze135", "north",
	  "players/quantos/under/maze158", "east",
	  "In the labyrinth",
	  "You are in the labyrinth under the plateau.\n", 0)
