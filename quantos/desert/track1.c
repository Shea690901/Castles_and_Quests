#include "std.h"

object troll1, troll2;

extra_reset () {
  object money, weapon;
  if (!troll1 || !living(troll1)) {
    troll1 = clone_object ("obj/monster");
    call_other (troll1, "set_name", "troll");
    call_other (troll1, "set_alias", "blacktroll");
    call_other (troll1, "set_race", "troll");
    call_other (troll1, "set_level", 12);
    call_other (troll1, "set_hp", 140);
    call_other (troll1, "set_ep", 175000);
    call_other (troll1, "set_al", -125);
    call_other (troll1, "set_short", "A black troll");
    call_other (troll1, "set_long",
		"It is a hideously ugly troll. with coruscating sparks of electricity\n" +
		"    cascading off its mottled hide.\n");
    call_other (troll1, "set_aggressive", 1);
    call_other (troll1, "set_wc", 15);
    call_other (troll1, "set_ac", 4);
    call_other (troll1, "set_spell_mess1",
		"The troll throws lightning!");
    call_other (troll1, "set_spell_mess2",
		"The troll hurls a bolt of electricity at you!");
    call_other (troll1, "set_chance", 18);
    call_other (troll1, "set_spell_dam", 20);
    move_object (troll1, this_object());
    money = clone_object ("obj/money");
    call_other (money, "set_money", random (600)); /* Was 1200 /Pell */
    move_object (money, troll1);
  }
  if (!troll2 || !living(troll2)) {
    troll2 = clone_object ("obj/monster");
    call_other (troll2, "set_name", "troll");
    call_other (troll2, "set_alias", "redtroll");
    call_other (troll2, "set_race", "troll");
    call_other (troll2, "set_level", 14); /* Was 12 /Pell */
    call_other (troll2, "set_hp", 150);
    call_other (troll2, "set_ep", 175000);
    call_other (troll2, "set_al", -125);
    call_other (troll2, "set_short", "A red troll");
    call_other (troll2, "set_long",
		"It is an enormous troll, with bulging muscles. It looks VERY strong.\n");
    call_other (troll2, "set_aggressive", 1);
    call_other (troll2, "set_wc", 20);
    call_other (troll2, "set_ac", 6);
    call_other (troll2, "set_spell_mess1",
		"The troll throws a sucker punch!");
    call_other (troll2, "set_spell_mess2",
		"The troll punches you, rupturing some vital organ!");
    call_other (troll2, "set_chance", 5);
    call_other (troll2, "set_spell_dam", 24);
    move_object (troll2, this_object());
    weapon = clone_object ("obj/weapon");
    call_other (weapon, "set_name", "club");
    call_other (weapon, "set_alias", "spiked club");
    call_other (weapon, "set_short", "A huge spiked club");
    call_other (weapon, "set_class", 12);
    call_other (weapon, "set_weight", 4);
    call_other (weapon, "set_value", 500);
    move_object (weapon, troll2);
  }
}

#undef EXTRA_RESET
#define EXTRA_RESET \
	extra_reset();

THREE_EXIT ("players/quantos/desert/desert3", "east",
	    "players/quantos/desert/village", "west",
	    "players/quantos/desert/desert2", "south",
	    "Village road",
	    "You are on the track leading to the village.\n", 1)
