/*
 *   A magic mirror leading to the mirrormaze.
 *   Thomas Padron-McCarthy, padrone@lysator.liu.se, 1990, 1991
 *	Clone this object and call setup(dest_room, maze_room, direction).
 *	The mirror will move itself to the right room,
 *	and the mirrormaze will be correspondingly updated.
 *   "Direction" is the direction to go when exiting from the maze.
 */

string dest_room, maze_room, direction;
object exit_object;
int broken;

short() {
    return "An old mirror is standing here";
}

long() {
    write("A large old mirror with a thick, gilded frame.\n" +
	  "You wouldn't be surprised if this is a magic mirror.\n");
    if (broken) {
	write("Unfortunately someone has broken the glass.\n");
    }
}

reset(arg) {
    broken = 0;
}

init() {
    add_action("enter", "enter");
    add_action("smash", "smash");
    add_action("smash", "break");
}

id(str) {
    return str == "mirror" || str == "old mirror";
}

get() {
    write("The mirror is too heavy. You cannot move it.\n");
    return 0;
}

query_name() { return "mirror"; }
query_value() { return 0; }
query_broken() { return broken; }

setup(dr, mr, dir) {
    dest_room = dr;
    maze_room = mr;
    direction = dir;

    exit_object = clone_object("players/padrone/maze/exit_object");
    exit_object->setup(this_object(), dest_room, direction);
    move_object(this_object(), dest_room);
    move_object(exit_object, maze_room);
} /* setup */

enter(str) {
    if (!id(str))
	return 0;
    if (broken) {
	write("The mirror is broken.\n");
	return 1;
    }
    write("You step into the mirror.\n");
    call_other(this_player(), "move_player",
	       "into the mirror#" + maze_room);
    return 1;
}

smash(str) {
    if (!id(str))
	return 0;
    if (broken) {
	write("It is already broken.\n");
	return 1;
    }
    broken = 1;
    write("You break the mirror. A stupid move, but now it's done.\n");
    say(call_other(this_player(), "query_name") + " broke the mirror.\n");
    return 1;
}
