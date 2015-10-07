#include "std.h"

object scorpion;

#undef EXTRA_RESET
#define EXTRA_RESET \
    extra_reset();

extra_reset() {

    object stinger, carapace;
    if (!scorpion || !living(scorpion)) {
	scorpion = clone_object ("obj/monster");
	call_other (scorpion, "set_name", "scorpion");
	call_other (scorpion, "set_alias", "giant scorpion");
	call_other (scorpion, "set_short", "A giant scorpion");
	call_other (scorpion, "set_long",
		"It is a huge desert scorpion with a poisonous stinger.\n");
	call_other (scorpion, "set_level", 12);
	call_other (scorpion, "set_hp", 225);
	call_other (scorpion, "set_wc", 12);
	call_other (scorpion, "set_al", -30);
/*	call_other (scorpion, "set_can_kill", 1); /Pell */
	call_other (scorpion, "set_whimpy", 1);
	call_other (scorpion, "set_move_at_reset", 1);
	call_other (scorpion, "set_aggressive", 1);
	call_other (scorpion, "set_init_ob", this_object());
	call_other (scorpion, "set_ac", 6);
	call_other (scorpion, "set_spell_mess1",
		"The scorpion raises its tail and strikes!");
	call_other (scorpion, "set_spell_mess2",
		"The scorpion strikes you with its stinger!");
	call_other (scorpion, "set_chance", 35);
	call_other (scorpion, "set_spell_dam", 18);
	move_object (scorpion, this_object());

	stinger = clone_object ("obj/weapon");
	call_other (stinger, "set_name", "stinger");
	call_other (stinger, "set_alias", "poisonous stinger");
	call_other (stinger, "set_short", "A poisonous stinger");
	call_other (stinger, "set_class", 10);
	call_other (stinger, "set_weight", 2);
	call_other (stinger, "set_value", 250);
	move_object (stinger, scorpion);

	carapace = clone_object ("obj/armour");	/* Fix by Pell, 901006 */
	call_other (carapace, "set_name", "carapace");
	call_other (carapace, "set_short", "A giant scorpion's carapace");
	call_other (carapace, "set_value", 375);
	call_other (carapace, "set_weight", 2);
	call_other (carapace, "set_ac", 3);
	move_object (carapace, scorpion);
    }
}

monster_init (obj) {
    if (call_other (obj, "query_name") == "spider") {return 0;}
    return 1;
}

TWO_EXIT ("players/quantos/desert/gulch2", "west",
	  "players/quantos/desert/dune", "east",
	  "Middle of desert",
	  "You are in a gulch in the middle of the desert.\n" +
	  "Huge walls of sand and rock flank you to the north and south.\n" +
	  "It is much cooler down here than above.\n", 1)
