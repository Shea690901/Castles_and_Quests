/*
 *  wizardshat.c -- the Wizard's Hat (magic!)
 *  Thomas Padron-McCarthy, padrone@lysator.liu.se
 *  Version 5.2 -- Feb 9, 1991
 */

#include "../config.h"

inherit "obj/armour";

status light_is_on, is_invisible;
object dest_room;
int hat_power;

reset(arg) {
    ::reset(arg);

    if (!arg) {
	/* First reset */
	set_name("wizard's hat");
	set_alias("hat");
	set_type("helmet");
	set_short("Wizard's Hat");
	set_ac(1);
	set_value(200);
	set_weight(2);
	hat_power = 100;
	light_is_on = 0;
	is_invisible = 0;

	dest_room = "players/padrone/workroom";
    }
    else {
	/* Periodical reset */
	if (!light_is_on) {
	    if (hat_power < 100)
		hat_power = 100;
	    if (worn)
		tell_object(worn_by, "You feel the hat pulse as it gets new power.\n");
	}
	else if (worn) {
	    tell_object(worn_by, "You feel the hat pulse as it gets new power,\n" +
			         "but since the light in the hat is on,\n" +
			         "all the new power is used up by the light. Sorry.\n");
	}
    }
} /* reset */


init() {
    add_action("do_read", "read");
    /* This version of the hat is activated by saying things: */
    add_action("do_say", "say");
    add_action("hatstat", "hatstat");
    ::init();
} /* init */

long(str) {	/* Used instead of long() in obj/armour. */
    write("This hat is made of blue velvet with stars and moons in silver.\n" +
	  "It is high and pointed, and quite obviously a Wizard's Hat.\n");
    if (worn)
	write("It fits very well, and since it is thick and well made\n" +
	      "it probably offers some protection against blows.\n");
    else
	write("The hat is thick and well made.\n" +
	      "As you look inside, you see a label.\n");
} /* long */

id(str) {	/* Used instead of id() in obj/armour. */
    return    (str == name) || (str == type) || (str == alias)
	   || (str == "wizards hat" ) || (str == "wizardshat") || (str == "wizardhat");
} /* id */

drop(silently) {
    if (worn) {
	hat_off();
    }
    ::drop(silently);
} /* drop */

remove(str) {
    if (!id(str))
	return 0;
    if (worn) {
	hat_off();
    }
    return ::remove(str);
} /* remove */

hat_off() {
    if (light_is_on) {
	light_is_on = 0;
	set_light(-1);
	tell_object(worn_by, "The hat goes dark.\n");
    }
    if (is_invisible) {
	is_invisible = 0;
	this_player()->vis();
	/* The player is told by "vis" that he is visible! */
    }
} /* hat_off */

/*--------- The magic is (mostly) below this line  -----------*/

do_say(str) {
    if (!str)
	return 0;

    if (str == "memorator situ")
	{ say_it(str); set_destination(); }
    else if (str == "hoppla jump")
	{ say_it(str); teleport(); }
    else if (str == "lux")
	{ say_it(str); light(); }
    else if (str == "finito lux")
	{ say_it(str); dark(); }
    else if (str == "vanish zap")
	{ say_it(str); invisible(); }
    else if (str == "solidus reflectus")
	{ say_it(str); visible(); }
    else if (str == "ego reparator")
	{ say_it(str); heal(); }
    else if (str == "pratus status")
	{ say_it(str); stat(); }
    else if (str == "sobrus instamatic")
	{ say_it(str); sober(); }
    else if (str == "glug glug")
	{ say_it(str); drink_power(); }
    else
	return 0;
    return 1;	/* If a hat command word! */
}

say_it(str) {
    say(this_player()->query_name() + " says: " + str + "\n");
}

do_read(str)
{
    if (str != "label")
	return 0;
    else if (worn) {
	write("You cannot read the label inside the hat while you are wearing it.\n");
	return 1;
    }
    else {
	write("The label inside the hat reads:\n" +
	      "    PadMagic Inc. Wizard's Hat Model 5\n" +
	      "    This high quality magic item has been carefully designed and manufactured\n" +
	      "    with the sole objective to satisfy your demanding requirements.\n" +
	      "    It offers invaluable assistance in the areas of transport,\n" +
      	      "    illumination, visibility and emergency medicine.\n" +
	      "    Note: Persons of limited experience have reported slight problems\n" +
	      "          in the handling of this sophisticated equipment.\n" +
	      "    This is a prototype specimen and no warranty whatsoever applies.\n");
	return 1;
    }
} /* do_read */

set_destination(arg) {
    object the_env;
    string the_file_name, junk;

    the_env = environment(this_player());
    the_file_name = file_name(the_env);

    /*  On Genesis, the rules don't allow teleporting into other castles.
     *  On Nanny, at least, we can teleport anywhere, except for the "realms" check.
     */
#ifdef GENESIS
    if (   the_file_name
	&& sscanf(the_file_name, "room/%s", junk) != 1
	&& sscanf(the_file_name, "players/padrone/%s", junk) != 1) {
        write("You try to set the teleport destination of your Wizard's Hat,\n" +
	      "but it doesn't seem to work in this place.\n");
    }
    else
#endif

    if (the_env->realm() == "NT") {
        write("You try to set the teleport destination of your Wizard's Hat,\n" +
	      "but this place has been magically protected against teleporting.\n");
    }
    else if (use_hat(1)) {
        write("You set the teleport destination of your Wizard's Hat.\n");
        dest_room = the_env;
    }
    return 1;
} /* set destination */

teleport(arg) {
    object from_realm, dest_realm;

    from_realm = environment(this_player())->realm();
    dest_realm = dest_room->realm();

    if (arg)
	return 0;
    else if (use_hat(10 + random(11))) {
	if (!dest_room) {
            write("The hat says in a squeeky voice: Yes, yes, but where?\n");
        } else {
            if ((from_realm == dest_realm) && (from_realm != "NT")) {
		write("As you activate your Wizard's Hat everything shimmers away...\n");
		say(this_player()->query_name() + " shimmers and fades.\n");
		move_object(this_player(), dest_room);
		say(this_player()->query_name() + " shimmers into solidity.\n");
		this_player()->look(0);
            } else {
                write("The Wizard's Hat struggles to take you with it, but fails.\n");
                write("The hat shimmers and fades!\n");
		worn_by->stop_wearing(name);
		if (light_is_on)
		    { light_is_on = 0; set_light(-1); }
		if (is_invisible)
		    { is_invisible = 0; this_player()->vis(); }
		worn_by = 0;
		worn = 0;
		move_object(this_object(), dest_room);
		this_player()->add_weight(-weight);
	    }
	}
    }
    return 1;
} /* teleport */

light(arg) {
    if (arg)
	return 0;
    else if (light_is_on) {
	write("The light is already on.\n");
    }
    else if (use_hat(10)) {
	set_light(1);
	write("You turn on the light in the Wizard's Hat.\n");
	say("The Wizard's Hat starts to shine brightly.\n");
	light_is_on = 1;
    }
    return 1;
} /* light */

dark(arg) {
    if (arg)
	return 0;
    else if (!light_is_on) {
	write("But the light was not on.\n");
    }
    else {
	set_light(-1);
	write("You turn off the light in the Wizard's Hat.\n");
	say("The Wizard's Hat goes dark.\n");
	light_is_on = 0;
    }
    return 1;
} /* dark */

invisible(arg)
{
    if (arg)
	return 0;
    else if (use_hat(20)) {
	write("The hat tries to make you invisible...\n");
	this_player()->invis();
	is_invisible = 1;
	set_heart_beat(1);
    }
    return 1;
} /* invisible */

heart_beat() {
    if (!is_invisible)
	set_heart_beat(0);	/* Hat has been removed, inv was lost */
    if (!random(6)) {
	/* Might not be worn at this stage... */
	set_heart_beat(0);
	worn_by->vis();
	/*  From the heart beat, so the player is NOT
	 *  told by "vis" that he is visible!
	 */
	tell_object(worn_by, "You are suddenly visible again.\n");
    }
} /* heart_beat */

visible(arg)
{
    if (arg)
	return 0;
    else if (use_hat(2)) {
	  write("The hat tries to make you visible...\n");
	  this_player()->vis();
	  is_invisible = 0;
    }
    return 1;
} /* visible */

heal(arg) {
    int level;

    if (arg)
	return 0;

    if (worn)
	write("The hat draws on its power and tries yo heal you...\n");

    if (use_hat(40)) {
	level = this_player()->query_level();
	this_player()->heal_self(3 * random(level) + random(100) + 20);
	write("You feel much better.\n");
	if (this_player()->query_frog()) {
	    write("And then the hat proceeds to cure that strange greenness...\n");
	    if (use_hat(30))
		this_player()->frog_curse(0);
	}
    }
    return 1;
} /* heal */

hatstat(arg) {
    if (arg && !id(arg))
	return 0;
    else if (this_player()->query_level() < 20)
	return 0;
    else {
	write("Wizard's Hat Status:\n" +
	      "    Hat Power: " + hat_power + "%\n" +
	      "    Teleport Destination: ");

	if (dest_room)
	    write(dest_room->short());
	else
	    write("None");
	write("\nCommands (say them!): Look at the note in Padrone's lab.\n");
	return 1;
    }
} /* hatstat */

stat(arg) {
    string power_string;
    int est;
    int level;

    if (arg)
	return 0;

    if (!use_hat(1))
	return 1;

    level =  this_player()->query_level();
    if (level < 20) {
	int noise;
	noise =  random (2 * (20 - level));
	if (random(2))
	    noise = 0 - noise;
	est = hat_power + noise;
    }
    else
	est = hat_power;

    if (est > 90)
	power_string = "very good";
    else if (est > 60)
	power_string = "good";
    else if (est > 50)
	power_string = "a bit tired";
    else if (est > 20)
	power_string = "tired";
    else
	power_string = "exhausted (phew!)";

    write("The hat says in a squeeky voice: I feel " + power_string +
	  ". I think I'm " + est + "% full");
    if (dest_room)
	write(",\nand I know where to go.\n");
    else
	write(".\n");
    return 1;
} /* stat */

sober(arg) {

    if (!use_hat(30))
	return 1;
    this_player()->add_intoxination(- this_player()->query_intoxination());
    write("You feel sober.\n");
    return 1;
} /* sober */

drink_power() {

    if (!use_hat(1))
	return 1;
    this_player()->restore_spell_points(hat_power);
    hat_power = 0;
    write("You drain the hat of its power.\n");
    return 1;
} /* drink_power */

use_hat(pp) {
    int level;

    if (!worn || worn_by != this_player()) {
	write("You think that the Wizard's Hat moved, but nothing further happens.\n");
	return 0;
    }

    level = this_player()->query_level();
    hat_power = hat_power - pp;
    if (hat_power < 0)
	hat_power = 0;
    if (hat_power > (20 + random(10) + (20 - level))) {
	/* The hat worked OK */
	return 1;
    }
    else {
	/* The hat was too tired */
	write("The hat seems strangely heavy, and nothing happens.\n");
	return 0;
    }
} /* use_hat */

explode_hat() {
    object ob, this_ob;

    /* Overload! The hat explodes... */
    write("The hat shrieks 'Help! Overload!' and explodes in a blinding flash.\n");

    /* First: burn the others in the same room! */
    say(this_player()->query_name() + "'s hat explodes!\n");
    say("You are burned by the explosion.\n");
    ob = first_inventory(environment(this_player()));
    while(ob) {
	/* We cannot do next_inventory(ob) if ob died and was destructed! */
	this_ob = ob;
	ob = next_inventory(ob);
	if (this_ob != this_object() && living(this_ob)) {
	    this_ob->hit_player(random(10));
	}
    }

    /* Always worn at this stage... */
    write("You are burned by the explosion.\n");
    worn_by->hit_player(random(20) + 1);
    worn_by->stop_wearing(name);
    if (light_is_on)
	{ light_is_on = 0; set_light(-1); }
    if (is_invisible)
	{ is_invisible = 0; this_player()->vis(); }
    worn_by = 0;
    worn = 0;
    move_object(this_object(), "players/padrone/store");
    this_player()->add_weight(-weight);
    return 0;
} /* explode_hat */
