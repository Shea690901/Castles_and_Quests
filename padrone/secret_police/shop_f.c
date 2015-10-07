/*  shop_f.c -- the facade of the secret police shop
 *	Thomas Padron-McCarthy (Padrone), padrone@lysator.liu.se, 1991
 *	Share and enjoy! No rights reserved except the right to reserve rights.
 *	This file latest updated February 23, 1991 by Padrone.
 */

#include "../config.h"
#include "location.h"

id(arg) {
    return arg == "shop" || arg == "facade";
}

short() {
    return "To the east, there is a shop. It is just an ordinary shop";
}

long() {
    write("This is a small shop, It looks just like an ordinary shop\n" +
	  "where you can buy and sell things. It looks just like an ordinary shop.\n" +
	  "Absolutely ordinary. Nothing strange with this shop.\n");
}

init() {
    add_action("east", "east");
    add_action("enter", "enter");
}

east(str) {
    this_player()->move_player("east#players/padrone/secret_police/shop");
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
    move_object(this_object(), SHOP_PLACE);
}
