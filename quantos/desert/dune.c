/* #include "std.h" /Pell */

reset (arg) {
    if(!arg)
	set_light (1);
}

init() {
    add_action ("north"); add_verb ("north");
    add_action ("west"); add_verb ("west");
    add_action ("east"); add_verb ("east");
}

north() {
    write ("The dune is too steep for you to climb.\n");
    return 1;
}

west() {
    call_other (this_player(), "move_player", "west#players/quantos/desert/gulch1");
    return 1;
}

east() {
    call_other (this_player(), "move_player", "east#players/quantos/desert/desert2");
    return 1;
}

long() {
    write ("You have entered a group of sand dunes.\n");
    write ("You can see the forest to the south, although it is very dense.\n");
    write ("There are two obvious exits, east and west.\n");
}

short() {
    return "Sand dune";
}
