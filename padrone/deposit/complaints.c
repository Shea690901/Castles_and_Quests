/*  complaints.c -- the complaints dept. of the safe-deposit box service
 *	Thomas Padron-McCarthy (Padrone), padrone@lysator.liu.se, 1990
 *	Share and enjoy! No rights reserved except the right to reserve rights.
 *	This file latest updated January 17, 1991 by Padrone.
 */

#include "std.h"
#include "deposit.h"

#undef EXTRA_INIT
#define EXTRA_INIT extra_init();

extra_init() {
    add_action("complain", "complain");
} /* extra_init */

ONE_EXIT(DEPOSIT, FROM_COMPLAINTS,
	 "Complaints Department",
	 "This is the Complaints Department of\n" +
	 "Padrone's Maximum-Security Safe-Deposit Box Service.\n" +
	 "Behind a long counter of gleaming marble, a complaints clerk\n" +
	 "handles any complaints raised against the establishment.\n" +
	 "Feel free to complain (just type 'complain').\n", 1)

complain(str) {
    if (str)
	return 0;
    write("You complain.\n");
    call_other(BOXROOM, "complain");
    return 1;
} /* complain */
