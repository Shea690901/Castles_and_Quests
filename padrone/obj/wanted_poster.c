/*  wanted_poster.c -- the posters from the Sheriff's Office in the Castle of Padrone.
 *  Version: 1.1 -- Jan 17, 1991
 */

string bandits_capname, bandits_lname, bandits_title, crime;
int bandits_level, reward, reset_count;

short() {
    return "A poster from the Police Department about " + bandits_capname;
}

long() {
    read("poster");
}

reset(arg) {
    if (!arg)
	reset_count = 0;
    else
	reset_count = reset_count + 1;

    if (reset_count >= 2)
	call_out("destruct_me", 1);
}

destruct_me() {
    say("The poster about " + bandits_capname + " has become old, and crumbles to dust.\n");
    destruct(this_object());
}

init() {
    add_action("read", "read");
}

id(str) {
    return    str == "poster"
           || str == "poster about " + bandits_lname
           || str == "poster about " + bandits_capname;
}

read(str) {
    if (!id(str))
	return 0;

    say(this_player()->query_name() +
	" reads the poster about " + bandits_capname + ".\n");

    write("You read the poster about " + bandits_capname + ". It says:\n\n");

    write("    WANTED: " + bandits_capname + " " + bandits_title + "\n\n");

    write("    This level " + bandits_level + " criminal is wanted DEAD (and not alive)\n");
    write("    by the Sheriff's Office in the Castle of Padrone\n");
    write("    for " + crime + ".\n");
    write("    This person is dangerous, armed and desperate.\n");
    write("    Upon deliverance of this desperado's dead body at the\n");
    write("    Sheriff's Office, a REWARD of " + reward + " gold coins will be paid.\n\n");

    return 1;
} /* read */

get() {
    return 1;
}

query_weight() { return 1; }
query_value() { return 2; }

init_poster(bn, bt, bl, c, r) {
    bandits_capname = bn;
    bandits_lname = lower_case(bn);
    bandits_title = bt;
    bandits_level = bl;
    crime = c;
    reward = r;
} /* init_poster */
