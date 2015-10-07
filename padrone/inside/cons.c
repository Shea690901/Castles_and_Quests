/*  Padrone's consultation room. Latest change: July 24, 1992.
 *	The spell "Change Alignment Description" is not available
 *      on GENESIS. Lars didn't like it. How sad.
 */

#include "../config.h"
#include "std.h"
#include "../../../obj/door.h"

object apprentice, invisible_companion, client,
       teleportee, latest_teleportee, bird;
status busy_teleporting;

/* For the NEW, IMPROVED monster class: */
string chat_str, a_chat_str, function, type, match,
       function2, type2, match2, chat_str3, function3, type3, match3;

#undef EXTRA_RESET
#define EXTRA_RESET  extra_reset(arg);

extra_reset(arg) {
    object hat, knife, key, money, stone;

    if (!apprentice || !living(apprentice)) {
	apprentice = clone_object("obj/monster");	/* NEW, IMPROVED monster class! */
	move_object(clone_object("players/padrone/obj/immunity"), apprentice);
	apprentice->set_name("apprentice");
	apprentice->set_level(19);
	apprentice->set_male();
	apprentice->set_hp(400);
	apprentice->set_al(100);
	apprentice->set_short("The Wizard's apprentice");
	apprentice->set_long("This is the Wizard's apprentice.\n" +
			     "Although still a young man\n" +
			     "he has already mastered many of the secrets of magic.\n" +
			     "He is wearing a strange hat and looks somewhat dangerous.\n" +
			     "Since the Wizard is not in today, the apprentice is handling\n" +
			     "the consultations. Talk to him and state your problem!\n");
	apprentice->set_aggressive(0);
	apprentice->set_spell_mess1("The apprentice casts a fireball.");
	apprentice->set_spell_mess2("The apprentice casts a fireball at you.");
	apprentice->set_chance(20);
	apprentice->set_spell_dam(40);

	move_object(apprentice, this_object());
	move_object(call_other("players/padrone/outside/front_yard", "make_ticket"), apprentice);

	/* The NEW, IMPROVED monster calls: */
	if (!chat_str)
	    setup_arrays();
	apprentice->load_chat(2, chat_str);
	apprentice->set_match(this_object(), function, type, match);

	/* The invisible companion hack */
	apprentice->set_dead_ob(this_object());
	invisible_companion = clone_object("obj/monster"); /* NEW, IMPROVED monster class! */	
	invisible_companion->set_name("invisible companion of the apprentice");
	invisible_companion->set_alias("invisible companion");
	move_object(clone_object("players/padrone/obj/immunity"), invisible_companion);
	invisible_companion->setup_invis();
	invisible_companion->set_level(20);
	invisible_companion->set_male();
	invisible_companion->set_ac(22000000);
	invisible_companion->set_hp(22000000);
	invisible_companion->set_short(0);
	invisible_companion->set_long("He is invisible and lurks in a corner.\n");
	invisible_companion->set_aggressive(0);
	move_object(invisible_companion, this_object());

	/* The NEW, IMPROVED monster calls: */
	invisible_companion->set_match(this_object(), function2, type2, match2);

	hat = clone_object("players/padrone/obj/wizardshat");
        move_object(hat, apprentice);
	apprentice->init_command("wear hat");

	knife = clone_object("obj/weapon");
        knife->set_name("long knife");
        knife->set_class(8);
        knife->set_value(20);
        knife->set_weight(1);
        knife->set_alt_name("knife");
        knife->set_short("A long knife");
        move_object(knife, apprentice);
	apprentice->init_command("wield knife");

	MAKE_KEY(key, "crystal", "towerdoor")
        move_object(key, apprentice);

	money = clone_object("obj/money");
        money->set_money(10 + 10 * random(5));
        move_object(money, apprentice);

	stone = clone_object("players/padrone/obj/gravstone");
	stone->set_weight(-2);
	move_object(stone, apprentice);

    }
}

TWO_EXIT("players/padrone/inside/waitingroom", "west",
	 "players/padrone/inside/eddies_room", "east",
	 "Consultation room",
	 "You are in Padrone's consultation room.\n" +
	 "It is in this room that the mighty Wizard meets his clients.\n" +
	 "The waiting room is west, and a small door leads east into a\n" +
	 "wardrobe or something.\n", 1)

handle_say(str) {
    string who, phrase, a, b, a_name, out;
    int oa, na, add;
    object obj;

    if (   (sscanf(str, "%s says: %s\n", who, phrase) != 2)
	&& (sscanf(str, "%s says \"%s\"\n", who, phrase) != 2)	/* Morgar's say with quotes! */
	&& (sscanf(str, "%s tells you: %s\n", who, phrase) != 2)) {
	say("The apprentice looks brain damaged.\n");
	return;
    }
    if ((who == "The apprentice") || (who == "Apprentice"))
	return;

    if (!bird || !teleportee)
	busy_teleporting = 0;
    if (busy_teleporting) {
	say("The apprentice is concentrating on a spell and doesn't listen.\n");
	return;
    }

    /* phrase = lower_case(phrase); -- NOPE! */
    client = present(lower_case(who), environment(apprentice));
    if (!client) {
	say("The apprentice looks confused.\n");
	return;
    }

    if (   sscanf(phrase, "%shelp%s", a, b) == 2
	|| sscanf(phrase, "%sHelp%s", a, b) == 2) {
	say("The apprentice says: Well, " + who + ", I do have some powers.\n" +
	    " - But magic assistance is of course not free.\n");
    }
    else if (   (sscanf(phrase, "%scost%s", a, b) == 2)
	     || (sscanf(phrase, "%sprice%s", a, b) == 2)
	     || (sscanf(phrase, "%sprice%s", a, b) == 2)
	     || (sscanf(phrase, "%slist%s", a, b) == 2)
	     || (sscanf(phrase, "%stell%s", a, b) == 2)
	     || (sscanf(phrase, "%sTell%s", a, b) == 2)
	     || (sscanf(phrase, "%sservice%s", a, b) == 2)
	     || (sscanf(phrase, "%swhat%s", a, b) == 2)
	     || (sscanf(phrase, "%sWhat%s", a, b) == 2)) {
	say("The apprentice says: The prices are fixed:\n" +
	    "          Know Alignment:                 100 gold coins\n" +
	    "          Heal yourself:                 4000 gold coins\n" +
	    "          Heal someone else:             2000 gold coins\n");
	say("          Teleport a player here         1000 gold coins\n" +
	    "          Change Alignment:               100 gold coins per point\n");
#ifndef GENESIS
	say("          Change Alignment Description:    20 gold coins (temporary)\n");
#endif
	say("          Remove Frog Curse:              500 gold coins\n");
	say(" - Just tell me what you want, the apprentice smiles.\n");
    }
    else if (phrase == "know alignment" || phrase == "Know alignment") {
	if (!take_money(100))
	    return;
	say("The apprentice casts the spell KNOW ALIGNMENT.\n");
	tell_object(client, "The apprentice tells you: Your alignment is " +
		    client->query_alignment() + ".\n");
    }
    else if (   sscanf(phrase, "heal %s", a_name) == 1
	     || sscanf(phrase, "Heal %s", a_name) == 1) {
	if (a_name == "myself" || a_name == "me")
	    obj = client;
	else {
	    obj = present(lower_case(a_name), environment(apprentice));
	    if (!obj || !living(obj)) {
		say("The apprentice says: But there is no " + a_name + " here!\n");
		return;
	    }
	}
	if (obj == client)
	    { if (!take_money(4000)) return; }
	else
	    { if (!take_money(2000)) return; }

       	say("The apprentice casts the spell HEAL.\n");
	obj->heal_self(1000);
	tell_object(obj, "You are healed by the Wizard's Apprentice.\n");
	/* Snicker, snicker... */
	apprentice->heal_self(1000);
	tell_object(client, "The apprentice heals himself at the same time.\n");
    }
    else if (phrase == "heal" || phrase == "Heal") {
        say("The apprentice says: Heal who? Say 'heal ...', and I'll do it.\n");
    }
    else if (   sscanf(phrase, "teleport %s", a_name) == 1
	     || sscanf(phrase, "teleport %s", a_name) == 1) {

	object teleportee_env;

	teleportee = find_living(lower_case(a_name));
	if (!teleportee) {
	    say("The apprentice says: Sorry, I cannot find " + a_name + ".\n");
	    return;
	}
	else if (teleportee->query_npc()) {
	    say("The apprentice says: Sorry, but that is just a simple monster.\n" +
		" - I only teleport players.\n");
	    return;
	}
	else if (present(teleportee, environment(apprentice))) {
	    say("The apprentice says: Don't be stupid.\n");
	    return;
	}
       	say("The apprentice says: Ok, this may take some time...\n");
	if (!take_money(1000))
	    return;
       	say("The apprentice casts the spell TELEPORT.\n");
	busy_teleporting = 1;

	/*  We create a small bird that teleports to the presumptive teleportee
	 *  and asks him if he wants to be teleported.
	 *  Otherwise, someone might use this spell for evil purposes...
	 */
	bird = clone_object("obj/monster");	/* NEW, IMPROVED monster class! */
	bird->set_name("bird");
	bird->set_level(1);
	bird->set_hp(10);
	bird->set_al(100);
	bird->set_ac(10);
	bird->set_short("A small bird that shimmers strangely");
	bird->set_long("This small bird doesn't seem quite natural.\n" +
		       "There must be magic involved here...\n");
	bird->set_aggressive(0);

	/* The NEW, IMPROVED monster calls: */
	if (!chat_str)
	    setup_arrays();
	bird->load_chat(25, chat_str3);
	bird->set_match(this_object(), function3, type3, match3);

	/* This is done only to start the heart beat in the bird: */
	{
	    move_object(bird, environment(apprentice));
	    move_object(apprentice, environment(apprentice));
	}

	teleportee_env = environment(teleportee);
	move_object(bird, teleportee_env);

	tell_room(teleportee_env,
		  "Suddenly a small bird comes flying from no obvious direction.\n");
	tell_room(teleportee_env,
		  "It seems to whisper something to " +
		  teleportee->query_name() + ".\n");
	tell_object(teleportee,
		    "The bird whispers to you: Greetings from " +
		    client->query_name() + "!\n" +
		    " - Do you want to be teleported?\n");
    }
    else if (phrase == "teleport" || phrase == "Teleport") {
        say("The apprentice says: Yes, but who? Say 'teleport ...', and I'll do it.\n");
    }
    else if (   sscanf(phrase, "change alignment to %d", na) == 1
	     || sscanf(phrase, "Change alignment to %d", na) == 1) {

	if (na > 10000 || na < -10000) {
	    /* Thanks to Qqqq for finding this problem. Blush! */
	    say("The apprentice says: " + na + "? Go away!\n");
	    return;
	}

	oa = client->query_alignment();
	if (!take_money(100 * abs(oa - na)))
	    return;
	add = na - (oa * 9) / 10;
        say("The apprentice casts the spell CHANGE ALIGNMENT\n" +
	    "to change the alignment from " + oa + " to " + na + ".\n");
	client->add_alignment(add);
    }
    else if (   (phrase == "change alignment")
	     || (phrase == "Change alignment")
	     || (sscanf(phrase, "Change alignment %d", a) == 1)
	     || (sscanf(phrase, "change alignment %d", a) == 1)) {
        say("The apprentice says: What? Say 'change alignment to ...', and I'll do it.\n");
    }
    else if (   sscanf(phrase, "change alignment to %s", a) == 1
	     || sscanf(phrase, "Change alignment to %s", a) == 1) {
        say("The apprentice says: The alignment has to be a numeric value.\n");
    }

#ifndef GENESIS
    else if (   sscanf(phrase, "change alignment description to %s", a) == 1
	     || sscanf(phrase, "Change alignment description to %s", a) == 1) {
	if (!take_money(20))
	    return;
        say("The apprentice casts the spell CHANGE ALIGNMENT DESCRIPTION.\n");
	apprentice->set_level(100);
	client->set_alignment(a);
	apprentice->set_level(19);
    }
    else if (   (phrase == "change alignment description")
	     || (phrase == "Change alignment description")
	     || (sscanf(phrase, "change alignment description %s", a) == 1)
	     || (sscanf(phrase, "Change alignment description %s", a) == 1)) {
        say("The apprentice says: What? Say 'change alignment description to ...',\n" +
            " - and I'll do it.\n");
    }
#endif

    else if (   phrase == "remove frog curse"
	     || phrase == "Remove frog curse") {
	if (!take_money(500))
	    return;
        say("The apprentice casts the spell REMOVE FROG CURSE.\n");
	client->frog_curse(0);
    }
    else if (   (sscanf(phrase, "%sfrog%s", a, b) == 2)
	     || (sscanf(phrase, "%scurse%s", a, b) == 2)) {
        say("The apprentice says: I can remove a frog curse.\n");
	say(" - Just say 'remove frog curse', and I'll do it.\n");
    }
    else if (   (sscanf(phrase, "%stitle%s", a, b) == 2)
	     || (sscanf(phrase, "%sdescription%s", a, b) == 2)) {

#ifdef GENESIS
        say("The apprentice says: Sorry, I don't know how to change either\n" +
	    " - your title or your alignment description.\n");
#else
        say("The apprentice says: I can change your alignment\n" +
	    " - description for you (but not your title).\n");
	say(" - Just say 'change alignment description to ...',\n" +
            " - and I'll do it.\n");
#endif

    }
    else if (sscanf(phrase, "%salignment%s", a, b) == 2) {

#ifdef GENESIS
        say("The apprentice says: I have the power to change your alignment.\n");
	say(" - Just say 'change alignment to ...',\n" +
            " - and I'll do it.\n");
#else
        say("The apprentice says: I know two spells to handle alignments,\n" +
	    " - KNOW ALIGNMENT and CHANGE ALIGNMENT.\n");
	say(" - Just say 'know alignment',\n" +
	    " - or 'change alignment to ...',\n" +
            " - and I'll do it.\n");
#endif

    }
    else {
        say("The apprentice looks puzzled.\n");
    }
} /* handle_say */


handle_arrival(str)
{
    string who, rest, n;

    if (sscanf(str, "%s arrives%s", who, rest) != 2) {
	say("The apprentice looks brain damaged.\n");
	return;
    }
    if ((who == "The apprentice") || (who == "Apprentice"))
	return;

    if (!bird || !teleportee)
	busy_teleporting = 0;
    if (busy_teleporting) {
	say("The apprentice is concentrating on a spell.\n");
	return;
    }

    client = present(lower_case(who), environment(apprentice));
    if (!client) {
	say("The apprentice looks confused.\n");
	return;
    }

    if (client == latest_teleportee) {
	latest_teleportee = 0;
	return;
    }
    if (!present("castle ticket", client)) {
	/* A player/monster without a ticket has arrived! -- ATTACK! */
	say("The apprentice immediately notices that " +
	    who + " hasn't got a ticket.\n");
	apprentice->attacked_by(client);
	return;
    }

    n = client->query_name();
    say("The apprentice says: Welcome, " + n + ".\n");
    if (present("padrone", environment(apprentice)))
        say(" - The Wizard is standing right here, but he is inventing new magic\n" +
	    " - and cannot be interrupted. But maybe I can help you?\n");
    else
	say(" - The Wizard is not here today, he's out looking for\n" +
	    " - a castle he lost. But maybe I can help you?\n");
} /* handle_arrival */


take_money(sum)
{
    object the_money;

    if (client->query_money() < sum) {
	tell_object(client, "That would cost " + sum + " gold pieces, which you don't have.\n");
	return 0;
    }
    tell_object(client, "You pay " + sum + " gold coins for the magic assistance.\n");
    client->add_money(-sum);

    /*  Put the money in the vault -- but not if the client is a wizard! */
    if (client->query_level() < 20) {
	the_money = clone_object("obj/money");
	the_money->set_money(sum);
	call_other("players/padrone/walker/cell", "put_in_vault", the_money);
    }

    if (!random(10)) {
	tell_object(client, "The apprentice fumbles and -- BLAMMM!! The spell failed." +
		    " You are now a frog.\n");
	say("The apprentice fumbles and turns " +
	    client->query_name() + " into a frog.\n");
	client->frog_curse(1);
	return 0;
    }
    return 1;
}

abs(n) {
    if (n < 0) return -n; else return n;
}

/*----------------------------------------------------------
  This is a real hack.
  The apprentice is a monster, and he should react
  on strings like "Padrone hit Apprentice."
  (note that hits is misspelled hit),
  but since a monster does not react on any strings
  while it is busy fighting, we'll have to put ANOTHER,
  invisible monster in the room, just to cast the spell!
  That is, take_weapon is called by INVISIBLE_COMPANION,
  not by APPRENTICE.
----------------------------------------------------------*/

take_weapon(str)
{
    object foe, foe_weapon, app_weapon, new_app_weapon;
    int app_wc, foe_wc;
    string who, rest, junk;

    if (   (sscanf(str, "%s hits Apprentice%s\n", who, rest) == 2)
	|| (sscanf(str, "%s hit Apprentice%s\n", who, rest) == 2)
	|| (sscanf(str, "%s missed Apprentice%s\n", who, rest) == 2)
	|| (sscanf(str, "%s smash Apprentice%s\n", who, rest) == 2)) {

	foe = present(lower_case(who), environment(apprentice));
	if (!foe)
	    return;

	if (!random(2))
	    return;	/* Just 50% that he casts the spell.. */

	app_weapon = get_wielded(apprentice);
	if (app_weapon)
	    app_wc = app_weapon->weapon_class();
	else
	    app_wc = 0;
	foe_weapon = get_wielded(foe);
	if (foe_weapon) {
	    say("The apprentice casts the spell MAGNETIC WEAPON SUMMONING.\n");
	    write("The apprentice casts the spell MAGNETIC WEAPON SUMMONING.\n");
	    foe_wc = foe_weapon->weapon_class();
	    if (foe_weapon->drop())
		tell_object(foe, "Strange. That weapon seems to be stuck.\n");
	    else {
		say(capitalize(foe->query_name()) + "'s " +
			    foe_weapon->query_name() +
			    " jumps to the apprentice!\n");
		write("Your " + foe_weapon->query_name() +
		      " jumps to the apprentice!\n");
		move_object(foe_weapon, apprentice);
		foe->add_weight(- foe_weapon->query_weight());
		if (foe_wc > app_wc) {
		    apprentice->init_command("wield " + foe_weapon->query_name());
		    new_app_weapon = get_wielded(apprentice);
		    if (!new_app_weapon) {
			apprentice->init_command("wield " + app_weapon->query_name());
		    } /* wield failed (Doomsgiver, for example), re-wield old weapon */
		}
	    }
	} /* foe had a weapon */
    } /* if apprentice is in a fight */
} /* take_weapon */


get_wielded(living_obj)
{
    object an_item, this_item;
    string junk;

    an_item = first_inventory(living_obj);
    while (an_item) {
	this_item = an_item;
	an_item = next_inventory(an_item);
	if (   this_item->weapon_class()
	    && (sscanf(this_item->short(), "%s (wielded)", junk)))
	    return this_item;
    } /* while */
    return 0;
} /* get_wielded */

/* Called when apprentice died */
monster_died(poor_apprentice)
{
    object junk, murderer;

    if (invisible_companion)
	destruct(invisible_companion);
    teleportee = 0;
    latest_teleportee = 0;
    busy_teleporting = 0;
    if (bird) {
	tell_room(environment(bird),
		  "Suddenly the small bird fades away and disappears.\n");
        move_object(bird, "players/padrone/store");
        destruct(bird);
    }	
    return 0;
}


bird_handle_leaves(str) {
    string who, rest;
    object obj;

    if (sscanf(str, "%s leaves %s.\n", who, rest) != 2) {
	notify("The bird looks brain damaged.\n");
	return;
    }
    if (teleportee && who == teleportee->query_name())
	bird->init_command(rest);
} /* bird_handle_leaves */

bird_handle_say(str) {
    string who, phrase, a, b;

    if (   (sscanf(str, "%s says: %s\n", who, phrase) != 2)
	&& (sscanf(str, "%s says \"%s\"\n", who, phrase) != 2)	/* Morgar's say with quotes! */
	&& (sscanf(str, "%s tells you: %s\n", who, phrase) != 2)) {
	notify("The bird looks brain damaged.\n");
	return;
    }
    phrase = lower_case(phrase);
    client = present(lower_case(who), environment(bird));
    if (!client) {
	notify("The bird looks confused.\n");
	return;
    }
    if (client != teleportee) {
	notify("The small bird doesn't seem interested in what " + who + " has to say.\n");
	return;
    }

    if (   sscanf(phrase, "%syes%s", a, b) == 2
        || sscanf(phrase, "%steleport%s", a, b) == 2
        || sscanf(phrase, "%sok%s", a, b) == 2) {

	notify("The small bird chirps happily, flutters around " + who + ", and flies away.\n");
        move_object(bird, "players/padrone/store");
        destruct(bird);

	latest_teleportee = teleportee;

	tell_object(teleportee, "You are magically transferred somewhere.\n");
	teleportee->move_player("X", environment(apprentice));
	if (!present("castle ticket", teleportee)) {
	    object ticket;

	    tell_room(environment(apprentice),
		      "The apprentice says: As a bonus you get a free ticket to the Castle of Padrone!\n");
	    ticket = call_other("players/padrone/outside/front_yard", "make_ticket");
	    if (teleportee->add_weight(1)) {
		move_object(ticket, teleportee);
		notify("The apprentice gives ticket to " +
		       teleportee->query_name() + ".\n");
	    }
	    else {
		notify("The apprentice drops the ticket.\n");
		move_object(ticket, this_object());
	    }
	}

        teleportee = 0;
        busy_teleporting = 0;
    }
    else if (   sscanf(phrase, "%snot%s", a, b) == 2
        || sscanf(phrase, "%sno%s", a, b) == 2
        || sscanf(phrase, "%sdo not%s", a, b) == 2
        || sscanf(phrase, "%sdon't%s", a, b) == 2) {
	notify("The small bird looks disappointed and flies away.\n");
        move_object(bird, "players/padrone/store");
        destruct(bird);
	tell_room(environment(apprentice),
		  "The apprentice says: " + teleportee->query_name() +
		  " didn't want to be teleported.\n");
        teleportee = 0;
        busy_teleporting = 0;
    }
    else {
	notify("The small bird doesn't understand. It is still waiting for something.\n");
    }
} /* bird_handle_say */


/* For the NEW, IMPROVED monster class: */
setup_arrays() {

    chat_str = ({
	"The apprentice says: How can I help you?\n",
	"The apprentice studies the appointment book.\n"
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

    function2 = allocate(3);
    type2 = allocate(3);
    match2 = allocate(3);

    function2[0] = "take_weapon";
    type2[0] = "hit";
    match2[0] = "";
    type2[1] = "miss";
    match2[1] = "";
    type2[2] = "smash";
    match2[2] = "";

    chat_str3 = ({
	"The small bird flutters happily.\n",
	"The small bird sings cheerfully.\n",
	"The small bird seems to be waiting for something.\n",
	"The small bird seems to be waiting for someone to say something.\n",
	"The small bird looks at you questioningly.\n"
    });

    function3 = allocate(3);
    type3 = allocate(3);
    match3 = allocate(3);

    function3[0] = "bird_handle_say";
    type3[0] = "says";
    match3[0] = "";
    type3[1] = "tells you:";
    match3[1] = " ";
    function3[2] = "bird_handle_leaves";
    type3[2] = "leaves";
    match3[2] = "";

} /* setup_arrays */

notify(x) { say(x); write(x); }
