#include "std.h"

init() {
    add_action ("out"); add_verb ("out");
    add_action ("north"); add_verb ("north");
    add_action ("east"); add_verb ("east");
}

out() {
    call_other (this_player(), "move_player", "out#players/quantos/desert/oasis");
    return 1;
}

north() {
    call_other (this_player(), "move_player", "north#players/quantos/under/maze1");
    return 1;
}

east() {
    call_other (this_player(), "move_player", "east#players/quantos/under/maze24");
    return 1;
}

long() {
    write ("You are standing at the junction of a corridor.\n");
    write ("Looking up, you see sand trickling down from a hole in the ceiling.\n");
    write ("There are two obvious exits, north and east.\n");
    write("If you want to exit the maze without searching for one of the\n");
    write("exits, type 'out' now, and you will be transported to the oasis.\n");
    write("This feature will most assuredly disappear in the near future.\n");
}

short() {
    return "Sinkhole";
}
