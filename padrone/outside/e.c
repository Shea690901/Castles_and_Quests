#include "std.h"

object badger;

#undef EXTRA_RESET
#define EXTRA_RESET extra_reset();

extra_reset() {
    if (!badger || !living(badger)) {
	badger = clone_object("obj/monster");
	badger->set_name("badger");
	badger->set_level(2);
	badger->set_female();
	badger->set_ac(3);
	badger->set_wc(10);
	badger->set_al(10);
	badger->set_spell_mess1("The badger bites her opponent.");
	badger->set_spell_mess2("The badger bites you. And she bites hard!");
	badger->set_spell_dam(10);
	badger->set_chance(19);
	badger->set_short("A badger");
	badger->set_long("This is a badger. She seems to be minding her own business,\n" +
			 "but if she is attacked she will probably defend herself\n" +
			 "with some determination.\n");
	move_object(badger, this_object());
    }
} /* extra_reset */

TWO_EXIT("players/padrone/outside/ne", "north",
	 "players/padrone/outside/se", "south",
	 "East of Padrone's Castle",
	 "This is a small path that goes all the way around Padrone's Castle.\n" +
	 "The eastern wall of the castle looms above you in its stony greyness.\n" +
	 "To the east, there is nothing but the impenetrable trees of the deep\n" +
	 "and dark forest.\n", 1)
