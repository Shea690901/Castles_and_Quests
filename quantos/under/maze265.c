#include "std.h"

#undef EXTRA_RESET		/* Pell */
#define EXTRA_RESET extra_reset(); /* Pell */

object spider, fang;

extra_reset() {
    if (!spider || !living(spider)) {
	spider = clone_object("obj/monster");
	call_other (spider, "set_name", "spider");
	call_other (spider, "set_alias", "tarantula");
	call_other (spider, "set_race", "arachnid");
	call_other (spider, "set_short", "A giant tarantula");
	call_other (spider, "set_level", 12);
	call_other (spider, "set_hp", 200);
	call_other (spider, "set_wc", 20);
	call_other (spider, "set_ac", 2);
	call_other (spider, "set_move_at_reset", 1);
/*	call_other (spider, "set_can_kill", 1); */  /* Don't have this /Pell */
	call_other (spider, "set_whimpy", 1);
	call_other (spider, "set_aggressive", 1);
	call_other (spider, "set_init_ob", this_object());
	move_object (spider, this_object());

	fang = clone_object("obj/weapon");
	call_other (fang, "set_name", "fang");
	call_other (fang, "set_short", "A poisonous fang");
	call_other (fang, "set_class", 10);
	call_other (fang, "set_weight", 2);
	call_other (fang, "set_value", 1000);
	move_object (fang, spider);
    }
}

monster_init (obj) {
    if (call_other (obj, "query_name") == "scorpion") {return 0;}
    return 1;
}


ONE_EXIT ("players/quantos/under/maze264", "south",
	  "Dead-end corridor",
	  "You are at a dead end in the labyrinth.\n", 0)
