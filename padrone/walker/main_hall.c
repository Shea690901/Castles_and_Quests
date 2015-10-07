#include "std.h"

#undef EXTRA_RESET
#define EXTRA_RESET extra_reset(arg);

object pirate, cutlass, money;

extra_reset(arg) {
    if (!pirate) {
	pirate = clone_object("obj/monster");
	pirate->set_name("evil pirate");
	pirate->set_alias("pirate");
	pirate->set_level(3);
	pirate->set_male();
	pirate->set_al(-200);
	pirate->set_short("An evil pirate");
	pirate->set_long("This is an evil-looking pirate.\n");
	pirate->set_aggressive(1);
        move_object(pirate, this_object());

	cutlass = clone_object("obj/weapon");
        cutlass->set_name("rusty cutlass");
        cutlass->set_class(7);
        cutlass->set_value(10);
        cutlass->set_weight(3);
        cutlass->set_alt_name("cutlass");
        cutlass->set_short("A rusty cutlass");
        cutlass->set_long("This used to be a fine weapon, but the pirate who owned it let it rust.\n");
        move_object(cutlass, pirate);
	pirate->init_command("wield cutlass");

	money = clone_object("obj/money");
	money->set_money(20 + random(30));
        move_object(money, pirate);
    }
} /* extra_init */

FOUR_EXIT("players/padrone/walker/ladder_room", "north",
	  "players/padrone/walker/castle_yard", "south",
	  "players/padrone/walker/upper_hall", "up",
	  "players/padrone/walker/banquet_hall", "east",
	  "Main hall of the walking castle",
	  "You are in the main hall of the walking castle.\n" +
	  "This used to be a luxurious and impressingly decorated place,\n" +
	  "but since a band of pirates took over this castle\n" +
	  "the expensive furniture has been broken, the thick carpets\n" +
	  "have been stained with blood, and the antique chandeliers\n" +
	  "have been smashed to pieces.\n", 1)
