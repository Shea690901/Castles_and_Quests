/* exit_object.c -- the exit from the mirrormaze, through a magic mirror! */

string dest_room, direction;
object mirror;

short() {
    return 0;
}

long() {
    write("This is an exit from the mirrormaze. Just go " + direction + ".\n");
}

reset(arg) { }

init() {
    add_action("do_exit", direction);
}

id(str) {
    return str == "exit";
}

get() {
    return 0;
}

query_name() { return "exit"; }
query_value() { return 0; }

setup(m, r, d) {
    mirror = m;
    dest_room = r;
    direction = d;
}

do_exit() {
    if (!mirror || mirror->query_broken())
	return 0;
    write("You step out from a magic mirror.\n");
    this_player()->move_player(direction + "#" + dest_room);
    return 1;
}
