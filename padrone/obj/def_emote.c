/* obj/def_emote.c - a defective emote command */

short() {
    return "A defective emote command";
}

long() {
    write("This is one of Padrone's experiments - a powerful wizard command!\n" +
	  "Unfortunately it is marked 'EXPERIMENTAL', and looks somewhat\n" +
	  "defective. But feel free to use it anyway!\n");
}

reset(arg) {
}

init() {
    add_action("do_emote", "emote");
}

id(str) {
    return    str == "emote command"  || str == "emote" || str == "command"
           || str == "defective emote command";
}

query_name() { return "emote command"; }
query_weight() { return 0; }
query_value() { return 10; }
get() { return 1; }

do_emote(str) {
    string pn, what, how;

    if (!str) {
	write("Emote what ?\n");
	return 1;
    }

    /* Remove trailing bangs and dots. */
    while (sscanf(str, "%s.", str) == 1)
	{ }
    while (sscanf(str, "%s!", str) == 1)
	{ }

    if (sscanf(str, "%ss %s", what, how) != 2) {
	write("*** Emote syntax error. Usage: emote VERBs REST\n");
	return 1;
    }
    if (sscanf(str, "is %s", how) == 1) {
	what = "be";
    }

    pn = this_player()->query_name();
    say(pn + " tries to " + what + " " + how +
	", but fails miserably.\n");
    write("You emote: " + pn + " tries to " + what + " " + how +
	  ", but fails miserably.\n");

    return 1;
} /* do_emote */
