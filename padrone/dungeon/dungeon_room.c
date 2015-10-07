/* dungeon_room.c -- a dungeon room */

object dungeon;
int x, y, z;
object exits;
status can_make_monsters;

reset(arg) {
    if (!arg) {
	set_light(1);
	exits = allocate(10);
    }
    can_make_monsters = 1;
} /* reset */

reset2() {
    move_object(this_object(), "players/padrone/dungeon/dungeon");
    dungeon = environment(this_object());
} /* reset2 */

init() {
    add_action("up", "up");
    add_action("down", "down");
    add_action("north", "north");
    add_action("south", "south");
    add_action("east", "east");
    add_action("west", "west");
    add_action("northwest", "northwest");
    add_action("northeast", "northeast");
    add_action("southwest", "southwest");
    add_action("southeast", "southeast");
    add_action("dig", "dig");
    add_action("roomstat", "roomstat");
    if (can_make_monsters) {
	can_make_monsters = 0;
	while (!random(4))
	    move_object(dungeon->make_monster(-z), this_object());
    }
} /* init */

set_coordinates(x1, y1, z1) { x = x1; y = y1; z = z1; }
match_xyz(x1, y1, z1) { return x == x1 && y == y1 && z == z1; }
query_exits() { return exits; }

up() { return do_move("up", 0); }
down() { return do_move("down", 1); }
north() { return do_move("north", 2); }
south() { return do_move("south", 3); }
east() { return do_move("east", 4); }
west() { return do_move("west", 5); }
northwest() { return do_move("northwest", 6); }
northeast() { return do_move("northeast", 7); }
southwest() { return do_move("southwest", 8); }
southeast() { return do_move("southeast", 9); }

dig(str) {
    int dir_nr, x1, y1, z1;
    object other_room;

    if (!str) {
	write("Yes, but in what direction do you want to dig?\n");
	return 1;
    }
    dir_nr = dungeon->dir_to_nr(str);
    if (dir_nr == -1) {
	write("What a strange direction!\n");
	return 1;
    }
    if (exits[dir_nr]) {
	write("But there is already an opening leading " + str + "!\n");
	return 1;
    }
    x1 = x + dungeon->query_delta_x(dir_nr);
    y1 = y + dungeon->query_delta_y(dir_nr);
    z1 = z + dungeon->query_delta_z(dir_nr);
    if (z1 > 0) {
	write("In this room, the ceiling is too hard to dig through.\n");
	return 1;
    }
    str = (dungeon->query_directions())[dir_nr];
    write("You dig a hole leading " + str + ".\n");
    say(this_player()->query_name() + " digs a hole leading " + str + ".\n");
    other_room = dungeon->find_dungeon_room(x1, y1, z1);
    if (!other_room) {
	other_room = clone_object("players/padrone/dungeon/dungeon_room");
	other_room->reset2();
	other_room->set_coordinates(x1, y1, z1);
    }
    other_room->set_exit(dungeon->query_opposite(dir_nr), this_object());
    set_exit(dir_nr, other_room);
    return 1;
} /* dig */

set_exit(dir_nr, room) {
    if (exits[dir_nr])
	write("WARNING! This exit was already used in the other room.\n");
    exits[dir_nr] = room;
}

roomstat() {
    int i;

    if (this_player()->query_level() < 20)
	return 0;

    write("Room coordinates: (x, y, x) = (" + x + ", " + y + ", " + z + ")\n");
    i = 0;
    while (i < 10) {
	write("  Exit " + i + ": ");
	write(exits[i]);
	write("\n");
	i += 1;
    }
    return 1;
} /* roomstat */

do_move(dirstring, nr) {
    if (!exits[nr])
	return 0;
    this_player()->move_player(dirstring, exits[nr]);
    return 1;
} /* do_move */

short() {
    return "A dungeon room";
}

long(str) {
    int i;
    object the_array;
    status notfirst;

    if (set_light(0) == 0) {
	write("It is dark.\n");
	return;
    }
    write("This is a room in the dungeon below the Castle of Padrone.\n" +
	  "The walls, as well as the floor and the ceiling, look\n" +
	  "very soft, and you could probably dig in any direction.\n" +
          "Some exits have already been dug, leading\n    ");

    the_array = dungeon->query_directions();
    notfirst = 0;
    i = 0;
    while (i < 10) {
	if (exits[i]) {
	    if (notfirst)
		write(", ");
	    write(the_array[i]);
	    notfirst = 1;
	}
	i += 1;
    }
    write(".\n");
} /* long */
