/* #include "std.h" /Pell */

reset (arg) {
    if(!arg)
	set_light(1);
    extra_reset();
}

object weed, treasure;

extra_reset() {
    if (!weed || !living (weed)) {
	weed = clone_object ("obj/monster");
	call_other (weed, "set_name", "weed");
	call_other (weed, "set_alias", "strangleweed");
	call_other (weed, "set_race", "plant");
	call_other (weed, "set_short", "A giant strangleweed plant");
	call_other (weed, "set_level", 8);
	call_other (weed, "set_wc", 10);
	call_other (weed, "set_aggressive", 1);
	call_other (weed, "set_spell_mess1", /* Pell */
		    "The plant forms itself into a noose!"); /* Pell */
	call_other(weed, "set_spell_mess2", "The plant cuts off your windpipe!"); /* Pell */
	call_other (weed, "set_chance", 40);
	call_other (weed, "set_spell_dam", 12);
	move_object (weed, this_object());

	treasure = clone_object ("obj/treasure");
	call_other (treasure, "set_id", "statue");
	call_other (treasure, "set_alias", "crystal statue");
	call_other (treasure, "set_short", "A crystal statue of a rattlesnake");
	call_other (treasure, "set_value", 150);
	move_object (treasure, weed);
    }
}

init() {
    add_action ("south"); add_verb ("south");
    add_action ("west"); add_verb ("west");
}

south() {
    call_other (this_player(), "move_player", "south#players/quantos/desert/track3");
    return 1;
}

west() {
    call_other (this_player(), "move_player", "west#players/quantos/desert/vall2");
    return 1;
}

long() {
    write ("You are at the eastern end of the valley.\n");
    write ("The vegetation is no more sparse at this end of the valley\n");
    write ("than anywhere else along its length. The valley stretches\n");
    write ("off to the west. There is a small track leading out of the\n");
    write ("valley to the south.\n");
}

short() {
    return "Eastern valley";
}
