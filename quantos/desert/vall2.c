/* #include "std.h" /Pell */

reset (arg) {
    if(!arg)
	set_light(1);
    extra_reset();
}

object cactus, treasure;

extra_reset() {
    if (!cactus || !living (cactus)) {
	cactus = clone_object ("obj/monster");
	call_other (cactus, "set_name", "cactus");
	call_other (cactus, "set_short", "A man-eating cactus");
	call_other (cactus, "set_race", "plant");
	call_other (cactus, "set_level", 8);
	call_other (cactus, "set_wc", 10);
	call_other (cactus, "set_aggressive", 1);
	call_other (cactus, "set_spell_mess1", "The cactus shoots needles!");
	call_other (cactus, "set_spell_mess2", "The cactus shoots needles at you!");
	call_other (cactus, "set_chance", 26);
	call_other (cactus, "set_spell_dam", 15);
	move_object (cactus, this_object());

	treasure = clone_object ("obj/treasure");
	call_other (treasure, "set_id", "statue");
	call_other (treasure, "set_alias", "crystal statue");
	call_other (treasure, "set_short", "A crystal statue of a scorpion");
	call_other (treasure, "set_value", 150);
	move_object (treasure, cactus);
    }
}

init() {
    add_action ("west"); add_verb ("west");
    add_action ("east"); add_verb ("east");
}

east() {
    call_other (this_player(), "move_player", "east#players/quantos/desert/vall3");
    return 1;
}

west() {
    call_other (this_player(), "move_player", "west#players/quantos/desert/vall1");
    return 1;
}

long() {
    write ("You are in the middle of a lush valley.\n");
    write ("There are desert plants all around you: cacti, yucca, and\n");
    write ("juniper bushes. Bluebottle flies zip from plant to plant in\n");
    write ("erratic lines, occasionally dodging other flies, or even you.\n");
    write ("The desert floor continues east and west.\n");
}

short() {
    return "Middle of valley";
}
