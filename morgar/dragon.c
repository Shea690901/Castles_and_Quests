#include "std.h"

object dragon;

extra_reset() {
    object treasure;
    if (!dragon || !living(dragon)) {
	dragon = clone_object("obj/monster");
	call_other(dragon, "set_name", "dragon");
	call_other(dragon, "set_alias", "wyrm");
	call_other(dragon, "set_level", 19);
        call_other(dragon, "set_hp", 200);
	call_other(dragon, "set_short", "A gold dragon");
	call_other(dragon, "set_wc", 22);
	call_other(dragon, "set_ac", 5);
	call_other(dragon, "set_al", 900);
	call_other(dragon, "set_aggressive", 0);
        call_other(dragon, "set_chance",20);
        call_other(dragon, "set_spell_mess1",
                   "The dragon breathes fire.");
        call_other(dragon, "set_spell_mess2",
                   "The dragon breathes fire on you.");
        call_other(dragon, "set_spell_dam",30);
	move_object(dragon, this_object());
	treasure = clone_object("obj/treasure");
	call_other(treasure, "set_id", "diamond");
	call_other(treasure, "set_alias", "gem");
	call_other(treasure, "set_short", "A giant diamond");
	call_other(treasure, "set_weight", 3);
	call_other(treasure, "set_value", 1000);
	move_object(treasure, dragon);
    }
}

#undef EXTRA_RESET
#define EXTRA_RESET\
    extra_reset();

ONE_EXIT("players/morgar/mountain", "down",
	 "The Gold Dragon's lair",
	 "You are in the lair of a gold dragon.\n", 1)
