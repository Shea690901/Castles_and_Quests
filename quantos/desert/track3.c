/* #include "std.h" /Pell */

reset (arg) {
    if(!arg)
	set_light(1);
}

init() {
    add_action ("up"); add_verb ("up");
    add_action ("up"); add_verb ("west");
    add_action ("east"); add_verb ("east");
    add_action ("north"); add_verb ("north");
    add_action ("south"); add_verb ("south");
}

up() {
    call_other (this_player(), "move_player", "up#players/quantos/plateau/nplat");
    return 1;
}

east() {
    call_other (this_player(), "move_player", "east#players/quantos/desert/track2");
    return 1;
}

north() {
    call_other (this_player(), "move_player", "north#players/quantos/desert/vall3");
    return 1;
}

south() {
    write ("You would not survive the fall to the bottom.\n");
    return 1;
}

long() {
    write ("You are on a track to the west of the village.\n");
    write ("The track continues to the east, and the ground slopes up to\n");
    write ("the west onto a wide plateau. You notice tiny bits of some\n");
    write ("transparent green glass embedded in the sand, some crunching\n");
    write ("under your heel. A roadrunner pauses, then speeds away at your\n");
    write ("approach. A small lizard stares at you sleepily from atop a\n");
    write ("nearby rock. To the south, you can see down into a long gulch.\n");
}

short() {
    return "Western track";
}
