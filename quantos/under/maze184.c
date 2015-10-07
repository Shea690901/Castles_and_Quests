#include "std.h"

#undef EXTRA_RESET
#define EXTRA_RESET \
    extra_reset();

object rakshasa, scroll;

extra_reset() {
    if (!rakshasa || !living(rakshasa)) {
	rakshasa = clone_object ("obj/monster");
	call_other (rakshasa, "set_name", "rakshasa");
	call_other (rakshasa, "set_race", "demon");
	call_other (rakshasa, "set_short", "An evil rakshasa");
	call_other (rakshasa, "set_long",
		"A fearsome rakshasa, one of the tiger-demons of India.\n");
	call_other (rakshasa, "set_level", 18);
	call_other (rakshasa, "set_ep", 400000); /* Was 1125000 Pell */
	call_other (rakshasa, "set_hp", 400); /* Was 600 */
	call_other (rakshasa, "set_ac", 7); /* Was 8 */
	call_other (rakshasa, "set_wc", 20); /* Was 25 */
	call_other (rakshasa, "set_al", -1000);
	call_other (rakshasa, "set_aggressive", 1);
	call_other (rakshasa, "set_spell_mess1", /* Pell */
		"The demon screams for your soul, chilling your body."); /* Pell */
	call_other (rakshasa, "set_spell_mess2",
		"The demon sucks out part of your soul, chilling your body.");
	call_other (rakshasa, "set_chance", 2);
	call_other (rakshasa, "set_spell_dam", 60); /* Was 80 */
	move_object (rakshasa, this_object());

	scroll = clone_object ("obj/money");
	call_other (scroll, "set_money", 1000 + random(1000));
	move_object (scroll, rakshasa);
    }
}
TWO_EXIT ("players/quantos/under/maze183", "south",
	  "players/quantos/under/maze160", "west",
	  "In the labyrinth",
	  "You are in the labyrinth under the plateau.\n", 0)
