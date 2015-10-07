/* obj/def_force.c - a defective force command */

short() {
    return "A defective force command";
}

long() {
    write("This is another of Padrone's experiments. After his near success\n" +
	  "with the powerful wizard command EMOTE, he went on to try to make FORCE.\n" +
	  "Unfortunately, this command too is marked 'EXPERIMENTAL', and it looks\n" +
	  "somewhat defective. But feel free to use it anyway!\n");
}

reset(arg) {
}

init() {
    add_action("do_force", "force");
}

id(str) {
    return    str == "force command"  || str == "force" || str == "command"
           || str == "defective force command";
}

query_name() { return "force command"; }
query_weight() { return 0; }
query_value() { return 10; }
get() { return 1; }

do_force(str) {
    string pn, who, what;
    object p;

    if (!str) {
        write("Force who to do what?\n");
        return 1;
    }

    /* Remove trailing bangs and dots. */
    while (sscanf(str, "%s.", str) == 1)
        { }
    while (sscanf(str, "%s!", str) == 1)
        { }

    if (sscanf(str, "%s %s", who, what) != 2) {
        write("*** Force syntax error. Usage: force NAME COMMAND\n");
        return 1;
    }

    p = present(lower_case(who), environment(this_player()));
    if (!p || !living(p)) {
        write("*** Force error. Noone called " + who + " in this room.\n");
        return 1;
    }

    pn = call_other(this_player(), "query_name");
    say(pn + " tries to force " + who + " to " + what +
        ", but " + this_player()->query_pronoun() + " fails.\n", p);
    tell_object(p, pn + " tries to force you to " + what +
                ", but " + this_player()->query_pronoun() + " fails.\n");
    write("You try to force " + who + " to " + what + ", but you fail.\n");
    write("Instead, you yourself feel an irresistible urge to " + what + "!\n");

    command(what, this_player());

    return 1;
} /* do_force */
