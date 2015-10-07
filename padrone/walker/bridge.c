/* walker/bridge.c -- control room for the walking castle */

#include "walker.h"
#include "../../../obj/door.h"

object pilot, pirate1, pirate2, pirate_king;

short() {
    if (set_light(0))
	return "The Bridge of the Walking Castle";
    return "dark room";
}

id_stick(str) {
    return str == "joystick" || str == "stick" || str == "lever";
}

id_switch(str) {
    return str == "switch";
}

id_sign(str) {
    return str == "sign" || str == "small sign";
}

id_view(str) {
    return str == "view" || str == "the view";
}

id_windows(str) {
    return str == "windows" || str == "window";
}

id (str) {
    return id_stick(str) || id_switch(str) || id_sign(str) || id_view(str) || id_windows(str);
}

long(str) {

    if (set_light(0) == 0) {
	write("It is dark.\n");
	return;
    }

    if (id_stick(str)) {
	write("This is a big lever made of wood.\n" +
	      "It is fastened to the floor, and it looks like\n" +
	      "it could be moved in different directions.\n");
	return;
    }
    if (id_switch(str)) {
	write("This is a small switch that can be moved up and down.\n");
	if (call_other(CASTLE, "query_drawbridge_down"))
	    write("It is currently in position 'down'.\n");
	else
    	    write("It is currently in position 'up'.\n");
	return;
    }
    if (id_sign(str)) {
	return read(str);
    }
    if (id_windows(str)) {
	write("The windows are big and very clear.\n" +
	      "They provide a good view of the castle's surroundings.\n");
	return;
    }
    if (id_view(str)) {
	write("You look at the view through the windows.\n");
	say(this_player()->query_name() +
	    " looks at the view through the windows.\n");
	if (call_other(CASTLE, "query_airborne"))
	    write("You see nothing but clouds.\n");
	else {
	    write("    Looking through the windows you see:\n\n");
	    move_object(this_player(), call_other(CASTLE, "query_environment"));
	    this_player()->look(0);
	    move_object(this_player(), this_object());
	}
	return;
    }

    write("This is the bridge of the Walking Castle.\n" +
	  "It is a room with big windows, built on top of the gatehouse.\n");
    if (call_other(CASTLE, "query_airborne"))
	write("Outside the windows you see nothing but clouds.\n");
    else {
	write("Outside the windows you see " +
	      call_other(CASTLE, "query_environment")->short() + ".\n");
	write("Maybe you should look at the view more carefully?\n");
    }
    write("A big wooden joystick in the floor can be moved in all directions,\n" +
	  "and a small switch can be moved up and down.\n");
    write("You also notice a small brass sign on the wall.\n");
    write("    The only obvious exit is north.\n");
} /* long */

reset(arg) {
    object key, sword, helmet, money, bag, cutlass, chainmail;

    if (!arg) {
	/* First reset */
	set_light(1);
    }

    if (!pilot) {
	pilot = clone_object("obj/monster");
	pilot->set_name("pilot");
	pilot->set_alias("castle pilot");
	pilot->set_level(3);
	pilot->set_male();
	pilot->set_wc(5);
	pilot->set_ep(140);
	pilot->set_al(-100);
	pilot->set_short("The pilot who is controlling the walking castle");
	pilot->set_long("This is a pilot. Using the controls on the bridge,\n" +
			"he can move the walking castle.\n");
	pilot->set_aggressive(0);
        move_object(pilot, this_object());
    }

    if (!pirate1) {
	pirate1 = clone_object("obj/monster");
	pirate1->set_name("very ugly pirate");
	pirate1->set_alias("pirate");
	pirate1->set_level(4);
	pirate1->set_male();
	pirate1->set_al(-100);
	pirate1->set_short("A very ugly pirate");
	pirate1->set_long("This is a medium-sized and very ugly pirate.\n");
	pirate1->set_aggressive(1);
        move_object(pirate1, this_object());

	sword = clone_object("obj/weapon");
        sword->set_name("knife");
        sword->set_class(5);
        sword->set_value(8);
        sword->set_weight(2);
        sword->set_short("A knife");
        move_object(sword, pirate1);
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
        money->set_money(1 + random(50));
        move_object(money, pirate1);
    }

    if (!pirate2) {
	pirate2 = clone_object("obj/monster");
	pirate2->set_name("ugly pirate");
	pirate2->set_alias("pirate");
	pirate2->set_level(2);
	pirate2->set_male();
	pirate2->set_al(-100);
	pirate2->set_short("An ugly pirate");
	pirate2->set_long("This is a small and ugly pirate.\n");
	pirate2->set_aggressive(1);
        move_object(pirate2, this_object());

	sword = clone_object("obj/weapon");
        sword->set_name("knife");
        sword->set_class(5);
        sword->set_value(8);
        sword->set_weight(2);
        sword->set_short("A knife");
        move_object(sword, pirate2);
	pirate2->init_command("wield knife");

        helmet = clone_object("obj/" + ARMOUR);
        helmet->set_name("metal helmet");
        helmet->set_ac(1);
        helmet->set_weight(3);
        helmet->set_value(75);
        helmet->set_alias("helmet");
        helmet->set_type("helmet");
        helmet->set_short("A metal helmet");
        helmet->set_long("A metal helmet\n");
        move_object(helmet, pirate2);
	pirate2->init_command("wear helmet");

	money = clone_object("obj/money");
        money->set_money(50 + random(100));
        move_object(money, pirate2);
    }

    if (!pirate_king) {
	pirate_king = clone_object("obj/monster");
	pirate_king->set_name("pirate king");
	pirate_king->set_alias("king");
	pirate_king->set_level(12);
	pirate_king->set_male();
	pirate_king->set_hp(200);
	pirate_king->set_al(-200);
	pirate_king->set_short("The pirate king");
	pirate_king->set_long("This is the pirate king. He is big and very very ugly.\n");
	pirate_king->set_aggressive(1);
        move_object(pirate_king, this_object());

	cutlass = clone_object("obj/weapon");
        cutlass->set_name("cutlass");
        cutlass->set_class(10);
        cutlass->set_value(50);
        cutlass->set_weight(3);
        cutlass->set_short("A cutlass");
        cutlass->set_long("This is a cutlass. It has probably belonged to a pirate.\n");
        move_object(cutlass, pirate_king);
	pirate_king->init_command("wield cutlass");

	chainmail = clone_object("obj/" + ARMOUR);
        chainmail->set_name("chainmail");
        chainmail->set_alias(ARMOUR);
        chainmail->set_type(ARMOUR);
        chainmail->set_ac(3);
        chainmail->set_value(500);
        chainmail->set_weight(5);
        chainmail->set_short("A suit of chainmail");
        move_object(chainmail, pirate_king);
	pirate_king->add_weight(5);
	pirate_king->init_command("wear chainmail");

        helmet = clone_object("obj/" + ARMOUR);
        helmet->set_name("metal helmet");
        helmet->set_ac(1);
        helmet->set_weight(3);
        helmet->set_value(75);
        helmet->set_alias("helmet");
        helmet->set_type("helmet");
        helmet->set_short("A metal helmet");
        helmet->set_long("A metal helmet\n");
        move_object(helmet, pirate_king);
	pirate_king->init_command("wear helmet");

	bag = clone_object("obj/bag");
        move_object(bag, pirate_king);
	money = clone_object("obj/money");
        money->set_money(100 + random(300));
        move_object(money, bag);

	MAKE_KEY(key, "bullet-proof", "walkervault")
        move_object(key, bag);
    }
} /* reset */

init() {
    add_action("move", "move");
    add_action("flip", "flip");
    add_action("do_switch", "switch");
    add_action("read", "read");
    add_action("north", "north");
} /* init */

move(str) {
    string what, where, player_name;
    int n;

    if (!str)
	return 0;

    if (id_stick(str) || id_switch(str)) {
	write("Yes, but in what direction?\n");
        return 1;
    }

    n = sscanf(str, "%s %s", what, where);
    player_name = this_player()->query_name();

    if (n == 2 && (id_stick(what) || id_switch(what))) {
	if (pilot && living(pilot) && present(pilot, this_object())) {
	    write("You try to move the controls, but the pilot stands in the way.\n");	
	    say(player_name +
		" tried to move the controls, but the pilot stands in the way.\n");
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

	if (where == "u") where = "up";
	if (where == "d") where = "down";
	if (where == "n") where = "north";
	if (where == "s") where = "south";
	if (where == "e") where = "east";
	if (where == "w") where = "west";
	if (where == "ne") where = "northeast";
	if (where == "nw") where = "northwest";
	if (where == "se") where = "southeast";
	if (where == "sw") where = "southwest";

	say(player_name + " moved the joystick " + where + ".\n");
	if (   where == "north" || where == "n"
	    || where == "south" || where == "s"
	    || where == "east" || where == "e"
	    || where == "west" || where == "w"
	    || where == "northeast" || where == "ne"
	    || where == "northwest" || where == "nw"
	    || where == "southeast" || where == "se"
	    || where == "southwest" || where == "sw") {
	    call_other(CASTLE, "move_castle", where, 0); /* 0 = "not auto-moving" */
	}
	else if (where == "up") {
	    call_other(CASTLE, "set_airborne", 1);
	}
	else if (where == "down") {
	    call_other(CASTLE, "set_airborne", 0);
	}
	else
	    write("What a strange direction.\n");
	return 1;
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

read(str) {
    if (id_sign(str)) {
	say(this_player()->query_name() + " reads the small sign.\n");
	write("The small brass sign is nailed to the wall, and it says:\n");
	write("    Padrone's Walking Castle, version\n    " + WALKER_VERSION + ".\n");
	return 1;
    }
    else
	return 0;
} /* read */

north() {
    this_player()->move_player("north#players/padrone/walker/walkway");
    return 1;
}

pilot_is_alive() {
    return pilot && living(pilot) && present(pilot, this_object());
}
