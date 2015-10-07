#include "std.h"

object eddie, client;

/* For the NEW, IMPROVED monster class: */
string chat_str, a_chat_str, function, type, match, function2, type2, match2;

#undef EXTRA_RESET
#define EXTRA_RESET  extra_reset(arg);

extra_reset(arg) {
    object note;

    if (!eddie || !living(eddie)) {
	eddie = clone_object("obj/monster");	/* NEW, IMPROVED monster class! */
	eddie->set_name("eddie");
	eddie->set_alias("eddie the mischievous prankster");
	eddie->set_level(3);
	eddie->set_ac(6);
	eddie->set_al(20);
	eddie->set_short("Eddie the mischievous prankster");
	eddie->set_long("Eddie is a small, sharp-nosed man of undecidable origin. He lives\n" +
			"in the small room behind the Wizard's consultation room, and he spends\n" +
			"his days snooping on the Wizard or his Apprentice when they perform\n" +
			"strange and beautiful magic. He has actually managed to learn one\n" +
			"spell... Maybe he will show you, if you talk nicely to him?\n");
	eddie->set_aggressive(0);
	eddie->set_spell_mess1("Eddie casts the spell SEGMENTATION VIOLATION.");
	eddie->set_spell_mess2("Eddie tries to hit you with the spell SEGMENTATION VIOLATION.\n" +
			       "He missed almost totally, but you are still hurt by this deadly spell.");
	eddie->set_chance(10);
	eddie->set_spell_dam(20);

	move_object(call_other("players/padrone/outside/front_yard", "make_ticket"), eddie);
	move_object(eddie, this_object());

	/* The NEW, IMPROVED monster calls: */
	if (!chat_str)
	    setup_arrays();
	eddie->load_chat(10, chat_str);
	eddie->load_a_chat(40, a_chat_str);
	eddie->set_match(this_object(), function, type, match);
    }
}

ONE_EXIT("players/padrone/inside/cons", "west",
	 "A small room behind the consultation room",
	 "This is a very small room behind Padrone's consultation room.\n", 1)

handle_say(str) {
    string who, phrase, a, b, a_name, out;
    int oa, na, add;
    object obj;

    if (   (sscanf(str, "%s says: %s\n", who, phrase) != 2)
	&& (sscanf(str, "%s says \"%s\"\n", who, phrase) != 2)	/* Morgar's say with quotes! */
	&& (sscanf(str, "%s tells you: %s\n", who, phrase) != 2)) {
	say("Eddie looks brain damaged.\n");
	return;
    }
    if (who == "Eddie")
	return;
    phrase = lower_case(phrase);
    client = present(lower_case(who), environment(eddie));
    if (!client) {
	say("Eddie looks confused.\n");
	return;
    }

    if (sscanf(phrase, "poke %s", a_name) == 1) {
	obj = find_living(a_name);

	if (!obj) {
	    say("Eddie says: Bah! There is noone called " + a_name + "!\n");
	    return 0;
	}
	if (obj == eddie) {
	    say("Eddie falls down laughing.\n");
	    return 0;
	}
	if (client->query_money() < 200) {
	    say("Eddie says: I want 200 coins to do that.\n");
	    return 0;
	}
	tell_object(client, "You pay 200 gold coins for the magic assistance.\n");
	client->add_money(-200);

       	say("Eddie says: Ok, here we go...\n");
	say("Eddie disappears in a puff of smoke.\n");
	move_object(eddie, environment(obj));
	say("Eddie arrives in a puff of smoke.\n");
	tell_object(obj, "Eddie pokes you in the eye. Ouch! That hurt!\n");
	say("Eddie pokes " + obj->query_name() + " in the eye!\n", obj);
	say("Eddie says: With greetings from " + client->query_name() + "!\n");
	say("Eddie disappears in a puff of smoke.\n");
	move_object(eddie, this_object());
	say("Eddie arrives in a puff of smoke.\n");
	say("Eddie says: Done!\n");
	say("Eddie giggles inanely.\n");
    }
    else if (phrase == "poke") {
        say("Eddie says: Yes, yes, but poke who?\n");
    }
    else if (   (sscanf(phrase, "%spoke%s", a, b) == 2)
	     || (sscanf(phrase, "%sjoke%s", a, b) == 2)
	     || (sscanf(phrase, "%sprank%s", a, b) == 2)) {
        say("Eddie says: For 200 I'll help you with a nice joke... Just tell me to poke someone!\n");
    }
    else if (   (sscanf(phrase, "%smoney%s", a, b) == 2)
	     || (sscanf(phrase, "%scost%s", a, b) == 2)
	     || (sscanf(phrase, "%sprice%s", a, b) == 2)) {
        say("Eddie says: Oh, for 200 I'll help you with a nice joke...\n");
    }
    else {
        say("Eddie smiles happily.\n");
    }
} /* handle_say */


handle_arrival(str)
{
    string who, rest, n;

    if (sscanf(str, "%s arrives%s", who, rest) != 2) {
	say("Eddie looks brain damaged.\n");
	return;
    }
    if (who == "Eddie")
	return;
    client = present(lower_case(who), environment(eddie));
    if (!client) {
	say("Eddie looks confused.\n");
	return;
    }

    n = client->query_name();
    say("Eddie says: Hi, " + n + "! Wanna pay 200 for a nice little joke?\n");
    say(" - Just tell me to poke someone!\n");
} /* handle_arrival */


handle_gives(str) {
    string who, what;
    int nr_coins;

    if (  sscanf(str, "%s gives %s to Eddie.\n", who, what) == 2) {
	say("Eddie says: Gee! Thanks! That's just what I always wanted!\n");
    }
    else if (sscanf(str, "%s gives you %d gold coins.\n", who, nr_coins) == 2) {
	if (nr_coins == 200)
	    say("Eddie says: Thank you! But I dont know who to do the joke to.\n");
	else
	    say("Eddie says: Thank you! I appreciate that.\n");
    }
    else
	say("Eddie looks brain damaged.\n");
} /* handle_gives */


/* For the NEW, IMPROVED monster class: */
setup_arrays() {

    /* Peaceful chatting: */
    chat_str = ({
	"Eddie grins evilly.\n",
	"Eddie pokes you in the ribs.\n",
	"Eddie falls down laughing.\n",
	"Eddie smiles happily.\n"
    });

    /* Combat chatting: */
    a_chat_str = ({
	"Eddie casts a fireball. It hits himself, and he is badly burnt.\n",
	"Eddie casts a shock. It hits the ceiling.\n",
	"Eddie casts a magic missile. It makes a small round hole in the wall.\n",
	"Eddie tries to summon a flash from the sky. Luckily, nothing happens.\n",
	"Eddie tries to cast the spell GLOBAL NUCLEAR EARTHQUAKE. Nothing happens.\n",
	"Eddie tries to cast the spell FLOATING POINT EXCEPTION. Nothing happens.\n",
	"Eddie tries to cast the spell KILL -9. Nothing happens.\n",
	"Eddie tries to summon a demon. Nothing happens.\n",
	"Eddie tries to summon a balrog. Nothing happens.\n",
	"Eddie screams for the security guards. Nothing happens.\n"
    });

    function = allocate(4);
    type = allocate(4);
    match = allocate(4);

    function[0] = "handle_say";
    type[0] = "says";
    match[0] = "";
    type[1] = "tells you:";
    match[1] = " ";
    function[2] = "handle_arrival";
    type[2] = "arrives";
    match[2] = "";
    function[3] = "handle_gives";
    type[3] = "gives";
    match[3] = "";
} /* setup_arrays */
