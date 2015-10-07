#include "std.h"
#include "walker.h"

#undef EXTRA_RESET
#define EXTRA_RESET extra_reset(arg);

object pirate;
object weapon, money, shield;

extra_reset(arg) {

    if (!pirate) {
	pirate = clone_object("obj/monster");
	pirate->set_name("lazy pirate");
	pirate->set_alias("pirate");
	pirate->set_level(3);
	pirate->set_male();
	pirate->set_hp(150);
	pirate->set_al(-100);
	pirate->set_short("A lazy pirate");
	pirate->set_long("This pirate looks very lazy.\n" +
			 "He has sneaked away here to take a nap in the nice bed,\n" +
			 "while his comrades are busy working at demolishing the castle.\n");
	pirate->set_aggressive(1);
        move_object(pirate, this_object());

	weapon = clone_object("obj/weapon");
        weapon->set_name("short sword");
        weapon->set_class(15);
        weapon->set_value(700);
        weapon->set_weight(2);
        weapon->set_alt_name("sword");
        weapon->set_short("A short sword");
        move_object(weapon, pirate);
	pirate->init_command("wield sword");

	shield = clone_object("obj/" + ARMOUR);
        shield->set_name("shield");
        shield->set_alias("small shield");
        shield->set_type("shield");
        shield->set_ac(1);
        shield->set_value(70);
        shield->set_weight(4);
        shield->set_short("A small metal shield");
        move_object(shield, pirate);
	pirate->add_weight(4);
	pirate->init_command("wear shield");

	money = clone_object("obj/money");
	money->set_money(10 + random(100));
        move_object(money, pirate);
    }
} /* extra_reset */

ONE_EXIT("players/padrone/walker/upper_hall", "west",
	 "A bedroom",
	 "This is a large, comfortable bedroom.\n" +
	 "The bed would have looked nice, if it hadn't been for all the blood.\n", 1)
