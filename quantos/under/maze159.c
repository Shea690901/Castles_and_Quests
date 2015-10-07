/* #include "std.h"  /Pell */

id(str) {return str=="fountain";} /* Pell */

reset(arg) {
    if(!arg)
	set_light(1);
}

init() {
    add_action ("north"); add_verb ("north");
    add_action ("east"); add_verb ("east");
    add_action ("south"); add_verb ("south");
    add_action ("west"); add_verb ("west");
    add_action ("northwest"); add_verb ("northwest");
    add_action ("northeast"); add_verb ("northeast");
    add_action ("southwest"); add_verb ("southwest");
    add_action ("southeast"); add_verb ("southeast");
#if 0				/* Shouldn't be necessary /Pell */
    add_action ("northwest"); add_verb ("nw");
    add_action ("northeast"); add_verb ("ne");
    add_action ("southwest"); add_verb ("sw");
    add_action ("southeast"); add_verb ("se");
#endif
    add_action ("enter"); add_verb ("enter");
}

north() {
    call_other (this_player(), "move_player", "north#players/quantos/under/maze160");
    return 1;
}

east() {
    call_other (this_player(), "move_player", "east#players/quantos/under/maze183");
    return 1;
}

south() {
    call_other (this_player(), "move_player", "south#players/quantos/under/maze158");
    return 1;
}

west() {
    call_other (this_player(), "move_player", "west#players/quantos/under/maze135");
    return 1;
}

northwest() {
    call_other (this_player(), "move_player", "northwest#players/quantos/under/maze136");
    return 1;
}

northeast() {
    call_other (this_player(), "move_player", "northeast#players/quantos/under/maze184");
    return 1;
}

southwest() {
    call_other (this_player(), "move_player", "southwest#players/quantos/under/maze134");
    return 1;
}

southeast() {
    call_other (this_player(), "move_player", "southeast#players/quantos/under/maze182");
    return 1;
}

enter(str) {
    if (str == "fountain") {
	call_other (this_player(), "move_player", "into the fountain#players/quantos/under/fountain"); /* Pell */
	return 1;
    } else {
	write ("Enter what?\n");
	return 1;
    }
}

long(str) {
    if (!str)			/* Pell */
      write ("You are in what is probably the only lit room in the labyrinth.\n");
    write ("A majestic fountain rises from the center of the floor, with\n");
    write ("statues of dolphins and cherubs spouting water into the pool\n");
    write ("which serves as its base. The depths of the pool gleam with an\n");
    write ("eerie internal green light, which casts its hue about the entire\n");
    write ("room. Around the base of the fountain, at the four corners, are\n");
    write ("gruesome faces carved from the stone.\n\n");
    if (!str)			/* Pell */
      write ("You may leave this area at any of the eight compass points.\n");
}

short() {
    return "The fountain";
}
