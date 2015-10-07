#include "std.h"

object moses;

#undef EXTRA_RESET
#define EXTRA_RESET  extra_reset(arg);

extra_reset(arg) {
    object paper;

    if (!moses || !living(moses)) {
	moses = clone_object("obj/monster");
	moses->set_name("Moses Schoenfinkel");
	moses->set_alias("moses");
	moses->set_race("schoenfinkel");
	moses->set_level(7);
	moses->set_hp(200);
	moses->set_al(600);
	moses->set_short("Moses Schoenfinkel, the father of combinatory logic");
	moses->set_long("This is Moses Schoenfinkel.\n" +
			"In 1920 he invented combinatory logic. Combinatory logic is a way\n" +
			"of doing logic or computations without using variables. For first-\n" +
			"order logic this is just a curiosity, but for higher orders it is\n" +
			"a technique with considerable advantages.\n");
	moses->set_aggressive(0);
	moses->set_spell_mess1("Moses Shoenfinkel forces a combinator down the throat of his opponent.");
	moses->set_spell_mess2("Moses Shoenfinkel forces a combinator down your throat.");
	moses->set_chance(20);
	moses->set_spell_dam(20);
	move_object(moses, this_object());

	paper = clone_object("players/padrone/obj/thing");
	paper->set_name("article");
	paper->set_alias("paper");
	paper->set_short("An article from a scientific journal");
	paper->set_long("This is a paper called \"Ueber die Bausteine der mathematischen Logik\",\n" +
			"published 1924 in \"Mathematische Annalen\" 92, pages 305-31.\n");
	paper->set_can_get(1);
	paper->set_weight(1);
	paper->set_value(40);
	paper->set_read("You are totally confused.\n" +
			"Not only is this paper written in German,\n" +
			"it is also filled with strange symbols!\n" +
			"What mysterious magic can this be?\n");
	move_object(paper, moses);
    }
} /* extra_reset */

TWO_EXIT("players/padrone/maze/moses_garden", "south",
	 "players/padrone/maze/moses_wardrobe", "east",
	 "Moses Schoenfinkel's office",
	 "You are in the office of Moses Schoenfinkel,\n" +
	 "a small room filled with books and papers.\n" +
	 "There is a small wardrobe to the east,\n" +
	 "and to the south a door leads out into a garden.\n", 1)
