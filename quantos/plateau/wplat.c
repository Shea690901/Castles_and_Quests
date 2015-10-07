/* #include "std.h" /Pell */

reset (arg) {
    if(!arg)
	set_light(1);
}

init() {
    add_action ("north"); add_verb ("north");
    add_action ("south"); add_verb ("south");
    add_action ("east"); add_verb ("east");
    add_action ("down"); add_verb ("down");
    add_action ("down"); add_verb ("west");
}

north() {
    call_other (this_player(), "move_player", "north#players/quantos/plateau/nwplat");
    return 1;
}

south() {
    call_other (this_player(), "move_player", "south#players/quantos/plateau/swplat");
    return 1;
}

east() {
    call_other (this_player(), "move_player", "east#players/quantos/plateau/plat");
    return 1;
}

down() {
    call_other (this_player(), "move_player", "down#players/quantos/plateau/cab_stop");
    return 1;
}

long() {
    write ("You are at the western edge of the plateau. There is a villa\n");
    write ("a few miles to the west, farther out into the desert. The\n");
    write ("plateau slopes down to the west to a flat circular area,\n");
    write ("where waits an imposing yellow-and-black metallic structure.\n");
    write ("The plateau continues to the north, east, and south.\n");
}

short() {
    return "West plateau";
}
