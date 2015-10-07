/*
 *  bodyguard.c - a bodyguard
 *  Thomas Padron-McCarthy (padrone), Email: padrone@lysator.liu.se
 *  Share and enjoy. No rights reserved, except the right to reserve rights.
 *	This object is a specialized bodyguard-monster.
 *	Since there might be many of them, and we need
 *	some unique variables, we cannot just use the room.
 *  1. Create a bodyguard monster
 *     (i. e. clone this file, "players/padrone/obj/bodyguard").
 *  2. Name it by calling set_name in the monster object.
 *  3. THEN call set_guarded, with the player (or monster!) OBJECT
 *     to be guarded as argument.
 *     The bodyguard will then be initialized,
 *     and all its parameters set - except for the name.
 *  If the object to be guarded changes, call set_guarded again.
 *  If the name of guarded is changed, you must call set_guarded again.
 *  It automatically handles new objects with the same name, e. g. if
 *  a player quits and then logs in again.
 *
 */

#define VERSION "3.5.1 (April 24, 1992)"
#define COST 1000

inherit "obj/monster";
add_money(m) { money = money + m; }	/* Without add_worth! */

object guarded;
string guarded_name, guarded_cap_name;
status init_done, employed, smart, sleeping, lost;

/* For the NEW, IMPROVED monster class: */
string function, type, match;

/*--------------------------------------------------------------------------*/

get_honorary() {
    if (!guarded || guarded->query_male())
	return "Sir";
    else if (guarded->query_female())
	return "Madam";
    else
	return "Creature";
} /* get_honorary */

/*--------------------------------------------------------------------------*/

reset(arg) {
    ::reset(arg);
    if (!arg) {
	set_name("zero");
	set_alias("bodyguard");
	set_race("bodyguard");
	set_level(1);
	set_short("Zero the uninitialized bodyguard");
	move_object(clone_object("obj/soul"), this_object());
	init_done = 0;
    }
} /* reset */

set_guarded(obj) {
    guarded = obj;
    if (guarded) {
	guarded_cap_name = guarded->query_name();
	guarded_name = lower_case(guarded_cap_name);
	log_file("padrone", ctime(time()) + ": " + cap_name + " will now guard " +
		 guarded_cap_name + "\n");
	initialize_bodyguard();
    }
} /* set_guarded */

show_stats() {
    ::show_stats();
    write("Additional bodyguard status:\n");
    write("  guarded = "); write(guarded); write (", guarded_name = " + guarded_name + "\n");
    write("  employed = " + employed + ", sleeping = " + sleeping);
    write(", lost = " + lost + ", smart = " + smart + "\n");
    if (guarded) {
	write("  Current location of guarded: ");
	write(environment(guarded));
	write("\n");
    }
    write("  Current location of bodyguard: ");
    write(environment(this_object()));
    write("\n");
    return 1;
} /* show_stats */

initialize_bodyguard() {
    int level, alignment;

    /* "guarded" must be set here! This function is only called from set_guarded! */
    employed = 1;
    if (!init_done) {
	level = random(guarded->query_level() / 5) + 1;
	set_level(level);
	alignment = guarded->query_al();
	if (alignment > 1000)
	    alignment = 1000;
	else if (alignment < -1000)
	    alignment = -1000;
	set_al(alignment);
	init_done = 1;
    }
    set_short(cap_name + ", " +
	      guarded_cap_name + "'s bodyguard");
    set_long(cap_name + " is a bodyguard, currently" +
	     " employed by " + guarded_cap_name + ".\n" +
	     cap_name +
	     " is dressed in a dark suit and is wearing dark sunglasses.\n");
    set_spell_mess1(cap_name + " protects " +
		    guarded_cap_name + " with intrepid courage.");
    set_spell_mess2(cap_name + " protects " +
		    guarded_cap_name + " with intrepid courage.");
    set_chance(15);
    set_spell_dam(0);
    set_aggressive(0);
    
    /* The NEW, IMPROVED monster calls: */
    if (!function)
	setup_arrays();
    set_match(this_object(), function, type, match);
} /* initialize_bodyguard */

/* For the NEW, IMPROVED monster class: */
setup_arrays() {

    function = allocate(9);
    type = allocate(9);
    match = allocate(9);

    function[0] = "handle_say"; type[0] = "says"; match[0] = "";
		     		type[1] = "tells you:"; match[1] = " ";
    function[2] = "handle_arrival"; type[2] = "arrives"; match[2] = "";
    function[3] = "handle_leaving"; type[3] = "leaves";  match[3] = "";
    function[4] = "handle_giving"; type[4] = "gives"; match[4] = "";
    function[5] = "check_fighting"; type[5] = "hit"; match[5] = "";
    				    type[6] = "miss"; match[6] = "";
    				    type[7] = "smash"; match[7] = "";
                                    type[8] = "massacre"; match[8] = "";
} /* setup_arrays */

/*--------------------------------------------------------------------------*/

check_guarded() {

    /* log_file("padrone", cap_name + ", check_guarded\n"); */

    if (!employed)
	return 0;
    if (!guarded)
	guarded = find_living(guarded_name);

    if (!guarded) {
	lost = 1;
	return 0;
    }
    else if (present(guarded, environment(this_object()))) {
	if (lost) {
	    notify(cap_name + " says: Hello, " + guarded_cap_name +
		   "! Please don't run away like that again!\n");
	    lost = 0;
	}
	return 1;
    }
    else {
	if (!lost) {
	    tell_object(guarded, cap_name +
			" tells you: " + get_honorary() + "! Come back here!\n");
	    lost = 1;
	}
	return 0;
    }
} /* check_guarded */

handle_leaving(str)
{
    string who, rest;

    /* log_file("padrone", cap_name + ", handle_leaving: " + str); */

    if (sleeping || !employed)
	return;
    if (sscanf(str, "%s leaves %s.\n", who, rest) != 2) {
	notify(cap_name + " looks brain damaged.\n");
	return;
    }
    if (who == guarded_cap_name)
	init_command(rest);
    if (check_guarded())
	random_attack();
} /* handle_leaving */

handle_arrival(str){
    string who, rest;

    /* log_file("padrone", cap_name + ", handle_arrival: " + str); */

    if (sleeping)
	return;
    if (sscanf(str, "%s arrives%s", who, rest) != 2) {
	notify(cap_name + " looks brain damaged.\n");
	return;
    }

    if (!employed) {
	init_command("bow " + who);
	notify(cap_name + " says: I am a bodyguard, and I am for hire for " +
	       COST + " gold coins.\n");
    }
    else if (!check_guarded())
	notify(cap_name + " says: Excuse me, " + who +
	       ", but have you seen " + guarded_cap_name + "?\n");
    else
	random_attack();
} /* handle_arrival */

random_attack() {
    object ob, this_ob;
    
    if (!employed)
	return;
    ob = first_inventory(environment(this_object()));
    while (ob) {
	this_ob = ob;
	ob = next_inventory(ob);
	if (   living(this_ob) && this_ob != this_object() && this_ob != guarded
	    && !random(10) && !smart && this_ob->query_npc() && this_ob->short()) {
	    notify(cap_name + " says: You! " + this_ob->query_name() +
		   "! Don't you even LOOK at " + guarded_cap_name + "!\n");
	    attacked_by(this_ob);
	    return;
	} /* Obnoxious attack! */
    } /* while */
} /* random_attack */

check_fighting() {
    object enemy;

    /* log_file("padrone", cap_name + ", check_fighting\n"); */

    if (sleeping) {
	notify(cap_name + " is awakened by the sound of fighting.\n");
	sleeping = 0;
    }
    if (!employed)
	return;
    if (!guarded) {
	lost = 1;
	return 0;
    }
    enemy = guarded->query_attack();
    if (enemy == this_object()) {
	notify(cap_name + " says: I hate you, " +
	       guarded_cap_name + ", and I hate this job! I quit!\n");
	make_unemployed();
    }
    else if (enemy && present(enemy, environment(this_object()))) {
	if (enemy != query_attack())
	    notify(cap_name + " says: Leave " + guarded_cap_name + " alone, jerk!\n");
	attacked_by(enemy);
    }
} /* check_fighting */

make_unemployed() {

    employed = 0;
    set_short(cap_name + ", " +
	      guarded_cap_name + "'s ex-bodyguard");
    set_long(cap_name + " is a bodyguard, who used to be employed by " +
	     guarded_cap_name + ".\n" +
	     cap_name +
	     " is dressed in a dark suit, but has removed the dark sunglasses,\n" +
	     "and is obviously not working as a bodyguard right now, but\n" +
	     "maybe you should spend " + COST + " gold coins to hire this bodyguard?\n");
    set_chance(0);
} /* make_unemployed */

handle_giving(str) {
    string who, what, whom;
    int the_sum;
    object the_obj;

    /* log_file("padrone", cap_name + ", handle_giving: " + str); */

    if (sscanf(str, "%s gives %s to %s.\n", who, what, whom) == 3) {
	the_obj = present(what, this_object());
	if (id(lower_case(whom)) && the_obj) {
	    /* Gave it to me, and I have it now. */
	    if (sleeping) {
		notify(cap_name + " is asleep an just drops the " + what + ".\n");
		add_weight(-the_obj->query_weight());
		move_object(the_obj, environment(this_object()));
	    }
	    else if (the_obj->weapon_class())
		try_wield(the_obj);
	    else if (the_obj->armour_class())
		init_command("wear " + what);
	    else {
		init_command("drink " + what);
		init_command("eat " + what);
		init_command("use " + what);
		init_command("apply " + what);
	    }
	}
    }
    else if (sscanf(str, "%s gives you %d gold coins.\n", who, the_sum) == 2) {
	if (sleeping) {
	    notify(cap_name + " is awakened by the sound of gold coins.\n");
	    sleeping = 0;
	}
	if (employed && who == guarded_cap_name)
	    notify(cap_name + " says: Thank you, " + get_honorary() + "!\n");
	else if (the_sum < COST) {
	    notify(cap_name + " says: Thanks for your contribution.\n");
	}
	else {
	    object ng;
	    ng = present(lower_case(who), environment(this_object()));
	    if (ng) {
		notify(cap_name + " says: Ok, boss! I'll work for you!\n");
		if (employed && guarded && present(guarded, environment(this_object())))
		    notify(cap_name + " says: Bye, bye, " + guarded_cap_name +
			   "! Have a nice life.\n");
		else if (employed && guarded)
		    tell_object(guarded, cap_name + " tells you: Bye, bye, " +
				guarded_cap_name + "! Have a nice life.\n");
		set_guarded(ng);
		lost = 0;
		employed = 1;
	    }
	    else {
		notify(cap_name + " looks confused.\n");
	    }
	}
    }
} /* handle_giving */

handle_say(str) {
    object talker;
    string lphrase, who, phrase, a, b, whom, what, where;
    status was_told;

    /* log_file("padrone", cap_name + ", handle_say: " + str); */

    if (   (sscanf(str, "%s says: %s\n", who, phrase) == 2)
	|| (sscanf(str, "%s says \"%s\"\n", who, phrase) == 2)) /* Morgar's say with quotes! */
	was_told = 0;
    else if (sscanf(str, "%s tells you: %s\n", who, phrase) == 2)
	was_told = 1;
    else {
	notify(cap_name + " looks brain damaged.\n");
	return;
    }
    lphrase = lower_case(phrase);

    /* Case 1: If the bodyguard is sleeping, it will react iff anybody talks about waking */
    if (sleeping) {
	if (   sscanf(lphrase, "%swake%s", a, b) == 2
	    || sscanf(lphrase, "%sgood morning%s", a, b) == 2
	    || sscanf(lphrase, "%sgoodmorning%s", a, b) == 2) {
	    notify(cap_name + " suddenly jumps to attention!\n");
	    notify(cap_name + " says: Good morning!\n");
	    sleeping = 0;
	}
	else {
	    notify(cap_name + " is asleep and snores loudly.\n");
	}
	return;
    } /* If asleep! */

    if (!employed)
	return;

    check_guarded();

    /* Case 3: The bodyguard is lost an just gets a direction */
    if (lost) {
	where = 0;
	if (sscanf(phrase, "%snorth%s", a, b) == 2) {
	    where = "north";
	}
	else if (sscanf(phrase, "%ssouth%s", a, b) == 2) {
	    where = "south";
	}
	else if (sscanf(phrase, "%seast%s", a, b) == 2) {
	    where = "east";
	}
	else if (sscanf(phrase, "%swest%s", a, b) == 2) {
	    where = "west";
	}
	else if (sscanf(phrase, "%ssoutheast%s", a, b) == 2) {
	    where = "southeast";
	}
	else if (sscanf(phrase, "%ssouthwest%s", a, b) == 2) {
	    where = "southwest";
	}
	else if (sscanf(phrase, "%snortheast%s", a, b) == 2) {
	    where = "northeast";
	}
	else if (sscanf(phrase, "%sup%s", a, b) == 2) {
	    where = "up";
	}
	else if (sscanf(phrase, "%sdown%s", a, b) == 2) {
	    where = "down";
	}
	if (where) {
	    say(cap_name + " says: " + capitalize(where) +
		", you say! Thank you for your information!\n");
	    init_command(where);
	    if (!check_guarded())
		notify(cap_name + " says: Excuse me, " + 
		       ", but has anyone seen " + guarded_cap_name + "?\n");
	    return;
	}
	else if (sscanf(phrase, "%syes%s", a, b) == 2) {
	    notify(cap_name + " says: Please, in which direction can I find " + 
		   guarded_cap_name + "?\n");
	    return;
	}
    }

    /* Case 3: Someone tells the bodyguard something */
    if (   (sscanf(lphrase, "%s, %s", whom, what) == 2 && id(whom))
	|| (sscanf(lphrase, "%s %s", whom, what) == 2 && id(whom))
	|| (sscanf(lphrase, "%s", what) == 1 && was_told)) {

	/* log_file("padrone", cap_name + ", command: " + str); */

	while (sscanf(what, "%s!", what))
	    { }
	while (sscanf(what, "%s.", what))
	    { }

	if (who == "Padrone" && what == "get smart") {
	    /* A special feature, ONLY for Padrone himself! */
	    notify(cap_name +
		   " says: Yes Sir My Creator Sir! I feel much smarter now!\n");
	    smart = 1;
	}
	else if (who == "Padrone" && what == "get stupid") {
	    /* Another special feature for Padrone */
	    notify(cap_name +
		   " says: Yes Sir My Creator Sir! I feel much more stupid now!\n");
	    smart = 0;
	}
	else if (who == guarded_cap_name || who == "Padrone") {
	    handle_command(what);
	    check_guarded();
	}
	else {
	    notify(cap_name + " says: Get lost, jerk! I don't follow your orders!\n");
	    init_command("kick " + lower_case(who));
	}
    }
} /* handle_say */


/* handle_command
 *	The bodyguard has been ordered to perform a command,
 *	and the order was given by the guarded player (or by Padrone).
 *	If this is one of the special bodyguard commands
 *	(kill, guard, sleep, wield and their synonyms),
 *	then do it.
 *	Else, just do an init_command.
 */

handle_command(cmdline) {
    string cmd, arg;
    object obj;
    int n;

    /* log_file("padrone", cap_name + ", handle_command(\"" + cmdline + "\")\n"); */

    cmd = ""; arg = 0;
    n = sscanf(cmdline, "%s %s", cmd, arg);
    if (n == 0)
	cmd = cmdline;

    if (query_attack()) {
	notify(cap_name + " is in the middle of a fight and doesn't listen.\n");
	return;
    }

    if (cmd == "kill") {
	if (!arg) {
	    notify(cap_name + " says: Kill who?\n");
	    return;
	}

	obj = present(lower_case(arg), environment(this_object()));
	if (!obj) {
	    notify(cap_name + " says: But there is no " + arg + " here, " +
		   get_honorary() + "!\n");
	}
	else if (!living(obj) || obj == this_object() || obj == guarded) {
	    notify(cap_name + " says: Very funny.\n");
	}
	else if (!obj->query_npc()) {
	    notify(cap_name + " says: No way, " + get_honorary() + "! " +
		   capitalize(arg) + " looks much too dangerous!\n");
	}
	else {
	    notify(cap_name + " says: Yes " + get_honorary() +
		   "! I will immediately kill " + arg + "!\n");
	    attacked_by(obj);
	}
	return;
    }
    else if (cmd == "guard") {
	if (!arg) {
	    notify(cap_name + " says: Guard who?\n");
	    return;
	}

	obj = present(lower_case(arg), environment(this_object()));
	if (!obj) {
	    notify(cap_name + " says: But there is no " + arg + " here, " +
		   get_honorary() + "!\n");
	}
	else if (!living(obj) || obj == this_object()) {
	    notify(cap_name + " says: Very funny.\n");
	}
	else if (obj == guarded) {
	    notify(cap_name + " says: I'm already doing that.\n");
	}
	else {
	    notify(cap_name + " says: I am now guarding " + arg + "!\n");
	    set_guarded(obj);
	}
	return;
    }		
    else if (cmd == "wait" || cmd == "sleep" || cmd == "rest") {

	if (arg) {
	    notify(cap_name + " says: What do you mean, " +
		   cmd + " " + arg + "?\n");
	    return;
	}

	if (hunted) {
	    notify(cap_name + " says: " + get_honorary() + "! I won't rest until " +
		   hunted->query_name() + " is dead!\n");
	    return;
	}
	if (hunter) {
	    notify(cap_name + " says: " + get_honorary() + "! I won't rest until " +
		   hunter->query_name() + " is dead!\n");
	    return;
	}

	notify(cap_name + " says: Ok, I'll take a nap then, " +
	       get_honorary() + "!\n");
	sleeping = 1;
	return;
    }
    else if (cmd == "wield") {
	if (!arg) {
	    notify(cap_name + " says: Wield what?\n");
	    return;
	}

	obj = present(arg, this_object());
	if (!obj) {
	    notify(cap_name + " says: But I have no " + arg + ", " + get_honorary() + "!\n");
	}
	else
	    try_wield(obj);
	return;
    }
    else if (cmd == "drop") {
	if (!arg) {
	    notify(cap_name + " says: Drop what?\n");
	    return;
	}
	else if (arg == "money" || arg == "coins") {
	    notify(cap_name + " says: Sorry " + get_honorary() +
		   ", but that's my money, not yours.\n");
	    return;
	}
	obj = present(arg, this_object());
	if (!obj) {
	    notify(cap_name + " says: But I have no " + arg + ", " +
		   get_honorary() + "!\n");
	}
	else if (obj->drop())
	    notify(cap_name + " says: I cannot drop that, " + get_honorary() + "!\n");
	else {
	    add_weight(-obj->query_weight());
	    move_object(obj, environment(this_object()));
	    notify(cap_name + " drops the " + arg + ".\n");
	}
	return;
    }
    else if (cmd == "report") {
	if (arg)
	    notify(cap_name + " says: What do you mean, report " + arg + "?\n");
	else
	    status_report();
	return;
    }
    else if (cmd == "version") {
	if (arg)
	    notify(cap_name + " says: What do you mean, version " + arg + "?\n");
	else
	    notify(cap_name + " says: I am a bodyguard version " + VERSION + ".\n");
	return;
    }
    else if (cmd == "wimpy") {
	if (arg)
	    notify(cap_name + " says: What do you mean, wimpy " + arg + "?\n");
	else {
	    notify(cap_name + " says: What??! I am NOT wimpy! I am brave!\n");
	    notify(cap_name + " growls.\n");
	}
	return;
    }
    else if (cmd == "say") {
	if (!arg)
	    notify(cap_name + " says: Say what, " + get_honorary() + "?\n");
	else
	    notify(cap_name + " says: " + arg + "\n");
	return;
    }
    else if (cmd == "score" || cmd == "info" || cmd == "help") {
	notify(cap_name + " says: Maybe you mean \"report\", " + get_honorary() + "?\n");
    }
    else if (   cmd == "get" || cmd == "take" || cmd == "give"
	     || cmd == "tell" || cmd == "shout") {
	notify(cap_name + " just stands there, looking stupid.\n");
	return;
    }
    else {
	notify(cap_name + " says: Yes " + get_honorary() +
	       "! I will immediately " + cmdline + "!\n");
	init_command(cmdline);
	return;
    }

} /* handle_command */


/* try_wield
 *	The bodyguard should not be too powerful, so it is limited
 *	to weapons of a weapon_class of 15.
 */

try_wield(wpn) {
    int wpn_weight;
    string wpn_name;

    wpn_name = wpn->query_name();
    notify(cap_name + " tries to wield " + wpn_name + ".\n");

    if (wpn->weapon_class() > 15) {
	init_command("gasp");
	notify(cap_name + " says: Wow! What a weapon! It's too powerful for me, "
	       + get_honorary() + "!\n");
	wpn_weight = wpn->query_weight();
	add_weight(-wpn_weight);
	if (!guarded->add_weight(wpn_weight)) {
	    move_object(wpn, environment(this_object()));
	    notify(cap_name + " drops the " + wpn_name + ".\n");
	}
	else {
	    notify(cap_name + " gives the " + wpn_name + " to " + guarded_name + ".\n");
	    move_object(wpn, guarded);
	}
    }
    else {
	init_command("wield " + wpn_name);
    }
} /* try_wield */

status_report() {
      notify(cap_name + " says: Hi! I am " + cap_name + ", a level " +
	     query_level() + " bodyguard.\n" +
	     "    I am guarding " + guarded_cap_name + " against all dangers.\n" +
	     "    I currently have " + query_hp() + " hit points " +
	     "out of a max of " + (42 + query_level() * 8) + ",\n");
      notify("    I have " + query_money() + " gold coins, and I am " +
	     (age * 2) + " seconds old,\n");
      if (smart)
	  notify("    I feel smart.\n");
      if (lost)
	  notify("    I have lost " + guarded_cap_name + ".\n");
      if (sleeping)
	  notify("    I am asleep (and talking in my sleep now).\n");
} /* status_report */

notify(x) {
    write(x); say(x);
}
