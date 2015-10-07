/*  box.c -- a safe-deposit box
 *	Thomas Padron-McCarthy (Padrone), padrone@lysator.liu.se, 1990
 *	Share and enjoy! No rights reserved except the right to reserve rights.
 *	This file latest updated January 17, 1991 by Padrone.
 */

#include "deposit.h"

string owner_name, name;

reset(arg) {
    if (arg)
	return;
    name = "unused-box";
}

short() {
    return "A safe-deposit box labeled " + capitalize(owner_name) + ". " +
           "It's name is " + name;
}

long() {
    write(short() + ".\n");
    if (first_inventory(this_object()))
	write("There is something in it, worth " +
	      query_boxvalue() + " gold coins.\n");
    else
	write("It is empty.\n");
}

set_owner(str) {
    owner_name = lower_case(str);
    name = "box-of-" + lower_case(str);
}

query_name() { return name; }

id(str) { return str == name || str == "box"; }

get() { return 0; }

can_put_and_get() { return 1; }

add_weight(w) { return 1; }	/* No limit! */


query_inventory() {
    object the_item;
    string temp;

    the_item = first_inventory(this_object());
    temp = "";
    while(the_item) {
	temp = temp +
	       owner_name + " " +
	       the_item->query_name() + " " +
	       the_item->query_value() + "\n";
	the_item = next_inventory(the_item);
    }
    return temp;
} /* query_inventory */

query_boxvalue() {
    object the_item;
    int sum, temp;

    the_item = first_inventory(this_object());
    sum = 0;
    while(the_item) {
	temp = the_item->query_value();
	if (temp > INSURANCE_LIMIT)
	    temp = INSURANCE_LIMIT;
	sum = sum + temp;
	the_item = next_inventory(the_item);
    }
    return sum;
} /* query_boxvalue */
