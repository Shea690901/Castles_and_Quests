/* secret_police/sleeping_room.c */

#include "std.h"

object spm;

#undef EXTRA_RESET
#define EXTRA_RESET extra_reset();

extra_reset() {
    object obj;

    if (!spm) {
	spm = clone_object("obj/monster");
	spm->set_name("policeman");
	spm->set_alias("secret policeman");
	spm->set_short("A policeman from the Secret Police");
	spm->set_long("This is a policeman from the Secret Police.\n");
	spm->set_level(1);
	spm->set_al(100);
	spm->set_male();
	spm->set_spell_mess1("The secret policeman kicks his opponent very hard.");
	spm->set_spell_mess2("The secret policeman kicks you very hard. You are hurt!");
	spm->set_chance(10);
	spm->set_spell_dam(10);

        move_object(spm, this_object());

	obj = clone_object("players/padrone/secret_police/membership");
	move_object(obj, spm);
	obj->set_name("policeman");

	obj = clone_object("obj/weapon");
        obj->set_name("dagger");
        obj->set_class(6);
        obj->set_value(10);
        obj->set_weight(1);
        obj->set_short("A dagger");
        move_object(obj, spm);
	spm->init_command("wield dagger");
    }
} /* extra_reset */

ONE_EXIT("players/padrone/secret_police/hall", "west",
	 "The Secret Police sleeping room",
	 "This is a room where the members of the Secret Police\n" +
	 "can rest and sleep.\n", 1)
