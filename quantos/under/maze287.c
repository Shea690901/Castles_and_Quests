#include "std.h"

object minotaur, axe, bag, money;

#undef EXTRA_RESET		/* Pell */
#define EXTRA_RESET extra_reset(); /* Pell */

extra_reset() {
    if (!minotaur || !living(minotaur)) {
	minotaur = clone_object ("players/quantos/minotaur");
	move_object (minotaur, this_object());

	axe = clone_object ("obj/weapon");
	call_other (axe, "set_name", "axe");
	call_other (axe, "set_alt_name", "battleaxe");
	call_other (axe, "set_alias", "mithril battleaxe");
	call_other (axe, "set_short", "The minotaur's mithril battleaxe");
	call_other (axe, "set_class", 18);
	call_other (axe, "set_weight", 6);
	call_other (axe, "set_value", 7500);
	transfer (axe, minotaur);

	bag = clone_object ("obj/bag");
	money = clone_object ("obj/money");
	call_other (money, "set_money", 500 + random (1500));
	transfer (money, bag);
	transfer (bag, minotaur);
    }
}

TWO_EXIT ("players/quantos/under/maze286", "south",
	  "players/quantos/under/maze263", "west",
	  "In the labyrinth",
	  "You are in the labyrinth under the plateau.\n", 0)
