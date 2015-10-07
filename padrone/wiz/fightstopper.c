/* This is the fightstopper */

short() {
    return "A fightstopper";
}

long() {
    write("This is the fightstopper, a powerful magic item.\n" +
	  "It looks like a small dove of peace\n" +
	  "(or maybe it looks like a 1-Megaton thermonuclear warhead\n" +
	  "-- it's hard to say, but that would work too, right?)\n" +
	  "and when you use it,\n" +
	  "all fighting that is going on in the room will stop!\n");
}

init() {
    add_action("do_stop", "stop");
    add_action("do_use", "apply");
    add_action("do_use", "use");
    add_action("do_use", "activate");
}

id(str) {
    return    str == "fightstopper" || str == "fight-stopper"
	   || str == "fight stopper" || str == "stopper";
}

reset(arg) {

}

do_use(arg) {
    if (!id(arg))
	return 0;
    do_what_you_do();
    return 1;
}

do_stop(arg) {
    if (arg == "fight" || arg == "fighting" || arg == "it") {
	do_what_you_do();
	return 1;
    }
    else
	return 0;
}

do_what_you_do() {
    object this_obj, an_obj;
    int nr;
    string namestring;

    if (this_player()->query_level() < 20) {
	write("The fightstopper tells you: Bah! Puny mortal! You cannot use me!\n");
	return 1;
    }

    write("You activate the fightstopper.\n");
    say(this_player()->query_name() + " activates " +
	this_player()->query_possessive() + " fightstopper.\n");

    an_obj  = first_inventory(environment(this_player()));
    while (an_obj) {
	nr = nr + 1;
	this_obj = an_obj;
	an_obj = next_inventory(an_obj);

	if (living(this_obj)) {
	    namestring = call_other(this_obj, "query_name");
	    if (this_obj != this_player())
		write(namestring + " suddenly looks very peaceful.\n");
	    say(namestring + " suddenly looks very peaceful.\n", this_obj);
	    tell_object(this_obj, "You suddenly feel very peaceful.\n");
	    this_obj->stop_fight();
	    this_obj->stop_fight();
	    this_obj->stop_hunter();
	}
    } /* while */
} /* do_what_you_do */

get() { return 1; }
query_weight() { return 1; }
query_value() { return 20; }
