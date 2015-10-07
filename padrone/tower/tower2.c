#include "std.h"

#undef EXTRA_RESET
#define EXTRA_RESET   extra_reset();

object the_guard;

extra_reset() {
    if (!the_guard) {
	object the_weapon, the_money;

	the_guard = clone_object("obj/monster");
	the_guard->set_name("security guard");
	the_guard->set_alias("guard");
	the_guard->set_level(4);
	the_guard->set_hp(100);
	the_guard->set_wc(5);
	the_guard->set_al(-10);
	the_guard->set_short("A security guard");
	the_guard->set_long("This is a security guard in a dark suit, tie and sunglasses.\n" +
			    "He is responsible for the security here.\n");
	the_guard->set_aggressive(1);
	the_guard->set_male();
	the_guard->set_spell_mess1("The guard yells: This is a private area! Get out, terrorist!");
	the_guard->set_spell_mess2("The guard yells at you: This is a private area! Get out, terrorist!");
	the_guard->set_chance(50);
	move_object(the_guard, this_object());

	the_weapon = clone_object("players/padrone/obj/m16");
        the_weapon->set_monsters_reload_at_reset(1);
        move_object(the_weapon, the_guard);
	the_guard->init_command("wield m16");

	the_money = clone_object("obj/money");
        the_money->set_money(random(50));
        move_object(the_money, the_guard);
    }
}

TWO_EXIT("players/padrone/tower/tower3", "up",
	 "players/padrone/tower/tower1", "down",
	 "Inside Padrone's private tower",
	 "You are approximately at the first floor of Padrone's private tower.\n" +
	 "A stone staircase winds up and down from here.\n", 0)
