#include "std.h"

object rat1, rat2, anticimex;

#undef EXTRA_RESET
#define EXTRA_RESET extra_reset();

extra_reset() {
    object bottle;

    if (!rat1 || !living(rat1)) {
	rat1 = clone_object("obj/monster");
	rat1->set_name("brown rat");
	rat1->set_alias("rat");
	rat1->set_level(1);
	rat1->set_hp(40);
	rat1->set_wc(5);
	rat1->set_al(-10);
	rat1->set_short("A big, brown rat");
	rat1->set_long("This is an ugly, dirty, smelling rat with a long, naked tail.\n" +
		       "It stares at you with angry red eyes and looks very aggressive.\n");
	rat1->set_aggressive(1);
	move_object(rat1, this_object());
    }

    if (!rat2 || !living(rat2)) {
	rat2 = clone_object("obj/monster");
	rat2->set_name("black rat");
	rat2->set_alias("rat");
	rat2->set_level(1);
	rat2->set_hp(40);
	rat2->set_wc(5);
	rat2->set_al(-12);
	rat2->set_short("A big, black rat");
	rat2->set_long("This rat looks really repulsing with its thick, balack, dirty hair\n" +
		       "and its small, clawed feet. It stares angrily at you and squeeks.\n");
	rat2->set_aggressive(1);
	move_object(rat2, this_object());
    }

    if (!anticimex || !living(anticimex)) {
	anticimex = clone_object("obj/monster");
	anticimex->set_name("vermin exterminator");
	anticimex->set_alias("exterminator");
	anticimex->set_level(2);
	anticimex->set_male();
	anticimex->set_wc(5);
	anticimex->set_al(10);
	anticimex->set_short("A vermin exterminator from Anticimex");
	anticimex->set_long("This is an old man in blue coveralls marked 'Anticimex'.\n" +
			    "He is here to kill the rats that have infested the cellar.\n");
	move_object(anticimex, this_object());

	bottle = clone_object("obj/drink");
	bottle->set_value("black bottle#A largish black bottle with some kind of liquid inside#Yuk! Rat poison! You feel horrible#-5#50#1");
	move_object(bottle, anticimex);
    }
} /* extra_reset */


ONE_EXIT("players/padrone/inside/dark_pass1", "east",
	 "Food cellar",
	 "This is a big room in the cellar that is used for storing food.\n", 0)
