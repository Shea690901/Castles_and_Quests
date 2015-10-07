int charges, weight;
string name;

reset (arg) { if(arg) return;
    charges = 5 + random(16); name = "wand"; weight = 1; }

set_weight(w) { weight = w; }

query_weight() { return weight; }

add_weight() { return 1; }	/* Pell */

set_name(n) { name = n; }

set_charges(c) { charges = c; }

long() {
    write ("A long tapered wand with a question mark imprinted on its base.\n");
}

short() { return "A willow wand"; }

id(str) { return str == name; }

init() {
    add_action ("wave_wand"); add_verb ("wave");
    add_action ("wave_wand"); add_verb ("use");
}

query_value() { return (charges * 200); }

get() { return 1; }

wave_wand(str) {
    int wonder, creation;
    object effect, demon;

    if (str == "wand" || str == "willow wand") { /* Pell */
	write ("You wave the wand, summoning forth a magical force.\n");
	say (call_other (this_player(), "query_name") + " waves a magic wand.\n");
	wonder = random(10);
	if (wonder == 0) {
	    effect = clone_object ("obj/money");
	    write ("A shower of gold comes raining down!\n");
	    say ("Gold coins fall from the sky.\n");
	    call_other (effect, "set_money", random(100));
	    move_object (effect, environment (this_player()));
	    return 1;
	} else if (wonder == 1) {
	    teleport (this_player());
	    write ("You feel a wrenching sensation in your gut as you are transported elsewhere!\n");
	    say (call_other (this_player(), "query_name") +
		" disappears in a puff of smoke!\n");
	    return 1;
	} else if (wonder == 2) {
	    object a;		/* Pell */
	    if ((a = call_other (this_player(), "query_attack")) &&
		!a->query_npc()) { /* Pell: don't teleport NPC's! */
		teleport (call_other (this_player(), "query_attack"));
		write ("Your attacker disappears in a flurry of sparks!\n");
		say (call_other (this_player(), "query_attack") +
		    " disappears into thin air!\n");
		return 1;
	    } else {
		write ("You double over with nausea, and recover in a different room.\n");
		say (call_other (this_player(), "query_name") +
		    " disappears suddenly.\n");
		teleport (this_player());
		return 1;
	    }
	} else if (wonder == 3) {
	    write ("The wand fades and disappears with a loud POP!\n");
	    say ("The wand disappears with a sharp noise!\n");
	    teleport (this_object());
	    return 1;
	} else if (wonder == 4) {
	    write ("You are creating something!\n");
	    creation = random(4);
	    if (creation == 0) {
		effect = clone_object ("obj/rope");
		write ("A rope falls out of the sky and coils at your feet.\n");
		say ("A thick rope falls from the heavens.\n");
	    } else if (creation == 1) {
		effect = clone_object ("obj/stethoscope");
		write ("A stethoscope falls to the ground with a clatter.\n");
		say ("A stethoscope appears out of nowhere.\n");
	    } else if (creation == 2) {
		effect = clone_object ("obj/bag");
		write ("A bag appears at your feet.\n");
		say ("A bag appears on the ground.\n");
	    } else if (creation == 3) {
		demon = clone_object ("obj/monster");
		call_other (demon, "set_name", "demon");
		call_other (demon, "set_alias", "wand demon");
		call_other (demon, "set_race", "demon");
		call_other (demon, "set_short", "The demon of the wand");
		call_other (demon, "set_level", 12);
		call_other (demon, "set_hp", 150);
		call_other (demon, "set_wc", 12);
		call_other (demon, "set_al", -600);
		call_other (demon, "set_aggressive", 1);
		write ("You have conjured forth the wand's personal demon!\n");
		say ("A demon appears in a cloud of sulphurous smoke!\n");
		effect = demon;
	    }
	    move_object (effect, environment (this_player()));
	    return 1;		/* Pell */
	} else if (wonder == 5) {
	    write ("A stream of colorful butterflies spews from the wand,\n");
	    write ("flying off into the sky in random directions.\n");
	    say ("Several butterflies fly forth from the wand.\n");
	    return 1;
	} else if (wonder == 6) {
	    write ("The wand creates a beautiful pyrotechnic display,\n");
	    write ("which then fizzles out, leaving dying sparks on the ground.\n");
	    say ("The wand generates a fury of bright sparks.\n");
	    return 1;
	} else if (wonder == 7) {
	    write ("You feel your bones beginning to knit.\n");
	    call_other (this_player(), "heal_self", 20 + random(10));
	    return 1;
	} else if (wonder == 8) {
	    if (call_other (this_player(), "query_attack")) {
		write ("A network of electrical energy surrounds your opponent!\n");
		say (call_other (this_player(), "query_name") + " unleashes magical electricity!\n");
		call_other (call_other (this_player(), "query_attack"),
		    "hit_player", 20 + random(20));
		return 1;
	    } else {
		write ("The wand sputters for a second, then backfires on you!\n");
		say ("The wand backfires on " + call_other (this_player(), "query_name") + ".\n");
		call_other (this_player(), "reduce_hit_point", random(15)); /* Pell, new function */
		return 1;
	    }
	} else if (wonder == 9) {
	    steal();
	    write ("You feel your load lighten somewhat.\n");
	    return 1;		/* Pell */
	}
	charges -= 1;
	if (charges == 0) {
	    write ("The wand fades into nothingness.\n");
	    effect = environment();
	    if (call_other (effect, "query_level"))
		call_other (effect, "add_weight", -weight);
	    destruct (this_object());
	    }
    } else {
	notify_fail("Wave what?\n"); /* Pell */
	return 0;
    }
}

steal()
{
    object ob, who;
    int weight;

    who = this_player();
    ob = first_inventory(who);
    while(ob && ob == this_object()) { /* Pell */
        ob = next_inventory(ob);
    }
    if (!ob) return 1;		/* Pell */
    if (transfer (ob,this_object()) == 0) /* Pell */
        destruct(ob);
    return 1;
}

teleport(obj) {
    int dest;
    object moved;

    moved = obj;
    dest = random(8);
    if (dest == 0) {
	move_object (moved, "room/church");
	return 1;
    } else if (dest == 1) {
	move_object (moved, "room/adv_guild"); /* Pell */
	return 1;
    } else if (dest == 2) {
	move_object (moved, "room/shop");
	return 1;
    } else if (dest == 3) {
	move_object (moved, "players/quantos/desert/oasis");
	return 1;
    } else if (dest == 4) {
	move_object (moved, "players/quantos/under/maze36");
	return 1;
    } else if (dest == 5) {
	move_object (moved, "players/quantos/under/maze287");
	return 1;
    } else if (dest == 6) {
	move_object (moved, "players/quantos/plateau/cab_stop");
	return 1;
    } else if (dest == 7) {
	move_object (moved, "room/pub2"); /* Pell */
	return 1;
    }
}
