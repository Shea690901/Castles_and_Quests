/* antigrav.c */

int weight;

short() {
    return "A small magic stone with a strange weight";
}

long() {
    write("This is a small stone, and you understand that it must be magic.\n" +
	  "Somehow its weight doesn't feel right...\n");
    if (weight < 0)
	write("If you didn't know better, you would guess\n" +
	      "that it weighs less than nothing!\n");
    if (this_player()->query_level() >= 20) {
	write("Wizard: The weight of this stone is currently " +
	      weight + ".\n");
	write("        You can set the weight ('set weight') to whatever you like!\n");
    }
} /* long */

reset(arg) {
    if (!arg)
	weight = -1;
}

init() {
    add_action("set", "set");
}

set(str) {
    string what; int how;

    if (!str)
	return 0;
    if (sscanf(str, "%s %d", what, how) != 2)
	return 0;
    if (what != "stone" && what != "weight")
	return 0;

    if (this_player()->query_level() < 20) {
	write("You tried to set the weight of the stone, but nothing happens.\n");
	return 1;
    }
    write("You set the weight of the stone to " + how + ".\n");
    weight = how;
    return 1;
} /* set */

id(str) {
    return    str == "stone" || str == "magic stone"
	   || str == "stone of gravity";
}

get() {
    return 1;
}

query_name() { return "stone"; }
query_weight() { return weight; }
set_weight(w) { weight = w; }

query_value() {
    if (weight < 0)
	return -100 * weight;
    else
	return 5;
}
