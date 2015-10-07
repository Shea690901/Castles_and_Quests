#include "std.h"

#undef EXTRA_RESET
#define EXTRA_RESET extra_reset(arg);

object pirate1, pirate2;
object weapon, money;

extra_reset(arg) {

    if (!pirate1) {
	pirate1 = clone_object("obj/monster");
	pirate1->set_name("disgusting pirate");
	pirate1->set_alias("pirate");
	pirate1->set_level(2);
	pirate1->set_male();
	pirate1->set_al(-100);
	pirate1->set_short("A disgusting pirate");
	pirate1->set_long("Yuk! What a disgusting pirate!\n");
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
        money->set_money(2 + random(20));
        move_object(money, pirate1);
    }

    if (!pirate2) {
	pirate2 = clone_object("obj/monster");
	pirate2->set_name("rude pirate");
	pirate2->set_alias("pirate");
	pirate2->set_level(3);
	pirate2->set_male();
	pirate2->set_al(-100);
	pirate2->set_short("A rude pirate");
	pirate2->set_long("The rude pirate laughs and makes an obscene gesture.\n");
	pirate2->set_aggressive(1);
        move_object(pirate2, this_object());

	weapon = clone_object("obj/weapon");
        weapon->set_name("hand axe");
        weapon->set_class(9);
        weapon->set_value(25);
        weapon->set_weight(2);
        weapon->set_alt_name("axe");
        weapon->set_short("A hand axe");
        move_object(weapon, pirate2);
	pirate2->init_command("wield axe");

	money = clone_object("obj/money");
        money->set_money(2 + random(40));
        move_object(money, pirate2);
    }

} /* extra_reset */

ONE_EXIT("players/padrone/walker/castle_yard", "east",
	 "The shop of the walking castle",
	 "You are in what used to be the local shop.\n" +
	 "Here you could buy and sell items of different kinds, but the\n" +
	 "pirates have of course stolen everything they could carry,\n" +
	 "and smashed the rest to small pieces.\n", 1)
