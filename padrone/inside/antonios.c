/* Antonio's Personal Protection Service (antonios.c) */

#define COST 1000

#include "std.h"

object antonio;
int was_female;

#undef EXTRA_RESET
#define EXTRA_RESET  extra_reset(arg);

#undef EXTRA_INIT
#define EXTRA_INIT  extra_init();

extra_reset(arg) {
    object weapon, armour, advertisement;

    if (!antonio) {
	antonio = clone_object("obj/monster");
	antonio->set_name("antonio");
	antonio->set_alias("director");
	antonio->set_level(18);
	antonio->set_male();
	antonio->set_al(-100);
	antonio->set_hp(300);
	antonio->set_short("Antonio");
	antonio->set_long("This is Antonio, the old mafioso.\n" +
			  "After a life of \"adventure\" he has settled down and started\n" +
			  "the Personal Protection Service, where rich people can hire\n" +
			  "bodyguards as a protection against the dangers in the world...\n");

	move_object(call_other("players/padrone/outside/front_yard", "make_ticket"), antonio);
	move_object(antonio, this_object());

	weapon = clone_object("obj/weapon");
        weapon->set_name("razor");
        weapon->set_class(5);
        weapon->set_value(10);
        weapon->set_weight(1);
        weapon->set_short("A razor");
        move_object(weapon, antonio);
	antonio->add_weight(1);

	weapon = clone_object("obj/weapon");
        weapon->set_name("razor");
        weapon->set_class(5);
        weapon->set_value(10);
        weapon->set_weight(1);
        weapon->set_short("A razor");
        move_object(weapon, antonio);
	antonio->add_weight(1);

	weapon = clone_object("obj/weapon");
        weapon->set_name("battle-axe");
        weapon->set_alt_name("battleaxe");
        weapon->set_alias("axe");
        weapon->set_class(12);
        weapon->set_value(250);
        weapon->set_weight(3);
        weapon->set_short("A battle-axe");
        move_object(weapon, antonio);
	antonio->add_weight(3);
	antonio->init_command("wield battle-axe");

	armour = clone_object("obj/armour");
        armour->set_name("chainmail");
        armour->set_alias("armour");
        armour->set_type("armour");
        armour->set_ac(3);
        armour->set_value(500);
        armour->set_weight(5);
        armour->set_short("A suit of chainmail");
        move_object(armour, antonio);
	antonio->add_weight(5);
	antonio->init_command("wear chainmail");

	armour = clone_object("obj/armour");
        armour->set_name("shield");
        armour->set_alias("small shield");
        armour->set_type("shield");
        armour->set_ac(1);
        armour->set_value(70);
        armour->set_weight(4);
        armour->set_short("A small metal shield");
        move_object(armour, antonio);
	antonio->add_weight(4);
	antonio->init_command("wear shield");

    }

    if (!present("advertisement")) {
	advertisement = clone_object("players/padrone/obj/thing");
	advertisement->set_name("advertisement");
	advertisement->set_alias("ad");
	advertisement->set_short("An advertisement for Antonio's Personal Protection Service");
	advertisement->set_long("It seems interesting. Why not read it?\n");
	advertisement->set_can_get(1);
	advertisement->set_weight(1);
	advertisement->set_value(1);
	advertisement->set_read("It says:\n" +
		   "    Welcome to Antonio's Personal Protection Service!\n" +
		   "    For a moderate price (" + COST +
		   " gold coins) you can hire a personal\n" +
		   "    bodyguard, that will follow you (almost) everywhere, and\n" +
		   "    valiantly protect you from your enemies!\n" +
		   "    The bodyguard will follow your orders - just tell him what to do\n" +
		   "    (by using 'tell' or 'say NAME, ....')!\n" +
		   "    Some useful commands: sleep (rest, wait), wake, kill, guard, report.\n" +
		   "    Address: The Courtyard at the Castle of Padrone\n");

	move_object(advertisement, this_object());
    }
} /* extra_reset */

extra_init() {
    add_action("hire", "hire");
    add_action("do_exit", "exit");
    add_action("do_exit", "out");
} /* extra_init */

do_exit() {
    this_player()->move_player("out#players/padrone/inside/courtyard");
    return 1;
}

find_unused_name() {
    was_female = 0;
    if (!find_living("luigi"))
	return "luigi";
    else if (!find_living("emilio"))
	return "emilio";
    else if (!find_living("sabrina")) {
	was_female = 1;
	return "sabrina";
    }
    else if (!find_living("carlos"))
	return "carlos";
    else if (!find_living("alberto"))
	return "alberto";
    else if (!find_living("benito"))
	return "benito";
    else if (!find_living("mario"))
	return "mario";
    else if (!find_living("furillo"))
	return "furillo";
    else
	return 0;
} /* find_unused_name */


make_bodyguard(client) {
    object bodyguard, weapon;
    string bg_name;

    bg_name = find_unused_name();
    if (!bg_name)
	return 0;

    /* My own subclass of NEW, IMPROVED etc. */
    bodyguard = clone_object("players/padrone/obj/bodyguard");
    bodyguard->set_name(bg_name);
    if (was_female)
	bodyguard->set_female();
    else
	bodyguard->set_male();
    bodyguard->set_guarded(client);

    weapon = clone_object("obj/weapon");
    weapon->set_name("razor");
    weapon->set_class(5);
    weapon->set_value(10);
    weapon->set_weight(1);
    weapon->set_short("A razor");
    move_object(weapon, bodyguard);
    bodyguard->init_command("wield razor");

    move_object(bodyguard, "players/padrone/outside/front_yard");
    move_object(environment(bodyguard)->make_ticket(), bodyguard);

    return bodyguard;
} /* make_bodyguard */

hire() {
    int cost;
    object bodyguard;

    if (!this_player())
	return 0;
    cost = COST;
    if (!antonio)
	write("But Antonio is not here, so he cannot assign a bodyguard to you.\n");
    else if (this_player()->query_money(0) < cost)
	write("You don't have " + cost + " gold coins, so you cannot hire a bodyguard.\n");
    else if (this_player()->query_name() == "Someone")
	write("Due to technical reasons, we cannot handle invisible clients.\n");
    else {

	bodyguard = make_bodyguard(this_player());
	if (!bodyguard) {
	    write("Sorry, all bodyguards are busy.\n");
	    return 1;
	}
	log_file("padrone", ctime(time()) + ": " + this_player()->query_name() +
		 " hired a bodyguard.\n");
	this_player()->add_money(-cost);

	/* Before moving the bodyguard here, or he could attack Antonio: */
	tell_room(this_object(), "A bodyguard arrives.\n");
	move_object(bodyguard, this_object());
	/* To start the heartbeat in the monster: */
	move_object(this_player(), this_object());
	tell_object(bodyguard, "Padrone tells you: report\n");
    }

    return 1;
} /* hire */

ONE_EXIT("players/padrone/inside/courtyard", "east",
	 "Antonio's Personal Protection Service",
	 "You are in the office of Antonio's Personal Protection Service.\n" +
	 "In this room you can hire a bodyguard (use 'hire').\n", 1)
