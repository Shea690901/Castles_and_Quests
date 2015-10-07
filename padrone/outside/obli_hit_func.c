/* Used by Sir Obliterator's Unholy Avenger */

/* If you change this, change crossing.c too: */
#define WEAPON_CLASS 20

weapon_hit(victim) {

    if (call_other(victim, "query_name") == "Violens") {
	if (!random(3)) {
	    write("The unholy avenger screams in thirst for blood!\n");
	    say("The unholy avenger screams in thirst for blood!\n");
	    return 20;
	}
	return 4;
    }
    else {
	write("The unholy avenger seems totally uninterested in this fight.\n");
	return - WEAPON_CLASS + 3;
    }
} /* weapon_hit */
