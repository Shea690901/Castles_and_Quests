/* walker/gate_control.c */

#include "walker.h"

object pirate;
object helmet, money, cutlass, jacket;

short() {
    if (set_light(0))
	return "The Gate Control Room of the Walking Castle";
    return "dark room";
}

id (str) {
    return !str || str == "switch" || str == "machine" || str == "big machine";
}

long(str) {
    if (set_light(0) == 0){ 
	write("It is dark.\n"); 
	return; 
    }  
    if (str == "switch") {
	write("This is a small switch that can be moved up and down.\n");
	if (call_other(CASTLE, "query_drawbridge_down"))
	    write("It is currently in position 'down'.\n");
	else
    	    write("It is currently in position 'up'.\n");
	return;
    }
    if (str == "machine" || str == "big machine") {
	write("A big machine that occupies this small room.\n");
	return;
    }
    write("This is a small room occupied by a big machine.\n" +
	  "From this room, the drawbridge can be lowered and raised.\n" +
	  "The only obvious exit is east.\n" +
	  "There is a small switch here.\n");
}

reset(arg) {

    if (!arg) {
	set_light(1);
    }

    if (!pirate) {

	pirate = clone_object("obj/monster");
	pirate->set_name("big smelly pirate");
	pirate->set_alias("pirate");
	pirate->set_level(7);
	pirate->set_male();
	pirate->set_al(-150);
	pirate->set_short("A big smelly pirate");
	pirate->set_long("This is a big pirate. He does not smell good.\n");
	pirate->set_aggressive(1);
        move_object(pirate, this_object());

	cutlass = clone_object("obj/weapon");
        cutlass->set_name("cutlass");
        cutlass->set_class(10);
        cutlass->set_value(50);
        cutlass->set_weight(3);
        cutlass->set_short("A cutlass");
        cutlass->set_long("This is a cutlass. It has probably belonged to a pirate.\n");
        move_object(cutlass, pirate);
	pirate->init_command("wield cutlass");

	jacket = clone_object("obj/" + ARMOUR);
	jacket->set_name("leather jacket");
	jacket->set_short("A leather jacket");
	jacket->set_alias("jacket");
	jacket->set_long("A worn but sturdy leather jacket.\n" +
			 "On the back is a lot of rivets making the pattern of a star.\n");
	jacket->set_value(50);
	jacket->set_weight(2);
	jacket->set_ac(2);
	jacket->set_type(ARMOUR);
	move_object(jacket, pirate);
	pirate->init_command("wear jacket");

        helmet = clone_object("obj/" + ARMOUR);
        helmet->set_name("metal helmet");
        helmet->set_ac(1);
        helmet->set_weight(3);
        helmet->set_value(75);
        helmet->set_alias("helmet");
        helmet->set_type("helmet");
        helmet->set_short("A metal helmet");
        helmet->set_long("A metal helmet\n");
        move_object(helmet, pirate);
	pirate->init_command("wear helmet");

	money = clone_object("obj/money");
        money->set_money(1 + random(50));
        move_object(money, pirate);
    }
} /* reset */

init() {
    add_action("move", "move");
    add_action("flip", "flip");
    add_action("do_switch", "switch");
    add_action("east", "east");
} /* init */

move(str) {
    string what, where, player_name;
    int n;

    if (!str)
	return 0;

    if (str == "switch") {
	write("Yes, but in what direction?\n");
        return 1;
    }

    n = sscanf(str, "%s %s", what, where);
    player_name = this_player()->query_name();

    if (n == 2 && (what == "switch")) {
	if (pirate && living(pirate) && present(pirate, this_object()))  {
	    write("You try to move the switch, but the pirate stands in the way.\n");
	    say(player_name +
		" tried to move the controls, but the pirate stands in the way.\n");
	    return 1;
	}
	if (what == "switch") {
	    if (where == "up" || where == "u") {
		say(player_name + " moved the small switch up.\n");
		call_other(CASTLE, "set_drawbridge_down", 0);
	    }
	    else if (where == "down" || where == "d") {
		say(player_name + " moved the small switch down.\n");
		call_other(CASTLE, "set_drawbridge_down", 1);
	    }
	    else
		write("What a strange direction.\n");
	    return 1;
	}
    }
    else
	return 0;
} /* move */

flip(str) {
    if (str != "switch")
	return 0;
    if (call_other(CASTLE, "query_drawbridge_down"))
	return move("switch up");
    else
	return move("switch down");
} /* flip */

do_switch(str) {
    return move("switch " + str);
} /* do_switch */

east() {
    this_player()->move_player("east#players/padrone/walker/gate_room");
    return 1;
}
