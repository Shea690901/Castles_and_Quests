/* walker/gate_room.c -- the room inside the gates of the walking castle */

#include "walker.h"

reset(arg) {  
    if (arg)
	return;
    set_light(1);
}

short() { 
	if (set_light(0))
	    return "Inside the gates of the walking castle"; 
	return "dark room";
}

init() { 
    add_action("north", "north");
    add_action("out", "out");
    add_action("out", "south");
    add_action("west", "west");
    add_action("east", "east");
}

north() {
    this_player()->move_player("north#players/padrone/walker/castle_yard");
    return 1;
}

west() {
    this_player()->move_player("west#players/padrone/walker/gate_control");
    return 1;
}

east() {
    this_player()->move_player("east#players/padrone/walker/guard_room");
    return 1;
}

out() {

    if (!call_other(CASTLE, "query_drawbridge_down")) {
	write("The drawbridge is up and the gates are closed. You cannot get out.\n");
	return 1;
    }
    if (call_other(CASTLE, "query_airborne")) {
	write("The castle is flying high up among the clouds.\n");
	write("You cannot reach the ground.\n");
	return 1;
    }

    this_player()->move_player("south", call_other(CASTLE, "query_environment"));
    return 1;
} /* out */

long(str) { 
    if (set_light(0) == 0){ 
	write("It is dark.\n"); 
	return; 
    }  
    write("You are standing just inside the gates of the walking castle.\n");
    write("A door leads west to a small room, and another door leads\n" +
	  "east to a guard room. The castle yard is north.\n");
    if (!call_other(CASTLE, "query_drawbridge_down"))
	write("The drawbridge is up and the gates are closed. You cannot get out.\n");
    else {
	write("The drawbridge is down and the gates are open.\n" +
	      "You can leave the castle through the gates to the south.\n");
	if (call_other(CASTLE, "query_airborne"))
	    write("Outside the gates you see some clouds.\n");
	else
	    write("Outside the gates you see " +
		  call_other(CASTLE, "query_environment")->short() + ".\n");
    }
} /* long */
