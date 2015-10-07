/* walker/rope_ladder.c -- hanging on the rope ladder under the castle */

#include "walker.h"

reset(arg) {  
    if (!arg)
	set_light(1);
}

short() { 
    if (set_light(0))
	return "On a rope ladder"; 
    return "dark room";
}

init() { 
    add_action("up", "up");
    add_action("down", "down");
}

up() {
    this_player()->move_player("up#players/padrone/walker/ladder_room");
    return 1;
}

down() {

    if (call_other(CASTLE, "query_airborne")) {
	write("The castle is flying high up among the clouds.\n");
	write("You cannot reach the ground.\n");
	return 1;
    }

    this_player()->move_player("down", call_other(CASTLE, "query_environment"));
    return 1;
} /* down */

long(str) { 
    if (set_light(0) == 0){ 
	write("It is dark.\n"); 
	return; 
    }  
    write("You are hanging on a rope ladder between the giant legs of the\n" +
	  "walking castle. Above you a small opening leads into the castle,\n");
    if (call_other(CASTLE, "query_airborne"))
	write("and very, very far below you, you can see the ground.\n");
    else
	write("and below you, you can see " +
	      call_other(CASTLE, "query_environment")->short() + ".\n");
    write("There are two obvious exits, up and down.\n");
} /* long */
