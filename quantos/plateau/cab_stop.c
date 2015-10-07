#include "std.h"

reset (arg) {
    if(!arg)
	set_light(1);
}

init() {
    add_action ("east"); add_verb ("east");
    add_action ("east"); add_verb ("up");
/*    add_action ("enter"); add_verb ("enter"); /Pell, not finished */
}

east() {
    call_other (this_player(), "move_player", "east#players/quantos/plateau/wplat");
    return 1;
}

enter() {
    call_other (this_player(), "move_player", "enter#players/quantos/plateau/cab"); /* Fix by Pell (added plateau) */
    return 1;
}

long() {
    write ("You are standing on a large circular area made out of some flat\n");
    write ("textured black rock you don't quite recognize. The flat rock\n");
    write ("is quite warm to the touch, and smells horribly in comparison\n");
    write ("to the rest of the desert. Sitting on this surface is a yellow\n");
    write ("and black metallic structure, which, because of its four\n");
    write ("wheels, you recognize as a means of conveyance. However, it's\n");
    write ("got a strange ghostly aura about it which you take to mean\n");
    write ("that this part of the realm is not complete yet.\n\n");
    write ("You can see the villa to the west even more clearly now,\n");
    write ("despite the great distance between you and it. To the east,\n");
    write ("the ground slopes up onto a wide plateau.\n");
}

short() {
    return "A circular driveway";
}

cab_arrives()			/* Pell */
{
  say("A cab arrives and stops to a screeching halt.\n");
}
