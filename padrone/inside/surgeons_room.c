/* On Genesis, the surgeon cannot change your appearance */

#include "std.h"
#include "../config.h"

object surgeon, client;

/* For the NEW, IMPROVED monster class: */
string chat_str, a_chat_str, function, type, match;

#undef EXTRA_RESET
#define EXTRA_RESET  extra_reset(arg);

#undef EXTRA_INIT
#define EXTRA_INIT  extra_init();

extra_init() {
    add_action("do_exit", "exit");
    add_action("do_exit", "out");
} /* extra_init */

do_exit() {
    this_player()->move_player("out#players/padrone/inside/courtyard");
    return 1;
}

extra_reset(arg) {
    object weapon, money;

    if (!surgeon) {
	surgeon = clone_object("obj/monster");	/* NEW, IMPROVED monster class! */
	surgeon->set_name("surgeon");
	surgeon->set_male();
	surgeon->set_level(16);
	surgeon->set_hp(400);
	surgeon->set_al(200);
	surgeon->set_short("A surgeon");
	surgeon->set_long("The surgeon is dressed in a white coat soiled with blood.\n" +
			  "He has gloves made of rubber and a face-mask.\n" +
			  "Is he competent? Well, who knows...\n" +
			  "But maybe you should ask him what he can do?\n");
	surgeon->set_aggressive(0);
	surgeon->set_spell_mess1("The surgeon performs some surgery.");
	surgeon->set_spell_mess2("Argggh! The surgeon removes one of your internal organs!");
	surgeon->set_chance(20);
	surgeon->set_spell_dam(40);

        move_object(surgeon, this_object());

	/* The NEW, IMPROVED monster calls: */
	if (!chat_str)
	    setup_arrays();
	surgeon->load_chat(2, chat_str);
	surgeon->set_match(this_object(), function, type, match);

	weapon = clone_object("obj/weapon");
        weapon->set_name("knife");
        weapon->set_alias("big knife");
        weapon->set_alt_name("big swordlike razor-sharp knife");
        weapon->set_class(14);
        weapon->set_value(600);
        weapon->set_weight(2);
        weapon->set_short("A big, swordlike, razor-sharp knife");
        move_object(weapon, surgeon);
	surgeon->init_command("wield knife");

	weapon = clone_object("obj/weapon");
        weapon->set_name("long knife");
        weapon->set_class(8);
        weapon->set_value(20);
        weapon->set_weight(1);
        weapon->set_alt_name("knife");
        weapon->set_short("A long knife");
        move_object(weapon, surgeon);

	weapon = clone_object("obj/weapon");
        weapon->set_name("bone-saw");
        weapon->set_alt_name("saw");
        weapon->set_class(8);
        weapon->set_value(100);
        weapon->set_weight(2);
        weapon->set_short("A bone-saw");
        weapon->set_long("This is a saw of a type used to cut bones.\n");
        move_object(weapon, surgeon);

	weapon = clone_object("obj/weapon");
        weapon->set_name("scalpel");
        weapon->set_class(6);
        weapon->set_value(80);
        weapon->set_weight(1);
        weapon->set_short("A scalpel");
        weapon->set_long("A surgeon's scalpel.\n");
        move_object(weapon, surgeon);

	surgeon->set_wc(30);
	surgeon->set_ac(5);

	money = clone_object("obj/money");
        money->set_money(10 + random(40));
        move_object(money, surgeon);

    }
}

#ifdef GENESIS
ONE_EXIT("players/padrone/inside/courtyard", "northeast",
	 "The surgeon's operating room",
	 "You are in the surgeon's operating room.\n" +
	 "If he is here, he can help you to change your sex.\n", 1)
#else
ONE_EXIT("players/padrone/inside/courtyard", "northeast",
	 "The surgeon's operating room",
	 "You are in the surgeon's operating room.\n" +
	 "If he is here, he can help you to change your description or your sex.\n", 1)
#endif

handle_say(str) {
    string who, phrase, a, b;
    object face;

    if (   (sscanf(str, "%s says: %s\n", who, phrase) != 2)
	&& (sscanf(str, "%s says \"%s\"\n", who, phrase) != 2)	/* Morgar's say with quotes! */
	&& (sscanf(str, "%s tells you: %s\n", who, phrase) != 2)) {
	say("The surgeon looks brain damaged.\n");
	return;
    }
    if ((who == "The surgeon") || (who == "Surgeon"))
	return;

    /* phrase = lower_case(phrase); -- NOPE! */
    client = present(lower_case(who), environment(surgeon));
    if (!client) {
	say("The surgeon looks confused.\n");
	return;
    }

#ifndef GENESIS
    if (   sscanf(phrase, "change appearance to %s", a) == 1
	|| sscanf(phrase, "Change appearance to %s", a) == 1) {

	while (sscanf(a, "%s.", a) == 1 || sscanf(a, "%s!", a) == 1)
	    { }
	if (a == "") {
	    say("The surgeon says: Ha ha. Go away.\n");
	    return;
	}

        say("The surgeon operates...\n");
	if (!random(10)) {
	    say("Arrgh!! He fumbled!\n");
	    client->reduce_hit_point(10);
	}
	else {
	    face = present("appearance", client);
	    if (face)
		destruct(face);
	    face = clone_object("players/padrone/obj/appearance");
	    face->set_description(a);
	    move_object(face, client);
	    say("The surgeon is finished.\n");
	}
    }
    else if (   (sscanf(phrase, "%sappearance%s", a, b) == 2)
	     || (sscanf(phrase, "%sdescription%s", a, b) == 2)) {
        say("The surgeon says: I can change your appearance.\n" +
	    " - Just say 'change appearance to ...', and I'll do it.\n");
    }
    else
#endif

    if (   sscanf(phrase, "change sex to %s", a) == 1
	|| sscanf(phrase, "Change sex to %s", a) == 1) {
	int players_level;
	a = lower_case(a);
	say("The surgeon operates...\n");
	if (!random(10)) {
	    say("Arrgh!! He fumbled!\n");
	    client->reduce_hit_point(10);
	    return;
	}
	else if (a == "m" || a == "male" || a == "man") {
	    client->set_male();
	    say(client->query_name() + " is now a man!\n");
	}
	else if (a == "f" || a == "female" || a == "w" || a == "woman") {
	    client->set_female();
	    say(client->query_name() + " is now a woman!\n");
	}
	else {
	    client->set_neuter();
	    say(client->query_name() + " is now something very strange!\n");
	}
	players_level = client->query_level();
	if (!client->query_npc() && players_level < 20)
	    client->set_title(call_other("room/adv_guild", "get_new_title", players_level - 1));
    }
    else if (   (phrase == "change sex")
	     || (phrase == "Change sex")
	     || (sscanf(phrase, "change sex %s", a) == 1)
	     || (sscanf(phrase, "Change sex %s", a) == 1)) {
        say("The surgeon says: What? Say 'change sex to ...', and I'll do it.\n");
    }
    else if (phrase == "heal" || phrase == "heal me" || phrase == "Heal" || phrase == "Heal me") {
       	say("The surgeon tries to heal you...\n");
	if (random(20)) {
	    say("Arrgh!! He fumbled!\n");
	    client->reduce_hit_point(10);
	}
	else {
	    say("The surgeon performs a successful healing operation!\n");
	    say("He really looks proud. Maybe he never succeeded in this before?\n");
	    client->heal_self(100);
	}
    }
    else if (   phrase == "remove frog curse"
	     || phrase == "Remove frog curse") {
       	say("The surgeon operates...\n");
	if (!random(10)) {
	    say("Arrgh!! He fumbled!\n");
	    client->reduce_hit_point(10);
	}
	else {
	    say("The surgeon cuts away the frog legs. You feel much better!\n");
	    client->frog_curse(0); 
	}
    }
    else if (   (sscanf(phrase, "%sfrog%s", a, b) == 2)
	     || (sscanf(phrase, "%scurse%s", a, b) == 2)) {
        say("The surgeon says: I can remove a frog curse.\n");
	say(" - Just say 'remove frog curse', and I'll do it.\n");
    }
    else if (sscanf(phrase, "%sheal%s", a, b) == 2) {
        say("The surgeon says: Heal you? Well, I could try...\n");
    }
    else if (   sscanf(phrase, "%shelp%s", a, b) == 2
	|| sscanf(phrase, "%sHelp%s", a, b) == 2
	|| sscanf(phrase, "%scost%s", a, b) == 2
        || sscanf(phrase, "%sprice%s", a, b) == 2
	|| sscanf(phrase, "%sprice%s", a, b) == 2
	|| sscanf(phrase, "%slist%s", a, b) == 2
	|| sscanf(phrase, "%stell%s", a, b) == 2
	|| sscanf(phrase, "%sTell%s", a, b) == 2
        || sscanf(phrase, "%sservice%s", a, b) == 2
	|| sscanf(phrase, "%swhat%s", a, b) == 2
	|| sscanf(phrase, "%sWhat%s", a, b) == 2
	|| sscanf(phrase, "%syes%s", a, b) == 2
	|| sscanf(phrase, "%sYes%s", a, b) == 2
	|| sscanf(phrase, "%splease%s", a, b) == 2
	|| sscanf(phrase, "%sPlease%s", a, b) == 2) {
	say("The surgeon says: I will gladly operate you for free!\n");
#ifdef GENESIS
	say(" - I am good at sex change operations (say \"change sex to ...\")!\n");
#else
	say(" - I can change your appearance (just say \"change appearance to ...\")\n" +
	    " - or your sex (say \"change sex to ...\")!\n");
#endif
	say("The surgeon grins evilly.\n");
    }
    else {
        /* say("The surgeon looks puzzled.\n"); */
    }
} /* handle_say */


handle_arrival(str)
{
    string who, rest, n;

    if (sscanf(str, "%s arrives%s", who, rest) != 2) {
	say("The surgeon looks brain damaged.\n");
	return;
    }
    if ((who == "The surgeon") || (who == "Surgeon"))
	return;

    client = present(lower_case(who), environment(surgeon));
    if (!client) {
	say("The surgeon looks confused.\n");
	return;
    }

    n = client->query_name();
    say("The surgeon says: Hi there, " + n + "! Want some surgery?\n");
} /* handle_arrival */

/* For the NEW, IMPROVED monster class: */
setup_arrays() {

    chat_str = ({
	"The surgeon says: How can I help you?\n",
	"The surgeon sharpens his knives.\n",
	"The surgeon tests the edge of his scalpel.\n"
    });

    function = allocate(3);
    type = allocate(3);
    match = allocate(3);

    function[0] = "handle_say";
    type[0] = "says";
    match[0] = "";
    type[1] = "tells you:";
    match[1] = " ";
    function[2] = "handle_arrival";
    type[2] = "arrives";
    match[2] = "";
} /* setup_arrays */
