#include "std.h"

object guest, tk;
string guestname;

#undef EXTRA_RESET
#define EXTRA_RESET extra_reset(arg);

#undef EXTRA_INIT
#define EXTRA_INIT extra_init();

#undef EXTRA_MOVE1
#define EXTRA_MOVE1 extra_move1();

extra_reset(arg) {
    if (!tk || !present(tk)) {
	tk = clone_object("obj/weapon");
	tk->set_name("tungur kniivur");
	tk->set_short("Tungur Kniivur");
	tk->set_long("A heavy knife.\n");
	tk->set_class(8);
	tk->set_value(20);
	tk->set_weight(5);
	tk->set_alt_name("kniivur");
	move_object(tk, this_object());
    }
} /* extra_reset */

extra_init() {
    if (query_occupied()) {
	write("Sorry, that room is occupied by " + guestname + ".\n");
	write("You'll have to wait outside.\n");
	tell_object(guest, this_player()->query_name() +
		   " tried to magically enter the guestroom, but failed (haha!).\n");
	this_player()->move_player("back out again#players/padrone/inside/w_uhall");
    }
    else {
	guest = this_player();
	guestname = guest->query_name();
	write("Welcome to the West Guestroom!\n");
    }
} /* extra_init */

extra_move1() {
    guest = 0;
}

ONE_EXIT("players/padrone/inside/w_uhall", "south",
	 "West Guestroom",
	 "This is the West Guestroom of the Castle, a spacious and\n" +
	 "luxuriously furnished room on the second floor.\n" +
	 "In this room you are guaranteed privacy, because\n" +
	 "while you are inside this room, noone else can enter!\n", 1)

query_occupied() {

    if (!guest)
	return 0;
    else if (!present(guest, this_object())) {
	write("Strange -- this guestroom used to be occupied\n" +
	      "by " + guestname + ", but there is noone here now...\n");
	guest = 0;
	return 0;
    }
    else
	return guest;
} /* query_occupied */
