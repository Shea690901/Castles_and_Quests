#include "std.h"

object reaper, scythe, necklace;

#undef EXTRA_RESET
#define EXTRA_RESET \
    extra_reset();

extra_reset() {
    if (!reaper || !living(reaper)) {
	reaper = clone_object ("obj/monster");
	call_other (reaper, "set_name", "reaper");
	call_other (reaper, "set_alias", "death");
	call_other (reaper, "set_short", "A skull-faced reaper");
	call_other (reaper, "set_race", "undead");
	call_other (reaper, "set_long",
		"A skull-faced reaper, wielding a long scythe.\n" +
	 	"It looks like nothing so much as Death Incarnate.\n");
	call_other (reaper, "set_level", 19);
	call_other (reaper, "set_hp", 375);
	call_other (reaper, "set_ep", 800000);
	call_other (reaper, "set_ac", 7);
	call_other (reaper, "set_wc", 24);
	call_other (reaper, "set_spell_mess1", "The reaper's eyes flash.");
	call_other (reaper, "set_spell_mess2",
		"The reaper gazes coldly at you.");
	call_other (reaper, "set_chance", 10);
	call_other (reaper, "set_spell_dam", 20);
	call_other (reaper, "set_aggressive", 1);
/*	call_other (reaper, "set_can_kill", 1);*/ /* Pell */
	move_object (reaper, this_object());

	scythe = clone_object ("obj/weapon");
	call_other (scythe, "set_name", "scythe");
	call_other (scythe, "set_alt_name", "reaper");
	call_other (scythe, "set_short", "A wicked curve-bladed scythe");
	call_other (scythe, "set_class", 15);
	call_other (scythe, "set_weight", 4);
	call_other (scythe, "set_value", 575);
	transfer (scythe, reaper);

	necklace = clone_object ("obj/armour");	/* Pell */
	call_other (necklace, "set_name", "necklace");
	call_other(necklace, "set_alias", "sightblinder");
	call_other (necklace, "set_short", "A moonstone necklace");
	call_other (necklace, "set_long",
		"A softly glowing moonstone necklace. It seems to pulse\n" +
		"with an inner light as you hold it near your flesh.\n");
	call_other (necklace, "set_value", 2500);
	call_other (necklace, "set_weight", 2);
	call_other (necklace, "set_ac", 0);
/* It doesn't have any ac and you can wear many necklaces, so I think you can
   oversee that the type is not one of the standard ones. */
	call_other (necklace, "set_type", "necklace");
	call_other (necklace, "set_arm_light", 1);
	transfer (necklace, reaper);
    }
}

TWO_EXIT ("players/quantos/under/maze160", "east",
	  "players/quantos/under/maze135", "south",
	  "In the labyrinth",
	  "You are in the labyrinth under the plateau.\n", 0)
