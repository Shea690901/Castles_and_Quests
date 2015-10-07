/*  "players/padrone/walker/vault.c" -- the vault in the walking castle
 *	If DEMON is defined, this room contains a door leading in to the cell
 *	with the chaosdemon. If DEMON is not defined, there is a pirate and some
 *	money here.
 */

#include "std.h"
#include "walker.h"

#ifdef DEMON
  /* DEMON is defined */

#include "../../../obj/door.h"

object obj_1, obj_2;	/* Used by the MAKE_DOORS macro */

#undef EXTRA_RESET
#define EXTRA_RESET extra_reset(arg);

extra_reset(arg) {

    if(!arg) {
	/* First reset */

	MAKE_DOORS("players/padrone/walker/vault", "north", "players/padrone/walker/cell", "south", "panzer", "walkercell", "This is a two feet thick maximum-security bullet-proof bank-vault door.\nThere is a sign on the door, saying \"You have been warned.\".\n", 1, 1, 1)
    }

    obj_1->set_closed(1);
    obj_1->set_locked(1);
    obj_1->set_both_status();

    throw_out_players();

} /* extra_reset */

TWO_EXIT("players/padrone/walker/cell", "north",
	 "players/padrone/walker/upper_hall", "south",
	 "Vault of the walking castle",
	 "This is a steel vault that probably was intended to be the\n" +
	 "treasury of the walking castle. It is empty, however, and\n" +
	 "part of the vault has been rebuilt into some kind of cell.\n" +
	 "A steel door leads to the cell, and from inside you can hear\n" +
	 "angry, snarling noises, along with the sound of clawed feet\n" +
	 "walking on steel.\n", 1)
#else
  /* DEMON is not defined */

object pirate, money;

#undef EXTRA_RESET
#define EXTRA_RESET extra_reset(arg);

extra_reset(arg) {
    object weapon;

    if (!money) {
	money = clone_object("obj/money");
        money->set_money(2 + random(10));
        move_object(money, this_object());
    }
    if (!pirate) {
	pirate = clone_object("obj/monster");
	pirate->set_name("friendly pirate");
	pirate->set_alias("pirate");
	pirate->set_level(1);
	pirate->set_male();
	pirate->set_al(150);
	pirate->set_short("A friendly pirate");
	pirate->set_long("This is a small, friendly pirate.\n" +
			 "He looks much nicer than the other pirates you have seen,\n" +
			 "and probably the other pirates have locked him away in the vault\n" +
			 "because they couldn't stand his friendly appearance.\n");
	pirate->set_aggressive(0);
        move_object(pirate, this_object());

	weapon = clone_object("obj/weapon");
        weapon->set_name("knife");
        weapon->set_class(5);
        weapon->set_value(10);
        weapon->set_weight(1);
        weapon->set_alt_name("knife");
        weapon->set_short("A knife");
        move_object(weapon, pirate);
	pirate->init_command("wield knife");

	money = clone_object("obj/money");
        money->set_money(2 + random(20));
        move_object(money, pirate);
    }

    throw_out_players();

} /* extra_reset */

ONE_EXIT("players/padrone/walker/upper_hall", "south",
	 "Vault of the walking castle",
	 "This is a steel vault that probably was the\n" +
	 "treasury of the walking castle. Now it has been robbed by\n" +
	 "the pirates, and only a few coins are left.\n", 1)

#endif
  /* DEMON */

/* The walker-vault is teleport-safe */
realm() { return "NT"; }

throw_out_players() {
    object obj, this_obj;

    obj = first_inventory(this_object());
    while (obj) {
	this_obj = obj;
	obj = next_inventory(obj);
	if (living(this_obj) && !this_obj->query_npc()) {
	    tell_object(this_obj, "Suddenly, you have a feeling of disorientation.\n");
	    this_obj->move_player("out#players/padrone/walker/upper_hall");
	}
    } /* while */
} /* throw_out_players */
