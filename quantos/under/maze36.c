#include "std.h"

#undef EXTRA_RESET
#define EXTRA_RESET \
    extra_reset();

object bamf, weapon;		/* Pell */

extra_reset() {
    object treasure;
    if (!bamf || !living (bamf)) {
/* This monster is just a bit too much, I think. I lowered some stats a little /Pell */
	bamf = clone_object ("obj/monster");
	call_other (bamf, "set_name", "juggernaut");
	call_other (bamf, "set_alias", "statue");
	call_other (bamf, "set_race", "construct");
	call_other (bamf, "set_short", "A stone juggernaut");
	call_other (bamf, "set_long",
		"A stone juggernaut, rolling towards you on huge wheels!\n");
	call_other (bamf, "set_level", 22);
	call_other (bamf, "set_hp", 1000); /* Was 2500 */
	call_other (bamf, "set_ep", 1000000); /* Was 3000000 */
	call_other (bamf, "set_wc", 36);
	call_other (bamf, "set_ac", 12);
	call_other (bamf, "set_al", -750);
	call_other (bamf, "set_aggressive", 1);
	call_other (bamf, "set_spell_mess2", "The juggernaut crushes you under its wheels!");
	call_other (bamf, "set_chance", 30);
	call_other (bamf, "set_spell_dam", 26);
	move_object (bamf, this_object());

	weapon = clone_object ("obj/weapon");
	call_other (weapon, "set_name", "rod of smiting");
	call_other (weapon, "set_class", 12);
	call_other (weapon, "set_weight", 3);
	call_other (weapon, "set_value", 7500);
	call_other (weapon, "set_alias", "rod");
	call_other (weapon, "set_short", "A heavy metal rod");
	call_other (weapon, "set_long",
		"A solid metal rod with a large ball on one end.\n" +
		"A faint inscription can be seen around the base of the ball.\n");
	call_other (weapon, "set_read",
		"The inscription says: 'Strength will come to those in need.'\n-Pell");
	call_other (weapon, "set_hit_func", this_object());

	treasure = clone_object ("obj/treasure");
	call_other (treasure, "set_id", "idol");
	call_other (treasure, "set_short", "A golden idol");
	call_other (treasure, "set_long", "An idol to some long-forgotten deity.\n");
	call_other (treasure, "set_value", 2500);
	call_other (treasure, "set_weight", 2);

	move_object (weapon, bamf);
	move_object (treasure, bamf);
      }				/* Pell */
}

ONE_EXIT ("players/quantos/under/maze35", "south",
	  "A dead-end in the maze",
	  "You are at a dead end in the labyrinth. The grooves in the stone\n" +
	  "seem more pronounced here. What to the south had been powdered\n" +
	  "bone now appears to have become an integral part of the stone.\n", 0)

/* This is almost too good. If you are in a very bad shape, the weapon class
   will be 25, on the average. If you are badly hurt, the class will be 19.
   Well, I think I'll let it pass. It is very expensive, after all. /Pell */

/* Pell: Changed "weapon" to "attacker" and other fixes. */
weapon_hit (attacker) {
    int minhp, maxhp, dam;
    if (!environment(weapon)) return 0;	/* Pell */
    maxhp = 50 + 8 * (call_other (environment(weapon), "query_level") - 1);
    minhp = call_other (environment(weapon), "query_hp");
    if (minhp < maxhp / 3) {
	if (minhp < maxhp / 6) {
	    write ("Your bravery channels tremendous power through the rod!\n");
	    dam = 9 + random(10);
	    return dam;
	}
	write ("You feel an abrupt surge of strength channel through you!\n");
	dam = 6 + random(4);
	return dam;
    }
    return 0;
}
