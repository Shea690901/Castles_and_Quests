/*  deposit_f.c -- the facade of the safe-deposit box service
 *	Thomas Padron-McCarthy (Padrone), padrone@lysator.liu.se, 1990
 *	Share and enjoy! No rights reserved except the right to reserve rights.
 *	This file latest updated January 18, 1991 by Padrone.
 */

#include "deposit.h"

id(arg) {
    return    arg == "safe-deposit box service"
	   || arg == "deposit box service" || arg == "service" || arg == "deposit"
	   || arg == "Padrone's" || arg == "padrone's" || arg == "facade";
}

short() {
    return "To the " + ENTER + " you can enter a safe-deposit box service";
}

long() {
    write("This is Padrone's Maximum-Security Safe-Deposit Box Service.\n" +
	  "It is a small but sturdy building, built of stone and with a\n" +
	  "heavy-looking steel door.\n" +
	  "It is open, and you may enter.\n");
}

init() {
    add_action("enter_dir", ENTER);
    add_action("enter", "enter");
}

enter_dir(str) {
    this_player()->move_player(ENTER + "#" + DEPOSIT);
    return 1;
}

enter(str) {
    if (!str || !id(str))
	return 0;
    enter_dir();
    return 1;
}

get() {
    return 0;
}

reset(arg) {
    if (arg)
        return;
    move_object(this_object(), DEPOSIT_PLACE);
}
