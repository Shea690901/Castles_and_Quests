#include "std.h"

#undef EXTRA_RESET
#define EXTRA_RESET extra_reset(arg);

object pirate;
object weapon, money;

extra_reset(arg) {

    if (!pirate) {
	pirate = clone_object("obj/monster");
	pirate->set_name("greedy pirate");
	pirate->set_alias("pirate");
	pirate->set_level(5);
	pirate->set_male();
	pirate->set_hp(150);
	pirate->set_al(-100);
	pirate->set_short("A greedy pirate");
	pirate->set_long("This pirate looks very greedy.\n" +
			 "He has stolen some money, and now he has sneaked away up here\n" +
			 "so he won't have to share it with his comrades.\n");
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

	money = clone_object("obj/money");
        money->set_money(100 + random(300));
        move_object(money, pirate);
    }
} /* extra_reset */

ONE_EXIT("players/padrone/walker/upper_hall", "down",
	 "The loft of the walking castle",
	 "This is a small loft, high up in the walking castle.\n", 1)
