/*  deposit.c -- Padrone's Maximum-Security Safe-Deposit Box Service
 *	Thomas Padron-McCarthy (Padrone), padrone@lysator.liu.se, 1990
 *	Share and enjoy! No rights reserved except the right to reserve rights.
 *	This file latest updated January 17, 1991 by Padrone.
 */

#include "std.h"
#include "deposit.h"

#undef EXTRA_INIT
#define EXTRA_INIT  extra_init();

#undef EXTRA_LONG
#define EXTRA_LONG  if (str == "sign") { read("sign"); return; }

#undef EXTRA_MOVE2
#define EXTRA_MOVE2  if (extra_move2()) return 1;

id(str) {
    return str == "sign";
}

extra_init() {
    add_action("store", "store");
    add_action("retrieve", "retrieve");
    add_action("list", "list");
    add_action("rent", "rent");
    add_action("read", "read");
} /* extra_init */

THREE_EXIT(DEPOSIT_PLACE, LEAVE,
	   BOXROOM, TO_BOXROOM,
	   COMPLAINTS, TO_COMPLAINTS,
	   "Padrone's Maximum-Security Safe-Deposit Box Service",
	   "This is Padrone's Maximum-Security Safe-Deposit Box Service.\n" +
	   "Rows and rows of gleaming deposit boxes, made in steel and mithril,\n" +
	   "line the walls. TV cameras constantly monitor the area.\n" +
	   "Obviously, this is a quality establishment.\n" +
	   "The storage room for the boxes is " + TO_BOXROOM + ", the complaints department\n" +
	   "is " + TO_COMPLAINTS + ", and the exit is to the " + LEAVE + ".\n" +
	   "There is a sign on the wall.\n", 1)

read(str) {
    if (str == "sign") {
	write("The sign says:\n\n" +
	      "    Welcome to Padrone's Maximum-Security Safe-Deposit Box Service.\n\n" +
	      "    You can store your things in a deposit box and retrieve them later.\n" +
	      "    If your items should be lost (e. g. due to a world crash),\n" +
	      "    an insurance, limited to " + INSURANCE_LIMIT + " gold coins per item, applies.\n" +
	      "    The insurance does not apply to items stored inside other items.\n" +
	      "    If your deposit box disappears, you get a new one without cost.\n" +
	      "    Because this is a maximum-security storage facility,\n" +
	      "    the rent for a deposit box is " + FEE + " gold coins.\n" +
	      "    You can rent your own maximum-security safe-deposit box\n" +
	      "    with the command 'rent'.\n" +
	      "    Then use the commands 'store', 'retrieve' and 'list'.\n" +
	      "    The complaints department is " + TO_COMPLAINTS + " from here.\n");
	return 1;
    }
    else
	return 0;
} /* read */

store(str) {
    if (!str)
	return 0;
    call_other(BOXROOM, "store_item", str);
    return 1;
} /* store */

retrieve(str) {
    if (!str)
	return 0;
    call_other(BOXROOM, "retrieve_item", str);
    return 1;
} /* retrieve */

list(str) {
    if (str)
	return 0;
    call_other(BOXROOM, "list_my_box");
    return 1;
} /* list */

rent(str) {
    object the_money;

    if (str && (str != "box"))
	return 0;
    call_other(BOXROOM, "rent");
    return 1;
} /* rent */

extra_move2() {
    write("A small steel door leads to the room where everything is stored.\n");
    if (this_player()->query_level() < 20) {
	write("However, this door is for wizards only.\n");
	return 1;
    }
    else
	return 0;
} /* extra_move2 */
