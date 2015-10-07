#include "std.h"

object wisp;

#undef EXTRA_RESET
#define EXTRA_RESET \
    extra_reset();

extra_reset() {
    if(!wisp || !living(wisp)) {
	wisp = clone_object("obj/monster");
	call_other(wisp, "set_level", 17);
	call_other(wisp, "set_name", "wisp");
	call_other(wisp, "set_alias", "balefire");
	call_other(wisp, "set_alt_name", "will-o-wisp");
	call_other(wisp, "set_short", "A will-o-wisp");
	call_other(wisp, "set_long",
	 "This is a floating, pulsing ball of electrical energy.\n" +
	 "It glows with an inner malevolent light.\n");
	call_other(wisp, "set_aggressive", 1);
	call_other(wisp, "set_hp", 300);
	call_other(wisp, "set_ep", 200000);
	call_other(wisp, "set_al", -450);
	call_other(wisp, "set_spell_mess1",
	 "The wisp crackles with electrical energy!");
	call_other(wisp, "set_spell_mess2",
	 "An electrical bolt from the will-o-wisp strikes you hard!");
	call_other(wisp, "set_spell_dam", 25);
	call_other(wisp, "set_chance", 34);
	call_other(wisp, "set_ac", 8);
	call_other(wisp, "set_wc", 16);
	move_object(wisp, this_object());
    }
}

TWO_EXIT ("players/quantos/under/maze183", "north",
	  "players/quantos/under/maze158", "west",
	  "In the labyrinth",
	  "You are in the labyrinth under the plateau.\n", 0)
