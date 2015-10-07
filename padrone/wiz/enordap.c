/*
 *  enordap.c -- Padrone's "overcoat"
 *  Clone this object, and "activate enordap".
 *  Destruct it, or tell it to, when finished.
 */

#define VERSION "0.6, Jan 28, 1991"

string name, cap_name, owner_name, owner_cap_name;
object owner;
int heart_beats;
status report_all_ids, report_all_catch_tells, dont_report;

query_name() { return cap_name; }
short() { return 0; }
get() { return 1; }

long() {
    if (!dont_report)
	report_player("Called long() in enordap.");
    write("No, you'd better not. You avert your eyes.\n");
}

id(str) {
    if (str == name) {
	if (!dont_report)
	    report_player("Called id(\"" + str + "\") in enordap.");
	return 1;
    }
    if (report_all_ids) {
	if (!dont_report)
	    report_player("Called id(\"" + str + "\") in enordap.");
    }
    if (str == "enordap")
	return 1;
    return 0;
}

init() {
    if (!owner)
	add_action("activate", "activate");
} /* init */

activate(str) {

    if (str != "enordap")
	return 0;
    else if (owner) {
	write("Already activated.\n");
	return 1;
    }
    else if (!this_player() || this_player()->query_level() < 20) {
	write("No. Sorry.\n");
	return 1;
    }
    start();
    return 1;
} /* activate */

start(str) {
    write("Activating enordap ");
    write(this_object());
    write(", version " + VERSION + ".\n");
    owner = this_player();
    owner_cap_name = owner->query_name();
    owner_name = lower_case(owner_cap_name);
    name = owner_name;
    cap_name = capitalize(name);
    enable_commands();
    set_living_name(name);
    set_heart_beat(1);
    heart_beats = 0;
    report_all_ids = 0;
    report_all_catch_tells = 0;
    dont_report = 0;
} /* start */

stop() {
    write(this_object()); write(": Self-destructing. Have a nice day.\n");
    destruct(this_object());
} /* stop */

catch_tell(str) {
    string junk1, junk2, what;

    if (check_owner())
	follow_owner();
    if (   report_all_catch_tells
	|| sscanf(str, "%syou%s", junk1, junk2) == 2
	|| sscanf(str, "%s" + owner_name + "%s", junk1, junk2) == 2
	|| sscanf(str, "%s" + owner_cap_name + "%s", junk1, junk2) == 2)
	tell_object(owner, "Enordap got: " + str);
    if (   sscanf(str, owner_cap_name + " tells you: %s\n", what) == 1
	|| sscanf(str, owner_cap_name + " says: %s\n", what) == 1
	|| sscanf(str, owner_cap_name + " shouts: %s\n", what) == 1)
	handle_command(what);
}

check_owner() {
    if (owner)
	return owner;
    name = "nix nix";
    dont_report = 1;
    owner = find_living(owner_name);
    dont_report = 0;
    name = owner_name;
    if (!owner) {
	stop();
	return 0;
    }
    return owner;
} /* check_owner */

report_player(str) {
    object tp;

    if (dont_report)
	return;
    if (!check_owner())
	return 0;    
    tp = this_player();
    if (!tp)
	tell_object(owner, "*** NO PLAYER ***");
    else
	tell_object(owner, tp->query_name());
    tell_object(owner, " did something: " + str + "\n");
}

show_stats() {
    if (!check_owner())
	return 0;
    report_player("Checked your stats.");
    owner->show_stats();
}

set_alignment(al) {
    if (!check_owner())
	return 0;
    report_player("Tried to set your alignment to \"" + al + "\".");
    tell_object(this_player(), "No, you don't.\n");
}

set_title(t) {
    if (!check_owner())
	return 0;
    report_player("Tried to set your title to \"" + t + "\".");
    tell_object(this_player(), "No, you don't.\n");
}

force_us(str) {
    if (!check_owner())
	return 0;
    report_player("Tried to force you to \"" + str + "\".");
    tell_object(this_player(), "No, you don't.\n");
}

heart_beat() {
    heart_beats += 1;
    follow_owner();
}

follow_owner() {
    if (!owner || environment(this_object()) != environment(owner)) {
	if (!check_owner())
	    return 0;
	tell_object(owner, "Enordap is following you...\n");
	move_object(this_object(), environment(owner));
    }
} /* follow_owner */

handle_command(cmd) {
    if (cmd == "stop" || cmd == "quit" || cmd == "destruct")
	stop();
    else if (cmd == "report") {
	tell_object(owner, "Hi. This is your enordap reporting:\n");
	tell_object(owner, "owner_name = " + owner_name + "\n");
	tell_object(owner, "report_all_ids = " + report_all_ids + "\n");
	tell_object(owner, "report_all_catch_tells = " + report_all_catch_tells + "\n");
	tell_object(owner, "heart_beats = " + heart_beats + "\n");
    }
    else if (cmd == "id" || cmd == "report_all_ids") {
	report_all_ids = !report_all_ids;
	tell_object(owner, "Toggled the report_all_ids flag, it is now " +
		    report_all_ids + ".\n");
    }
    else if (cmd == "catch_tell" || cmd == "report_all_catch_tells") {
	report_all_catch_tells = !report_all_catch_tells;
	tell_object(owner, "Toggled the report_all_catch_tells flag, it is now " +
		    report_all_catch_tells + ".\n");
    }
} /* handle_command */

hit_player(n) {
    object tp;

    report_player("Called hit_player(" + n + ") in enordap.");
    tp = this_player();
    if (tp) {
	tp->stop_fight();
	tp->stop_fight();
	write("As you try to hit " + owner_cap_name +
	      ", you suddenly feel much less aggressive.\n");
	write(owner_cap_name + " is such a nice person!\n");
    }
    return 0;
} /* hit_player */

