#include "std.h"

#undef EXTRA_RESET
#define EXTRA_RESET extra_reset(arg);

object pirate1, pirate2;
object weapon, money;

extra_reset(arg) {

    if (!pirate1) {
	pirate1 = clone_object("obj/monster");
	pirate1->set_name("hungry pirate");
	pirate1->set_alias("pirate");
	pirate1->set_level(2);
	pirate1->set_male();
	pirate1->set_al(-100);
	pirate1->set_short("A hungry pirate");
	pirate1->set_long("This pirate looks hungry. He's looking for food in the kitchen.\n");
	pirate1->set_aggressive(1);
        move_object(pirate1, this_object());

	weapon = clone_object("obj/weapon");
        weapon->set_name("knife");
        weapon->set_class(5);
        weapon->set_value(10);
        weapon->set_weight(1);
        weapon->set_alt_name("knife");
        weapon->set_short("A knife");
        move_object(weapon, pirate1);
	pirate1->init_command("wield knife");

	money = clone_object("obj/money");
        money->set_money(2 + random(10));
        move_object(money, pirate1);
    }

    if (!pirate2) {
	pirate2 = clone_object("obj/monster");
	pirate2->set_name("perverted pirate");
	pirate2->set_alias("pirate");
	pirate2->set_level(3);
	pirate2->set_male();
	pirate2->set_al(-120);
	pirate2->set_short("A perverted pirate");
	pirate2->set_long("This pirate really is perverted!\n" +
			  "It is disgusting to see what he is doing.\n" +
			  "You didn't know that it was anatomically possible to do that,\n" +
			  "at least not with cabbage...\n" +
			  "You are shocked.\n");
	pirate2->set_aggressive(1);
        move_object(pirate2, this_object());
    }

} /* extra_reset */

ONE_EXIT("players/padrone/walker/banquet_hall", "south",
	 "The kitchen of the walking castle",
	 "This is the kitchen of the walking castle.\n" +
	 "The pirates had a party yesterday, and if you hadn't seen it\n" +
	 "for yourself you wouldn't have believed that it is possible\n" +
	 "for a kitchen to be so filthy.\n", 1)
