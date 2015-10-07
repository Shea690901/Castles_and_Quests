/* The generic "maze room object", to be inherited from the rooms in the maze. */

string north_room, south_room, west_room, east_room;

reset(arg) {
    if (arg)
	return;
    set_light(1);
} /* reset */

init() {
    add_action("north", "north");
    add_action("south", "south");
    add_action("east", "east");
    add_action("west", "west");
    add_action("smash", "smash");
    add_action("smash", "break");
} /* init */

id(str) {
    return    str == "mirror" || str == "mirrors"
	   || str == "north mirror" || str == "south mirror"
	   || str == "east mirror" || str == "west mirror";
} /* id */

long(str) {
    if (set_light(0) == 0){
       write("It is dark.\n");
       return;
    }
    else if (id(str)) {
	write("A large mirror covering the wall.\n" +
	      "You wouldn't be surprised if this is a magic mirror.\n");
    }
    else {
	write("You are in the mirrormaze that was made by Uglagrok the mirrormage.\n" +
	      "The walls are covered with mirrors, and everything seems\n" +
	      "strangely reversed.\n");
	write("It could be very easy to get lost in this place,\n" +
	      "especially with all those reversed directions...\n");
	write("    There are four obvious exits, north, south, east and west.\n");
    }
} /* long */
    
short() {
    if (set_light(0))
	return "In the mirrormaze";
    return "Dark room";
} /* short */

smash(str) {
    if (!id(str))
	return 0;
    write("That would not be appreciated.\n");
    return 1;
} /* smash */

north() {
    if (north_room)
	this_player()->move_player("north" + "#" + "players/padrone/maze/" + north_room);
    else
	write("Ouch! That was just a mirror!\n");
}

south() {
    if (south_room)
	this_player()->move_player("south" + "#" + "players/padrone/maze/" + south_room);
    else
	write("Ouch! That was just a mirror!\n");
}

east() {
    if (east_room)
	this_player()->move_player("east" + "#" + "players/padrone/maze/" + east_room);
    else
	write("Ouch! That was just a mirror!\n");
}

west() {
    if (west_room)
	this_player()->move_player("west" + "#" + "players/padrone/maze/" + west_room);
    else
	write("Ouch! That was just a mirror!\n");
}
