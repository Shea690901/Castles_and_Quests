/* #include "std.h" /Pell */

reset (arg) {
    if(!arg)
	set_light(1);
}

init() {
    add_action ("north"); add_verb ("north");
    add_action ("south"); add_verb ("south");
    add_action ("east"); add_verb ("east");
    add_action ("west"); add_verb ("west");
}

north() {
    call_other (this_player(), "move_player", "north#players/quantos/plateau/wplat");
    return 1;
}

south() {
    write ("As you step to the south, you feel the ground give way beneath your feet!\n");
    write ("You hit the ground hard!\n");
    call_other (this_player(), "reduce_hit_point", random(10));	/* Pell */
    call_other (this_player(), "move_player", "south#players/quantos/under/sinkhole");
    return 1;
}

east() {
    call_other (this_player(), "move_player", "east#players/quantos/plateau/splat");
    return 1;
}

west() {
    write ("The climb is too steep, and you would not survive the fall.\n");
    return 1;
}

long() {
    write ("You are at the western edge of the plateau. A few miles away,\n");
    write ("to the northwest, you can see a large building, like a hotel.\n");
    write ("At the base of the plateau, down and to the north, is some\n");
    write ("kind of small metal structure, which is colored yellow and\n");
    write ("black.\n\n");
    write ("The plateau continues to the north, east, and south.\n");
}

short() {
    return "Southwest plateau";
}
