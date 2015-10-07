#include "std.h"
#include "walker.h"

#undef EXTRA_RESET
#define EXTRA_RESET extra_reset(arg);

object pirate, knife, helmet, money;

extra_reset(arg) {

    if (!pirate) {
	pirate = clone_object("obj/monster");
	pirate->set_name("fat pirate");
	pirate->set_alias("pirate");
	pirate->set_level(3);
	pirate->set_male();
	pirate->set_al(-100);
	pirate->set_short("A fat pirate");
	pirate->set_long("This is a short and fat pirate.\n");
	pirate->set_aggressive(1);
        move_object(pirate, this_object());

	knife = clone_object("obj/weapon");
        knife->set_name("knife");
        knife->set_class(5);
        knife->set_value(10);
        knife->set_weight(1);
        knife->set_alt_name("knife");
        knife->set_short("A knife");
        move_object(knife, pirate);
	pirate->init_command("wield knife");

        helmet = clone_object("obj/" + ARMOUR);
        helmet->set_name("metal helmet");
        helmet->set_ac(1);
        helmet->set_weight(3);
        helmet->set_value(75);
        helmet->set_alias("helmet");
        helmet->set_type("helmet");
        helmet->set_short("A metal helmet");
        helmet->set_long("A metal helmet\n");
        move_object(helmet, pirate);
	pirate->init_command("wear helmet");

	money = clone_object("obj/money");
        money->set_money(2 + random(10));
        move_object(money, pirate);
    }
} /* extra_init */

FOUR_EXIT("players/padrone/walker/gate_room", "south",
	  "players/padrone/walker/main_hall", "north",
	  "players/padrone/walker/shop", "west",
	  "players/padrone/walker/pub", "east",
	  "Castle yard of the walking castle",
	  "You are in the castle yard of the walking castle.\n" +
	  "Once this was a nice place, with beautiful flowers, sculptures\n" +
	  "and a fountain, but the pirates have eaten the flowers,\n" +
	  "broken the sculptures, and polluted the fountain.\n", 1)
