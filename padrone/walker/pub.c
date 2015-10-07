#include "std.h"
#include "walker.h"

#undef EXTRA_RESET
#define EXTRA_RESET extra_reset(arg);

#undef EXTRA_LONG
#define EXTRA_LONG if (extra_long(str)) return;

#undef EXTRA_INIT
#define EXTRA_INIT add_action("read", "read");

object pirate1, pirate2, pirate3, pirate4, pirate5;
object weapon, helmet, money;

/* For the NEW, IMPROVED monster class: */
string chat_str1, chat_str2, chat_str3, chat_str4, chat_str5;

extra_reset(arg) {

    if (!chat_str1)
	setup_arrays();

    if (!pirate5) {
	pirate5 = clone_object("obj/monster");	/* NEW, IMPROVED monster class! */
	pirate5->set_name("completely drunk pirate");
	pirate5->set_alias("pirate");
	pirate5->set_level(7);
	pirate5->set_male();
	pirate5->set_al(-100);
	pirate5->set_short("A completely drunk pirate");
	pirate5->set_long("He is completely drunk.\n");
	pirate5->set_aggressive(0);
        move_object(pirate5, this_object());

	/* The NEW, IMPROVED monster calls: */
	pirate5->load_chat(5, chat_str5);

	weapon = clone_object("obj/weapon");
        weapon->set_name("cutlass");
        weapon->set_class(10);
        weapon->set_value(50);
        weapon->set_weight(3);
        weapon->set_short("A cutlass");
        move_object(weapon, pirate5);
	pirate5->init_command("wield cutlass");

	money = clone_object("obj/money");
        money->set_money(100 + random(100));
        move_object(money, pirate5);
    }

    if (!pirate4) {
	pirate4 = clone_object("obj/monster");	/* NEW, IMPROVED monster class! */
	pirate4->set_name("very drunk pirate indeed");
	pirate4->set_alias("pirate");
	pirate4->set_level(6);
	pirate4->set_male();
	pirate4->set_al(-100);
	pirate4->set_short("A very drunk pirate indeed");
	pirate4->set_long("He is very drunk indeed.\n");
	pirate4->set_aggressive(0);
        move_object(pirate4, this_object());

	/* The NEW, IMPROVED monster calls: */
	pirate4->load_chat(5, chat_str4);

	weapon = clone_object("obj/weapon");
        weapon->set_name("knife");
        weapon->set_class(5);
        weapon->set_value(10);
        weapon->set_weight(1);
        weapon->set_alt_name("knife");
        weapon->set_short("A knife");
        move_object(weapon, pirate4);
	pirate4->init_command("wield knife");

        helmet = clone_object("obj/" + ARMOUR);
        helmet->set_name("metal helmet");
        helmet->set_ac(1);
        helmet->set_weight(3);
        helmet->set_value(75);
        helmet->set_alias("helmet");
        helmet->set_type("helmet");
        helmet->set_short("A metal helmet");
        helmet->set_long("A metal helmet\n");
        move_object(helmet, pirate4);
	pirate4->init_command("wear helmet");

	money = clone_object("obj/money");
        money->set_money(2 + random(10));
        move_object(money, pirate4);
    }

    if (!pirate3) {
	pirate3 = clone_object("obj/monster");	/* NEW, IMPROVED monster class! */
	pirate3->set_name("very drunk pirate");
	pirate3->set_alias("pirate");
	pirate3->set_level(5);
	pirate3->set_female();
	pirate3->set_al(-100);
	pirate3->set_short("A very drunk pirate");
	pirate3->set_long("She is very drunk.\n");
	pirate3->set_aggressive(0);
        move_object(pirate3, this_object());

	/* The NEW, IMPROVED monster calls: */
	pirate3->load_chat(5, chat_str3);

	weapon = clone_object("obj/weapon");
        weapon->set_name("curved knife");
        weapon->set_class(7);
        weapon->set_value(15);
        weapon->set_weight(1);
        weapon->set_alt_name("knife");
        weapon->set_short("A curved knife");
        move_object(weapon, pirate3);
	pirate3->init_command("wield knife");

	money = clone_object("obj/money");
        money->set_money(2 + random(10));
        move_object(money, pirate3);
    }

    if (!pirate2) {
	pirate2 = clone_object("obj/monster");	/* NEW, IMPROVED monster class! */
	pirate2->set_name("more drunk pirate");
	pirate2->set_alias("pirate");
	pirate2->set_level(4);
	pirate2->set_male();
	pirate2->set_al(-100);
	pirate2->set_short("A more drunk pirate");
	pirate2->set_long("He is more drunk.\n");
	pirate2->set_aggressive(0);
        move_object(pirate2, this_object());

	/* The NEW, IMPROVED monster calls: */
	pirate2->load_chat(5, chat_str2);

	weapon = clone_object("obj/weapon");
        weapon->set_name("hand axe");
        weapon->set_class(9);
        weapon->set_value(25);
        weapon->set_weight(2);
        weapon->set_alt_name("axe");
        weapon->set_short("A hand axe");
        move_object(weapon, pirate2);
	pirate2->init_command("wield axe");

	money = clone_object("obj/money");
        money->set_money(2 + random(10));
        move_object(money, pirate2);
    }

    if (!pirate1) {
	pirate1 = clone_object("obj/monster");	/* NEW, IMPROVED monster class! */
	pirate1->set_name("moderately drunk pirate");
	pirate1->set_alias("pirate");
	pirate1->set_level(4);
	pirate1->set_female();
	pirate1->set_al(-100);
	pirate1->set_short("A moderately drunk pirate");
	pirate1->set_long("She is moderately drunk.\n");
	pirate1->set_aggressive(0);
        move_object(pirate1, this_object());

	/* The NEW, IMPROVED monster calls: */
	pirate1->load_chat(5, chat_str1);

	weapon = clone_object("obj/weapon");
        weapon->set_name("knife");
        weapon->set_class(5);
        weapon->set_value(10);
        weapon->set_weight(1);
        weapon->set_alt_name("knife");
        weapon->set_short("A knife");
        move_object(weapon, pirate1);
	pirate1->init_command("wield knife");

        helmet = clone_object("obj/" + ARMOUR);
        helmet->set_name("metal helmet");
        helmet->set_ac(1);
        helmet->set_weight(3);
        helmet->set_value(75);
        helmet->set_alias("helmet");
        helmet->set_type("helmet");
        helmet->set_short("A metal helmet");
        helmet->set_long("A metal helmet\n");
        move_object(helmet, pirate1);
	pirate1->init_command("wear helmet");

	money = clone_object("obj/money");
        money->set_money(2 + random(10));
        move_object(money, pirate1);
    }

} /* extra_reset */

id(str) {
    return !str || comments_id(str);
}

comments_id(str) {
    return    str == "comments" || str == "rude comments" || str == "writing"
	   || str == "text" || str == "walls";
}

extra_long(str) {
    if (comments_id(str)) {
	return read(str);
    }
    else
	return 0;
} /* extra_long */

read(str) {
    if (comments_id(str)) {
	write("Your cheeks are burning.\n");
        return 1;
    }
    else
	return 0;
} /* read */

ONE_EXIT("players/padrone/walker/castle_yard", "west",
	 "The pub of the walking castle",
	 "You are in what used to be the pub of the walking castle.\n" +
	 "This was once a nice and cosy place, where you could take a beer\n" +
	 "or a cup of coffee and chat with your friends.\n" +
	 "Now the pirates have drunk absolutely everything drinkable,\n" +
	 "broken the empty bottles, and written rude comments on the walls.\n", 1)


/* For the NEW, IMPROVED monster class: */
setup_arrays() {
    chat_str1 = ({ "The moderately drunk pirate sings: And a bottle of rum!\n" });
    chat_str2 = ({ "The more drunk pirate sings: And a bott-(hick)-bottle of rum!\n" });
    chat_str3 = ({ "The very drunk pirate sings: And a chest of rum! Yeah!\n" });
    chat_str4 = ({ "The very drunk pirate indeed sings: Andsch a rum of bottle chest! La-la-la!\n" });
    chat_str5 = ({ "The completely drunk pirate tries to sing but falls down and pukes.\n" });
} /* setup_arrays */
