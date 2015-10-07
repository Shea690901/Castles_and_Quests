/* #include "std.h" /Pell */

reset (arg) {
    if(!arg)
	set_light (1);
}

init() {
    add_action ("south"); add_verb("south");
    add_action ("east"); add_verb("east");
    add_action ("west"); add_verb("west");
    add_action ("down"); add_verb("down");
    add_action ("down"); add_verb("north");
}

south() {
    call_other (this_player(), "move_player", "south#players/quantos/plateau/wplat");
    return 1;
}

east() {
    call_other (this_player(), "move_player", "east#players/quantos/plateau/nplat");
    return 1;
}

west() {
    write ("The climb is too steep, and the ground far below.\n");
    write ("You would probably break your neck in the attempt.\n");
    return 1;
}

down() {
    call_other (this_player(), "move_player", "down#players/quantos/desert/vall1");
    return 1;
}

long() {
    write ("You are standing on the northwest part of the plateau.\n");
    write ("To the far northwest, you can see the characteristic glow of a\n");
    write ("large desert city in the evening sun. It looks much too far to\n");
    write ("walk...perhaps there is some other mode of transport nearby?\n\n");
    write ("The plateau slopes down and to the north into a wide, sweeping\n");
    write ("valley that would lead you eventually to the village to your\n");
    write ("east. You could also go further onto the plateau, to the east\n");
    write ("or south of your present location, but the light desert breeze\n");
    write ("and the pleasant evening sun prompt you to relax a while.\n");
}

short() {
    return "Northwest plateau";
}
