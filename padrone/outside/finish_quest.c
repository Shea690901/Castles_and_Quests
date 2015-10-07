/* finish_quest.c */

#include "std.h"
#include "../config.h"
#include "../walker/walker.h"

object golem;

/* For the NEW, IMPROVED monster class: */
string chat_str, a_chat_str, function, type, match;

#undef EXTRA_RESET
#define EXTRA_RESET  extra_reset(arg);

extra_reset(arg) {
    if (!golem)
	make_golem();
}

#undef EXTRA_LONG
#define EXTRA_LONG \
	if (id(str)) { \
	    write("Well, actually this is only a stand-in for Padrone.\n"); \
            golem->long(); \
	    return; \
	}

id(str) {
    if (!golem)
	return 0;
    else
	return str == "padrone" || str == "Padrone";
}

ONE_EXIT("players/padrone/outside/crosspath2", "west",
	 "Open place",
	 "In the middle of the forest a rather large open place has been\n" +
	 "cleared. There are some strange depressions in the ground, almost\n" +
	 "like big -- and I do mean BIG -- footprints.\n" +
	 "You notice that this would be a nice place for a castle.\n", 1)

/* -------- The code for Golem-Padrone is below this line --------- */

make_golem() {
    object temp;

    golem = clone_object("obj/monster");	/* NEW, IMPROVED monster class! */
    golem->set_name("golem-padrone");
    golem->set_alias("golem");
    golem->set_level(21);
    golem->set_ep(120000);
    golem->set_hp(1000);
    golem->set_ac(5);
    golem->set_ac(5);
    golem->set_al(0);
    golem->set_short("Padrone the Wizard of Law and Balance (grey lord)");
    golem->set_long("The famous wizard doesn't have time to sit here and wait all day.\n" +
		    "Therefore he made this golem, named it Golem-padrone, and put\n" +
		    "it here. It is a silicon golem, and it is equipped with a\n" +
		    "limited amount of intelligence.\n");
    
    golem->set_aggressive(0);

    /* The NEW, IMPROVED monster calls: */
    if (!chat_str)
	setup_arrays();
    golem->load_chat(10, chat_str);
    golem->load_a_chat(20, a_chat_str);
    golem->set_match(this_object(), function, type, match);

    move_object(call_other("players/padrone/outside/front_yard", "make_ticket"), golem);
    move_object(golem, this_object());

    temp = clone_object("players/padrone/obj/wizardshat");
    move_object(temp, golem);
    golem->init_command("wear hat");
    golem->init_command("say lux");

    temp = clone_object("obj/weapon");
    temp->set_name("debugging tool");
    temp->set_alt_name("tool");
    temp->set_alias("debugger");
    temp->set_class(10);
    temp->set_value(100);
    temp->set_weight(3);
    temp->set_short("A debugging tool");
    temp->set_long("This is a debugging tool.\n" +
		   "One of the wizards probably made it to take care of all\n" +
		   "the bugs that crawl into his correct and beautiful programs\n" +
		   "as soon as he's looking the other way.\n" +
		   "It looks like a big iron hammer with an extra wide head.\n");
    temp->set_hit_func(this_object());
    move_object(temp, golem);

    golem->set_ac(10);		/* After all wear commands! */
} /* make_robot_padrone */


handle_say(str) {
    string who, phrase, a, b;
    int oa, na, add;
    object client;

    /* log_file("padrone", "Golem: handle_say: " + str); */

    if (   (sscanf(str, "%s says: %s\n", who, phrase) != 2)
	&& (sscanf(str, "%s says \"%s\"\n", who, phrase) != 2)	/* Morgar's say with quotes! */
	&& (sscanf(str, "%s tells you: %s\n", who, phrase) != 2)) {
	notify("Padrone looks brain damaged.\n");
	return;
    }
    if (who == "Padrone" || who == "Golem-padrone")
	return;
    phrase = "." + lower_case(phrase) + ".";
    client = present(lower_case(who));
    if (!client) {
	notify("Padrone looks confused. Who said that?\n");
	return;
    }

    if (sscanf(phrase, "%shelp%s", a, b) == 2) {
	notify("Padrone says: What kind of help do you need?\n");
    }
    else if (   (sscanf(str, "%scastle%s", a, b) == 2)
	     || (sscanf(str, "%swalk%s", a, b) == 2)) {
	notify("Padrone says: Do you know where my walking castle is??? Bring it here!\n");
    }
    else if (sscanf(str, "%sheal%s", a, b) == 2) {
	notify("Padrone says: Sorry, I cannot heal you. Talk to my apprentice!\n");
    }
    else if (sscanf(str, "%sbug%s", a, b) == 2) {
	notify("Padrone says: What do you mean, \"bug\"? There are no bugs in my code!\n");
    }
    else if (   (sscanf(phrase, "%schange%s", a, b) == 2)
	     || (sscanf(phrase, "%sset%s", a, b) == 2)
	     || (sscanf(phrase, "%salignment%s", a, b) == 2)
	     || (sscanf(phrase, "%stitle%s", a, b) == 2)
	     || (sscanf(phrase, "%sdescription%s", a, b) == 2)
	     || (sscanf(phrase, "%sfrog%s", a, b) == 2)) {

	notify("Padrone says: Talk to my apprentice about that.\n");
    }
    else if (sscanf(phrase, "%srobot%s", a, b) == 2) {
	notify("Padrone says: Yes, I am a robot. So what?\n");
    }
    else if (sscanf(phrase, "%swho%s", a, b) == 2) {
	notify("Padrone says: I don't know.\n");
    }
    else if (sscanf(phrase, "%swhere%s", a, b) == 2) {
	notify("Padrone says: Last time I saw the castle, it was in the northern plains.\n");
    }
    else if (sscanf(phrase, "%syes%s", a, b) == 2) {
	notify("Padrone says: I am glad to hear that.\n");
    }
    else if (sscanf(phrase, "%sno%s", a, b) == 2) {
	notify("Padrone says: Oh.\n");
    }
    else {
	if (random(2))
	    notify("Padrone says: Just help me find my castle, and then bring it here.\n");
	else
	    notify("Padrone says: I would really appreciate some help with this.\n");
    }
} /* handle_say */


handle_arrival(str)
{
    string who, rest, n;
    object client;

    /* log_file("padrone", "Golem: handle_arrival: " + str); */

    if (sscanf(str, "%s arrives%s", who, rest) != 2) {
	return;
    }
    if ((who == "Padrone") || (who == "padrone"))
	return;
    client = present(lower_case(who), this_object());
    if (!client)
	return;
    notify("Padrone bows gracefully.\n");
    check_castle();
} /* handle_arrival */


handle_kick(str)
{
    /* log_file("padrone", "Golem: handle_kick: " + str); */
    notify("Padrone says: Don't be angry! After all, I'm only a robot.\n");
}


handle_smile(str)
{
    notify("Padrone smiles happily.\n");
}


check_castle() {
    object client, idwand, an_obj;
    string client_name, client_lname;

    if (!present("walking castle", this_object()))
	return 0;
    client = call_other(CASTLE, "who_drove_it_here");
    if (client) {
	client_name = client->query_name();
	client_lname = lower_case(client_name);
	if (!present(client, this_object())) {
	    notify("Padrone says: Excuse me, but I would like to talk to " +
		   client->query_name() + ".\n");
	    return 0;
	}
    }
    else {
	/* Just take any player who happens to be here! */
	an_obj = first_inventory(this_object());
	while (an_obj && !client) {
	    if (living(an_obj) && !an_obj->query_npc())
		client = an_obj;
	    an_obj = next_inventory(an_obj);
	}
	client_name = client->query_name();
	client_lname = lower_case(client_name);
    }
    if (!client)
	return 0;

    if (client->query_quests("padrone")) {
	notify("Padrone says: Hi there, " + client_name+ ". Haven't I seen you before?\n");
	notify("Padrone says: But it doesn't matter. I'll give you a reward this time too.\n");
	log_file("padrone", ctime(time()) + ": " + client_name + " solved the quest (again).\n");
    }
    else {
	notify("Padrone says: You found my castle! I am so happy!\n");
	golem->init_command("kiss " + client_lname);
#ifndef GENESIS
	shout("Padrone shouts: " + client_name + " just solved my quest!\n");
#endif
	client->set_quest("padrone");
	log_file("padrone", ctime(time()) + ": " + client_name +
		 " (level " + client->query_level() +
		 ") solved the quest.\n");
    }

    notify("Padrone says: Here! Take this small token of my appreciation!\n");
    notify("Padrone fetches something from another dimension.\n");

    idwand = clone_object("players/padrone/obj/idwand");
    if (client->add_weight(1)) {
	notify("Padrone gives wand to " + client_name + ".\n");
	move_object(idwand, client);
    }
    else {
	notify("Padrone drops the wand.\n");
	move_object(idwand, this_object());
    }
    notify("Padrone says: I have also arranged for a bodyguard for you.\n");
    notify("Padrone says: Just go to Antonio's Personal Protection Service.\n");

    notify("Padrone quietly opens a small door in reality. Then, he is gone.\n");
    notify("The castle disappears in a puff of smoke.\n");
    call_other(CASTLE, "callable_castle_reset");	/* Also resets the bridge */
    move_object(golem, "players/padrone/store");
    call_out("give_bodyguard", 4, client);

    destruct(golem);
    return 1;
} /* check_castle */

give_bodyguard(client) {
    object bodyguard;

    if (!client)
	return;
    bodyguard = call_other("players/padrone/inside/antonios", "make_bodyguard", client);
    if (!bodyguard) {
	tell_object(client, "Sorry, all bodyguards are busy.\n");
	return;
    }
    /* This is just to start the heartbeat in the bodyguard: */
    move_object(bodyguard, environment(client));
    move_object(client, environment(client));

    move_object(bodyguard, "players/padrone/inside/antonios");
} /* give_bodyguard */

notify(str) {
    say(str);
    write(str);
}


/* For the NEW, IMPROVED monster class: */
setup_arrays() {

    function = allocate(5);
    type = allocate(5);
    match = allocate(5);

    function[0] = "handle_say";
    type[0] = "says";
    match[0] = "";
    type[1] = "tells you:";
    match[1] = " ";
    function[2] = "handle_arrival";
    type[2] = "arrives";
    match[2] = "";
    function[3] = "handle_kick";
    type[3] = "kicks";
    match[3] = " you.   OUCH!!";
    function[4] = "handle_smile";
    type[4] = "smiles";
    match[4] = " happily.";

    chat_str = ({
	"Padrone sighs deeply.\n",
	"Padrone sulks in the corner.\n",
	"Padrone bursts into tears.\n",
	"Padrone bursts into tears.\n",
	"Padrone growls.\n",
	"Padrone creates a small pirate and stomps it into the ground.\n",
	"Padrone says: It took almost two weeks to build that castle!\n",
	"Padrone says: I really feel stupid. Letting some monsters steal my castle!\n",
	"Padrone says: Have you seen my walking castle?\n",
	"Padrone says: Can you help me?\n",
	"Padrone says: Could you please help me find my lost castle?\n",
    });
    
    a_chat_str = ({
	"Golem-padrone falls down laughing.\n",
	"Golem-padrone smiles happily.\n",
	"Golem-padrone pats you on the head.\n",
	"Golem-padrone ruffles your hair playfully.\n",
	"Golem-padrone fetches something from another dimension.\n",
	"Golem-padrone says: You DO know I'm a wizard, don't you?\n",
	"Golem-padrone says: I COULD summon 500 balrogs, you know...\n",
    });
} /* setup_arrays */

/* This is the hit function for the debugging tool: */
weapon_hit(victim) {
    
    if (   victim
	&& (victim->query_name() == "Bug" || lower_case(victim->query_race()) == "bug")) {
	notify("Splat! The bug suddenly looks much flatter.\n");
	return 10;
    }
    else
	return 0;
} /* weapon_hit for the debugging tool */
