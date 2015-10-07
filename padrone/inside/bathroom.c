#include "std.h"

object guest;
string guestname;

#undef EXTRA_INIT
#define EXTRA_INIT extra_init();

#undef EXTRA_MOVE1
#define EXTRA_MOVE1 extra_move1();

extra_init() {
    if (query_occupied()) {
	write("Sorry, the bathroom is occupied by " + guestname + ".\n");
	write("You'll have to wait outside.\n");
	tell_object(guest, call_other(this_player(), "query_name") +
		   " tried to magically enter the bathroom, but failed (haha!).\n");
	call_other(this_player(), "move_player", "back out again#players/padrone/inside/w_uhall");
    }
    else {
	guest = this_player();
	guestname = call_other(guest, "query_name");
	/* 	write("Welcome to the bathroom!\n"); */
    }
} /* extra_init */

extra_move1() {
    guest = 0;
}

ONE_EXIT("players/padrone/inside/w_uhall", "north",
	 "Bathroom",
	 "This is the bathroom.\n" +
	 "In this room you are guaranteed privacy, because\n" +
	 "while you are inside this room, noone else can enter!\n", 1)

query_occupied() {

    if (!guest)
	return 0;
    else if (!present(guest, this_object())) {
	write("Strange -- the bathroom used to be occupied\n" +
	      "by " + guestname + ", but there is noone here now...\n");
	guest = 0;
	return 0;
    }
    else
 	return guest;
} /* query_occupied */
