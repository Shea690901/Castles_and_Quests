/* The courtyard. Lots of exits. */

#include "../config.h"

object the_sign, giant1, giant2;

/* For the NEW, IMPROVED monster class: */
string function1, type1, match1, function2, type2, match2;

extra_reset(arg) {
    object weapon;

    if (!giant2) {
	giant2 = clone_object("obj/monster");	/* NEW, IMPROVED monster class!*/
	giant2->set_name("sam");
	giant2->set_alias("giant");
	giant2->set_race("giant");
	giant2->set_level(16);
	giant2->set_male();
	giant2->set_hp(250);
	giant2->set_al(-200);
	giant2->set_short("Sam the giant");
	giant2->set_long("Sam is a giant. You gasp at his incredible size!\n" +
			 "He towers high above you, and wields a huge tree trunk as a weapon.\n" +
			 "Sam and his little brother Billy have been employed by the Wizard\n" +
			 "as guards. You guess that the Wizard probably doesn't worry\n" +
			 "much about intruders any more.\n" +
			 "You know that there used to be a platoon of U. S. Marines\n" +
			 "guarding this castle, but now they have been replaced\n" +
			 "with something more intimidating...\n");
	giant2->set_aggressive(0);
	giant2->set_spell_mess1("Sam the giant laughs happily.");
	giant2->set_spell_mess2("Sam the giant laughs at you.");
	giant2->set_chance(20);

	move_object(call_other("players/padrone/outside/front_yard", "make_ticket"), giant2);
	move_object(giant2, this_object());

	weapon = clone_object("obj/weapon");
	weapon->set_name("huge tree trunk");
	weapon->set_alias("trunk");
	weapon->set_short("A huge tree trunk");
	weapon->set_class(40);
	weapon->set_weight(150);
	weapon->set_value(30);
	move_object(weapon, giant2);
	giant2->init_command("wield trunk");

	/* The NEW, IMPROVED monster calls: */
	if (!function2)
	    setup_arrays();
	giant2->set_match(this_object(), function2, type2, match2);
    }

    if (!giant1) {
	giant1 = clone_object("obj/monster");	
	giant1->set_name("billy");
	giant1->set_alias("giant");
	giant1->set_race("giant");
	giant1->set_level(15);
	giant1->set_male();
	giant1->set_hp(200);
	giant1->set_al(-100);
	giant1->set_short("Billy the giant");
	giant1->set_long("Billy is a giant. You gasp at his incredible size!\n" +
			 "He towers high above you, and wields a tree trunk as a weapon.\n" +
			 "Billy and his big brother Sam have been employed by the Wizard\n" +
			 "as guards. You guess that the Wizard probably doesn't worry\n" +
			 "much about intruders any more.\n" +
			 "You know that there used to be a platoon of U. S. Marines\n" +
			 "guarding this castle, but now they have been replaced\n" +
			 "with something more intimidating...\n");
	giant1->set_aggressive(0);
	giant1->set_spell_mess1("Billy the giant laughs happily.");
	giant1->set_spell_mess2("Billy the giant laughs at you.");
	giant1->set_chance(20);

	move_object(call_other("players/padrone/outside/front_yard", "make_ticket"), giant1);
	move_object(giant1, this_object());

	weapon = clone_object("obj/weapon");
	weapon->set_name("tree trunk");
	weapon->set_alias("trunk");
	weapon->set_short("A tree trunk");
	weapon->set_class(30);
	weapon->set_weight(100);
	weapon->set_value(20);
	move_object(weapon, giant1);
	giant1->init_command("wield trunk");

	/* The NEW, IMPROVED monster calls: */
	if (!function1)
	    setup_arrays();
	giant1->set_match(this_object(), function1, type1, match1);
    }

    if (!the_sign) {
	the_sign = clone_object("players/padrone/obj/thing");
	the_sign->set_name("sign");
	the_sign->set_alias("roadsign");
	the_sign->set_short("In the middle of the yard, a sign points out directions");
	the_sign->set_read_file("/players/padrone/inside/courtyard_sign.txt");
	the_sign->set_can_get(0);
	move_object(the_sign, this_object());
    }
} /* extra_reset */

reset(arg) {
    extra_reset(arg);
    if (arg)
	return;
    set_light(1);
}

short() {
    if (set_light(0))
	return "The courtyard";
    return "dark room";
}

init() {
    add_action("north", "north");
    add_action("south", "south");
    add_action("east", "east");
    add_action("west", "west");
    add_action("northeast", "northeast");
    add_action("northwest", "northwest");
    add_action("southeast", "southeast");
    add_action("southwest", "southwest");
}

north() {
    this_player()->move_player("north#players/padrone/inside/gate_room");
    return 1;
}

south() {
    this_player()->move_player("south#players/padrone/inside/main_hall");
    return 1;
}

east() {
    this_player()->move_player("east#players/padrone/inside/sheriffs_office");
    return 1;
}

west() {
    this_player()->move_player("west#players/padrone/inside/antonios");
    return 1;
}


northwest() {
    this_player()->move_player("northwest#players/padrone/inside/elizas_office");
    return 1;
}

northeast() {
    this_player()->move_player("northeast#players/padrone/inside/empty_room");
    return 1;
}

southwest() {
    this_player()->move_player("southwest#players/padrone/inside/surgeons_room");
    return 1;
}

southeast() {
    this_player()->move_player("southeast#players/padrone/inside/pmf_office");
    return 1;
}

long(str) {
    if (set_light(0) == 0) {
	write("It is dark.\n");
	return;
    }
    write("You are standing in the courtyard of the Castle of Padrone,\n" +
 	  "a stronghold of Law, Order and Balance.\n" +
 	  "North lies the gate that leads out of the Castle,\n" +
	  "and to main entrance is to the south.\n" +
	  "Some local agencies have opened offices here.\n");
    write("    There are eight exits, leading in all directions:\n" +
	  "    north, south, east, west, northwest, northeast, southwest and southeast.\n");
}

/* For the NEW, IMPROVED monster class: */
setup_arrays() {

    function1 = allocate(1);
    type1 = allocate(1);
    match1 = allocate(1);

    function1[0] = "ticket_check1";
    type1[0] = "arrives";
    match1[0] = "";

    function2 = allocate(1);
    type2 = allocate(1);
    match2 = allocate(1);

    function2[0] = "ticket_check2";
    type2[0] = "arrives";
    match2[0] = "";
} /* setup_arrays */

ticket_check1(str) {  real_ticket_check(str, giant1, "Billy"); }

ticket_check2(str) {  real_ticket_check(str, giant2, "Sam"); }

real_ticket_check(str, giant, giant_name) {
    string who, rest, checker_name;
    object suspect;

    if (sscanf(str, "%s arrives%s", who, rest) != 2)
	return;		
    suspect = present(lower_case(who), this_object());
    if (!suspect)
	return;		
    if (!present("castle ticket", suspect)) {
	
	say(giant_name + " immediately notices that " +
	    who + " hasn't got a ticket.\n");
	giant->attacked_by(suspect);
    }
} /* real_ticket_check */
