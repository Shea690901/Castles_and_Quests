#include "std.h"
#include "walker.h"

#undef EXTRA_RESET
#define EXTRA_RESET extra_reset(arg);

object pirate1, pirate2;
object weapon, helmet, money;

extra_reset(arg) {

    if (!pirate2) {
	pirate2 = clone_object("obj/monster");
	pirate2->set_name("bigger pirate");
	pirate2->set_alias("pirate");
	pirate2->set_level(9);
	pirate2->set_male();
	pirate2->set_al(-130);
	pirate2->set_short("A bigger pirate");
	pirate2->set_long("This pirate is bigger than his companion.\n");
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
        money->set_money(20 + random(200));
        move_object(money, pirate2);
    }

    if (!pirate1) {
	pirate1 = clone_object("obj/monster");
	pirate1->set_name("big pirate");
	pirate1->set_alias("pirate");
	pirate1->set_level(7);
	pirate1->set_male();
	pirate1->set_al(-120);
	pirate1->set_short("A big pirate");
	pirate1->set_long("This pirate is big, but not as big as his friend.\n");
	pirate1->set_aggressive(0);
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

        helmet = clone_object("obj/" + ARMOUR);
        helmet->set_name("metal helmet");
        helmet->set_ac(1);
        helmet->set_weight(3);
        helmet->set_value(75);
        helmet->set_alias("helmet");
        helmet->set_type("helmet");
        helmet->set_short("A metal helmet");
        helmet->set_long("A metal helmet\n");
        move_object(helmet, pirate1);
	pirate1->init_command("wear helmet");

	money = clone_object("obj/money");
        money->set_money(10 + random(100));
        move_object(money, pirate1);
    }
} /* extra_reset */

ONE_EXIT("players/padrone/walker/gate_room", "west",
	 "Guard room",
	 "You are in a small guard room east of the gate room in the walking castle.\n" +
	 "The castle guards used to stay here, but now they have been killed\n" +
	 "or driven away by the pirates.\n", 1)
