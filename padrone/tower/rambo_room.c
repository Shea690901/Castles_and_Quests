#include "std.h"
#include "../../../obj/door.h"

object rambo1, rambo2, rambo3;
object the_key;

#undef EXTRA_RESET
#define EXTRA_RESET extra_reset(arg);

#undef EXTRA_MOVE1
#define EXTRA_MOVE1   if (rambo_block()) return 1;

rambo_block()
{
    if (rambo1 && present(rambo1, this_object()))
	write("Rambo I bars the way.\n");
    if (rambo2 && present(rambo2, this_object()))
	write("Rambo II bars the way.\n");
    if (rambo3 && present(rambo3, this_object()))
	write("Rambo III bars the way.\n");

    if (   (rambo1 && present(rambo1, this_object()))
	|| (rambo2 && present(rambo2, this_object()))
	|| (rambo3 && present(rambo3, this_object())))
	return 1;
    else
	return 0;
}

extra_reset(arg) {

      throw_out_players();

      if (!rambo3) {
	  make_rambo(3);
	  MAKE_KEY(the_key, "maximum-security", "vaultdoor")
	  move_object(the_key, rambo3);

      }
      if (!rambo2)
	  make_rambo(2);
      if (!rambo1)
	  make_rambo(1);
} /* extra_init */


make_rambo(nr) {
      object rambo, weapon;
      string roman;

      if (nr == 1)
	  roman = "I";
      else if (nr == 2)
	  roman = "II";
      else if (nr == 3)
	  roman = "III";

      rambo = clone_object("obj/monster");

      if (nr == 1) {
	  rambo1 = rambo;
	  rambo->set_alias("rambo i");
      }
      else if (nr == 2) {
	  rambo2 = rambo;
	  rambo->set_alias("rambo ii");
      }
      else if (nr == 3) {
	  rambo3 = rambo;
	  rambo->set_alias("rambo iii");
	  move_object(clone_object("players/padrone/obj/immunity"), rambo);
      }

      rambo->set_name("Rambo " + roman);
      rambo->set_race("rambo");
      rambo->set_level(14 + nr);	/* 15, 16, and 17 */
      /* rambo->set_hp(200 + 50*nr); -- too hard */
      rambo->set_al(40);
      rambo->set_short("Rambo " + roman);
      rambo->set_long("This is Rambo " + roman + ".\n" +
		      "Wow! What bulging muscles!\n" +
		      "He is employed by Padrone to guard the treasury. Which he does.\n");
      rambo->set_aggressive(1);
      rambo->set_male();
      if (nr == 3)
	  weapon = clone_object("players/padrone/obj/machinegun");
      else
	  weapon = clone_object("players/padrone/obj/m16");
      weapon->set_monsters_reload_at_reset(1);
      move_object(weapon, rambo);
      if (nr == 3)
	  rambo->init_command("wield machinegun");
      else
	  rambo->init_command("wield m16");
      move_object(rambo, this_object());

      return rambo;

} /* make_rambo */


TWO_EXIT("players/padrone/tower/treasury", "north",
	 "players/padrone/tower/hall", "south",
	 "Rambo room in the treasury",
	 "This is the Castle's treasury.\n" +
	 "Over the years, many of the riches of the world have been collected here.\n" +
	 "In his youth the Wizard travelled the world and collected numerous fantastic\n" +
	 "and valuable items, and since he retired from his adventuring and settled down\n" +
	 "in this comfortable castle, consultation fees and royalties have contributed\n" +
	 "even more to his fortune.\n" +
         "The treasure is stored in the vault, north of this room.\n", 1)


throw_out_players() {
    object obj, this_obj;

    obj = first_inventory(this_object());
    while (obj) {
	this_obj = obj;
	obj = next_inventory(obj);
	if (living(this_obj) && !this_obj->query_npc()) {
	    tell_object(this_obj, "Suddenly, you have a feeling of disorientation.\n");
	    this_obj->move_player("out#players/padrone/tower/hall");
	}
    } /* while */
} /* throw_out_players */
