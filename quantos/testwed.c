#include "std.h"

object preacher;

init() {
    add_action("west"); add_verb("west");
    add_action("pray"); add_verb("pray");
}

short() {
    return "Church hall";
}

long() {
    write("You are in the sacred church hall.\n"); 
}

pray() {
    say(call_other(this_player(),"query_name",0) + " prays.\n");
    write("You fall to you knees, and ask for forgivness.\n");
    return 1;
    }

west() {
    call_other(this_player(), "move_player", "west#room/attic");
}

reset(arg) {
    if (!arg)
	set_light(1);
    if (!precher || !living(precher)) {
	precher = clone_object("obj/precher");
	move_object(precher, this_object());
    }
}
