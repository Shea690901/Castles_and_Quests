reset(arg) {
    if (arg)
	return;
    set_light(1);
}

short() {
    if (set_light(0))
	return "Back yard";
    return "dark room";
}

init() {
    add_action("move1", "north");
    add_action("move2", "down");
    add_action("move3", "west");
    add_action("move4", "east");
    add_action("move5", "south");
}

move1() {
    this_player()->move_player("north#players/padrone/inside/kitchen");
    return 1;
}

move2() {
    this_player()->move_player("down#players/padrone/inside/coal_cellar");
    return 1;
}

move3() {
    this_player()->move_player("west#players/padrone/outside/sw");
    return 1;
}

move4() {
    this_player()->move_player("east#players/padrone/outside/se");
    return 1;
}

move5() {
    this_player()->move_player("south#players/padrone/vdb1");	/* Not "outside" */
    return 1;
}

long(str) {
    if (set_light(0) == 0) {
	write("It is dark.\n");
	return;
    }
    write("You are standing in the back yard, behind Padrone's Castle.\n" +
 	  "There is a door leading north into the house, probably to the kitchen\n" +
	  "(sniff sniff), and another door seems to be leading down into the cellar.\n" +
 	  "You can follow the small path around the castle, either to the west\n" +
	  "or to the east, and another small path leads south, into the bushes.\n");
    write("    There are five obvious exits: north, south, east, west and down.\n");
}
