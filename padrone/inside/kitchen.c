#include "std.h"

#undef EXTRA_RESET
#define EXTRA_RESET extra_reset();

object cook;

/* For the NEW, IMPROVED monster class: */
string function, type, match;

extra_reset()
{

    if (!cook) {
	object weapon;

	cook = clone_object("obj/monster");	/* NEW, IMPROVED monster class! */
	cook->set_name("Kung-Fu Cook");
	cook->set_alias("cook");
	cook->set_level(random(2) + 5);
	cook->set_male();
	cook->set_hp(80);
	cook->set_al(100);
	cook->set_short("The Incredible Kung-Fu Cook");
	cook->set_ac(0);

	move_object(call_other("players/padrone/outside/front_yard", "make_ticket"), cook);
	move_object(cook, this_object());

	weapon = clone_object("obj/weapon");
	weapon->set_name("meat chopper");
	weapon->set_class(9);
	weapon->set_value(30);
	weapon->set_weight(2);
	weapon->set_alt_name("chopper");
	move_object(weapon, cook);
	cook->init_command("wield chopper");

	/* The NEW, IMPROVED monster calls: */
	if (!function)
	    setup_arrays();
	cook->set_match(this_object(), function, type, match);
    }

    if (!present("coke", this_object())) {
	object coke;
	int i;

	i = random(4) + 1;
	while (i) {
	    i = i - 1;
	    coke = clone_object("obj/drink");
	    coke->set_value("coke#A bottle of Coca Cola#It's the real thing#0#10#0");
	    move_object(coke, this_object());
	} /* while */
    }
}

TWO_EXIT("players/padrone/inside/dining_room", "north",
	 "players/padrone/outside/back_yard", "south",
	 "The kitchen",
	 "You are in the kitchen.\n" +
	 "Gleaming micro-wave ovens and ice-cream machines line the walls,\n" +
	 "along with stacks of potato chips and bottles of coke.\n", 1)


/* For the NEW, IMPROVED monster class: */
setup_arrays() {

    function = allocate(1);
    type = allocate(1);
    match = allocate(1);

    function[0] = "ticket_check";
    type[0] = "arrives";
    match[0] = "";
} /* setup_arrays */


ticket_check(str) {
    string who, rest;
    object suspect;

    if (sscanf(str, "%s arrives%s", who, rest) != 2)
	return;		/* Some strange error! */
    suspect = present(lower_case(who), this_object());
    if (!suspect)
	return;		/* Already gone! */
    if (!present("castle ticket", suspect)) {
	/* A player/monster without a ticket has arrived! -- ATTACK! */
	say("Kung-Fu Cook immediately notices that " +
	    who + " hasn't got a ticket.\n");
	cook->attacked_by(suspect);
    }
} /* check_ticket */
