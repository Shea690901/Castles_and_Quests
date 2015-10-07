#include "std.h"

int found;
    object diamond, trollsmasher, troll;

#undef EXTRA_RESET
#define EXTRA_RESET \
    found = found - 1;\
    fix_troll();

fix_troll() {
    if (!troll || !living (troll)) {
	troll = clone_object ("obj/monster");
	call_other (troll, "set_name", "troll");
	call_other (troll, "set_alias", "two headed troll");
	call_other (troll, "set_race", "troll");
	call_other (troll, "set_level", 20); /* Was 19 /pell */
	call_other (troll, "set_hp", 550);
/*	call_other (troll, "set_ep", 1225000); Doesn't work anyway */
	call_other (troll, "set_al", -500);
	call_other (troll, "set_short", "A giant two-headed troll");
	call_other (troll, "set_long",
		"This loathsome twin-headed behemoth laughs eerily from both of its mouths.\n");
	call_other (troll, "set_wc", 35);
	call_other (troll, "set_ac", 12);
	call_other (troll, "set_aggressive", 1);
	call_other (troll, "set_whimpy", 1);

	diamond = clone_object ("obj/treasure");
	call_other (diamond, "set_id", "diamond");
	call_other (diamond, "set_alias", "flawless diamond");
	call_other (diamond, "set_short", "A flawless diamond");
	call_other (diamond, "set_value", 1500);

    if (found < 0) {
	found = 1;
	trollsmasher = clone_object ("obj/weapon");
	call_other (trollsmasher, "set_name", "longsword");
	call_other (trollsmasher, "set_alias", "sword");
	call_other (trollsmasher, "set_short", "Longsword");
	call_other (trollsmasher, "set_alt_name", "trollsmasher");
	call_other (trollsmasher, "set_long",
		"A very sharp, finely crafted 3-foot blade.\n" +
		"The Rune of Fire graces its hilt, as does a picture of a troll.\n");
	call_other (trollsmasher, "set_class", 12);
	call_other (trollsmasher, "set_weight", 6);
	call_other (trollsmasher, "set_value", 2500);
	call_other (trollsmasher, "set_hit_func", this_object());

    move_object (troll, this_object());
    move_object (diamond, troll);
    move_object (trollsmasher, troll);
    }
    }
}

ONE_EXIT ("players/quantos/desert/village", "south",
	  "Troll's hut",
	  "You are in the central hut of the troll village.\n", 1) 

weapon_hit (attacker)
{
    if (call_other (attacker, "id", "troll")) {
	write ("The sword bites deep into your foe.\n");
	return 10;
    }
    return 0;
}
