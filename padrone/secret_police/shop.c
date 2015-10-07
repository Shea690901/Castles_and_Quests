/* secret_police/shop.c */

#include "../config.h"
#include "location.h"		/* Defines where to put the shop! */
#include "std.h"
#include "../../../obj/door.h"

object shopkeeper;
string chat_str;

#undef EXTRA_INIT
#define EXTRA_INIT extra_init();

extra_init() {
    add_action("do_sell", "sell");
    add_action("do_value", "value");
    add_action("do_buy", "buy");
    add_action("do_list", "list");
    add_action("do_read", "read");
} /* extra_init */

id(str) {
    return str == "note" || str == "small note";
}

#undef EXTRA_LONG
#define EXTRA_LONG \
	if (str == "note" || str == "small note") { \
		do_read("note"); \
		return 1; \
	}

#undef EXTRA_RESET
#define EXTRA_RESET extra_reset();

extra_reset() {
    object obj, key;

    if (!chat_str) {
	chat_str = ({
	    "The shopkeeper looks at you suspiciously.\n",
	    "The shopkeeper says: Psst! We might have a job for you. Go north, quickly!\n",
	    "The shopkeeper says: Psst! You can earn 10000 gold coins!\n",
	    "The shopkeeper says: You can earn 10000 gold coins!\n",
	    "The shopkeeper says: Psst! We'll give you ten thousand for a small job!\n",
	    "The shopkeeper tries to look like a shopkeeper.\n",
	    "The shopkeeper pretends to be counting some money.\n",
	});
    }

    if (!shopkeeper) {
	shopkeeper = clone_object("obj/monster");
	shopkeeper->set_name("shopkeeper");
	shopkeeper->set_alias("the shopkeeper");
	shopkeeper->set_short("The shopkeeper");
	shopkeeper->set_long("At first glance, this shopkeeper looks like an ordinary\n" +
			     "shopkeeper - fat, middle-aged, big and strong. But as\n" +
			     "you take a closer look at this particular shopkeeper\n" +
			     "you notice some very un-shopkeeper-like features, like\n" +
			     "a set of more or less hidden daggers and a pair of dark\n" +
			     "sunglasses...\n");
	shopkeeper->set_level(4);
	shopkeeper->set_hp(250);
	shopkeeper->set_al(80);
	shopkeeper->set_male();
	shopkeeper->set_spell_mess1("The shopkeeper kicks his opponent very hard.");
	shopkeeper->set_spell_mess2("The shopkeeper kicks you very hard. You are hurt!");
	shopkeeper->set_chance(20);
	shopkeeper->set_spell_dam(10);
	shopkeeper->load_chat(20, chat_str);

        move_object(shopkeeper, this_object());

	obj = clone_object("players/padrone/secret_police/membership");
	move_object(obj, shopkeeper);
	obj->set_name("shopkeeper");

	obj = clone_object("obj/weapon");
        obj->set_name("long, sharp dagger");
        obj->set_alt_name("dagger");
        obj->set_class(7);
        obj->set_value(15);
        obj->set_weight(1);
        obj->set_short("A long, sharp dagger");
        move_object(obj, shopkeeper);
	shopkeeper->init_command("wield long, sharp dagger");

	obj = clone_object("obj/weapon");
        obj->set_name("dagger");
        obj->set_class(6);
        obj->set_value(10);
        obj->set_weight(1);
        obj->set_short("A dagger");
        move_object(obj, shopkeeper);

	MAKE_KEY(key, "iron", "interrogation")
        move_object(key, shopkeeper);
    }
} /* extra_reset */

check_shopkeeper() {
    if (!shopkeeper) {
	write("How can you do that when there is no shopkeeper here?\n");
	return 0;
    }
    else
	return 1;
} /* check_shopkeeper */

do_sell(item) {
    if (!check_shopkeeper())
	return 1;
    else {
	notify("The shopkeeper says: Sorry, but we don't buy " + item + "s.\n");
	return 1;
    }
} /* do_sell */

do_buy(item) {
    if (!check_shopkeeper())
	return 1;
    else {
	notify("The shopkeeper says: Sorry, but we are currently out of " + item + "s.\n");
	return 1;
    }
} /* do_buy */

do_list(item) {
    if (!check_shopkeeper())
	return 1;
    else {
	notify("The shopkeeper says: I am sorry, but I cannot give you that information.\n");
	return 1;
    }
} /* do_list */

do_value(item) {
    if (!check_shopkeeper())
	return 1;
    else {
	notify("The shopkeeper says: I am sorry, but I cannot give you that information.\n");
	return 1;
    }
} /* do_value */

do_read(str) {
    if (str == "note" || str == "small note") {
	write("The note says: 'Pssst! This way!\n");
	return 1;
    }
    else
	return 0;
} /* do_str */

notify(str) {
    write(str);
    say(str);
} /* notify */

TWO_EXIT(SHOP_PLACE, "west",
	 "players/padrone/secret_police/backroom", "north",
	 "The \"shop\"",
	 "You are in a small shop. It looks like any other shop you have been in,\n" +
	 "and you note that it is a bit strange that yet another shop in this area\n" +
	 "can show a profit... But maybe you can buy or sell things here, too?\n" +
	 "The exit is to the west, and a door leads north.\n" +
	 "There is a small note close to the north door.\n", 1)
