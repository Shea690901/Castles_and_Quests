#include "std.h"

#undef EXTRA_RESET
#define EXTRA_RESET   extra_reset(arg);

object the_terrorist;

extra_reset(arg) {
    if (!the_terrorist) {
	object weapon;

	the_terrorist = clone_object("obj/monster");
	the_terrorist->set_name("german terrorist");
	the_terrorist->set_alias("terrorist");
	the_terrorist->set_level(6);
	the_terrorist->set_male();
	the_terrorist->set_al(-100);
	the_terrorist->set_short("A german terrorist");
	the_terrorist->set_long("This is a terrorist, wearing black clothes and a green army jacket.\n" +
				"He has long, unwashed hair, dark sunglasses, and an angry look.\n" +
				"He must have sneaked past the security!\n" +
				"Maybe he has come to kill the wizard or blow up the castle?\n");
	the_terrorist->set_aggressive(1);
	the_terrorist->set_spell_mess1("The terrorist yells: Verdammte bourgeois fascist lackey! R-A-F! R-A-F!");
	the_terrorist->set_spell_mess2("The terrorist yells: Verdammte bourgeois fascist lackey! R-A-F! R-A-F!");
	the_terrorist->set_chance(20);
	move_object(the_terrorist, this_object());

	weapon = clone_object("obj/weapon");
        weapon->set_name("bayonet");
        weapon->set_class(12);
        weapon->set_value(100);
        weapon->set_weight(1);
        weapon->set_short("A bayonet");
        move_object(weapon, the_terrorist);
	the_terrorist->init_command("wield bayonet");
    }
}

TWO_EXIT("players/padrone/tower/tower4", "up",
	 "players/padrone/tower/tower2", "down",
	 "Inside Padrone's private tower",
	 "You are approximately at the second floor of Padrone's private tower.\n" +
	 "A stone staircase winds up and down from here.\n", 0)
