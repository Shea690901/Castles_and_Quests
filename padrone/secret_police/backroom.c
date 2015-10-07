/* secret_police/backroom.c */

#include "std.h"

object spm1, spm2;

#undef EXTRA_RESET
#define EXTRA_RESET extra_reset();

extra_reset() {
    object obj;

    if (!spm2) {
	spm2 = clone_object("obj/monster");
	spm2->set_name("policeman");
	spm2->set_alias("secret policeman");
	spm2->set_short("Another policeman from the Secret Police");
	spm2->set_long("This is a policeman from the Secret Police.\n" +
		       "What can he be doing in this shop?\n");
	spm2->set_level(2);
	spm2->set_al(80);
	spm2->set_male();
	spm2->set_spell_mess1("The secret policeman kicks his opponent very hard.");
	spm2->set_spell_mess2("The secret policeman kicks you very hard. You are hurt!");
	spm2->set_chance(10);
	spm2->set_spell_dam(10);

        move_object(spm2, this_object());

	obj = clone_object("players/padrone/secret_police/membership");
	move_object(obj, spm2);
	obj->set_name("policeman");

	obj = clone_object("obj/weapon");
        obj->set_name("dagger");
        obj->set_class(6);
        obj->set_value(10);
        obj->set_weight(1);
        obj->set_short("A dagger");
        move_object(obj, spm2);
	spm2->init_command("wield dagger");
    }

    if (!spm1) {
	spm1 = clone_object("obj/monster");
	spm1->set_name("policeman");
	spm1->set_alias("secret policeman");
	spm1->set_short("A policeman from the Secret Police");
	spm1->set_long("This is a policeman from the Secret Police.\n" +
		       "What can he be doing in this shop?\n");
	spm1->set_level(1);
	spm1->set_al(60);
	spm1->set_male();
	spm1->set_spell_mess1("The secret policeman kicks his opponent very hard.");
	spm1->set_spell_mess2("The secret policeman kicks you very hard. You are hurt!");
	spm1->set_chance(10);
	spm1->set_spell_dam(10);

        move_object(spm1, this_object());

	obj = clone_object("players/padrone/secret_police/membership");
	move_object(obj, spm1);
	obj->set_name("policeman");

	obj = clone_object("obj/weapon");
        obj->set_name("dagger");
        obj->set_class(6);
        obj->set_value(10);
        obj->set_weight(1);
        obj->set_short("A dagger");
        move_object(obj, spm1);
	spm1->init_command("wield dagger");
    }
} /* extra_reset */

FOUR_EXIT("players/padrone/secret_police/hall", "north",
	  "players/padrone/secret_police/shop", "south",
	  "players/padrone/secret_police/kitchen", "east",
	  "players/padrone/secret_police/store", "west",
	  "The back room behind the shop",
	  "You are in the back room behind the shop.\n" +
	  "There seems to be a kitchen to the east, and the door to the west\n" +
	  "must lead to the store room of this shop, and the shop itself is south.\n" +
	  "But where does that door to the north lead?\n", 1)
