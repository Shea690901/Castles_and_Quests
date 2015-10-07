/* #include "std.h" /Pell */

reset(arg) {
    if (!arg) set_light(1);
/*	set_light(1); /Pell */
}

init() {
    add_action("up"); add_verb("up");
    add_action("up"); add_verb("south");
    add_action("east"); add_verb("east");
}

up() {
    call_other (this_player(), "move_player", "up#players/quantos/plateau/nwplat");
    return 1;
}

east() {
    call_other (this_player(), "move_player", "east#players/quantos/desert/vall2");
    return 1;
}

long() {
    write ("You are in a peaceful, quiet valley in the desert.\n");
    write ("The valley stretches off to the east, and the vegetation\n");
    write ("is fuller and more lush than anything you've seen around here\n");
    write ("so far. The air is very pleasant here, and the sun does not\n");
    write ("seem quite so warm. To the south, the valley floor slopes up\n");
    write ("onto a large plateau.\n");
}

short() {
    return ("A pleasant valley");
}
