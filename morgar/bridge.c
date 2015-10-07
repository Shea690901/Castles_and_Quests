#include "std.h"

object bridge_troll;
int count;

#undef EXTRA_MOVE2
#define EXTRA_MOVE2 block(0);

#undef EXTRA_MOVE3
#define EXTRA_MOVE3 block(1);

#undef EXTRA_RESET
#define EXTRA_RESET\
    if (!find_living("bridge troll"))\
        start_troll();



ONE_EXIT("room/plane9","west",
	 "players/morgar/across","east",
	 "players/morgar/under","down",
	 "On a bridge",
	 "A troll bridge.\n", 1)

object bridge_troll;

block(num) {
    if (bridge_troll && living(bridge_troll)) {
        write("The troll blocks your way.\n");
        if (num==0) write("The troll says: Give me a treasure!\n");
        return 1;
    }
}

start_troll() {
    if(!bridge_troll || !living(bridge_troll)) {
        bridge_troll = clone_object("obj/monster.talk");
        call_other(bridge_troll, "set_name", "bridge troll");
        call_other(bridge_troll, "set_alias", "troll");
        call_other(bridge_troll, "set_short", "The bridge troll");
        call_other(bridge_troll, "set_long",
	   "It is a big, ugly, nasty bridge troll.\n");
        call_other(bridge_troll, "set_ac", 4);
        call_other(bridge_troll, "set_level",12);
        call_other(bridge_troll, "set_al",-200);
        call_other(bridge_troll, "set_wc",15);
        call_other(bridge_troll, "set_aggressive", 0);
        move_object(bridge_troll, "players/morgar/bridge");
        call_other(bridge_troll, "set_object", this_object());
        call_other(bridge_troll, "set_function", "gives");
        call_other(bridge_troll, "set_type", "gives");
        call_other(bridge_troll, "set_match", " ");
        call_other(bridge_troll, "set_chat_chance", 20);
        call_other(bridge_troll, "load_chat",
            "Troll says: Give me a treasure!\n");
    }
}

notify(str) {
    say(str);
    write(str);
}

gives(str) {
    string who, what, whom;
    int rand;
    object obj, next_obj;
    if(sscanf(str, "%s gives %s to %s.\n", who, what, whom) != 3)
        return;
    if(whom != "Troll")
        return;
    else if(what == "corpse") {
        notify("Troll says: Tasty, but not valuable.\n");
    } else {
        notify("Troll says: Ok.\n");
        call_other(bridge_troll, "move_player","down#players/morgar/under");
    }
}
