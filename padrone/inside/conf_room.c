/* conf_room.c -- the Conference Room */

status is_closed;

id (str) {
    return str && str == "door";
}

open(str) {
    if (!str || str != "door")
	return 0;
    if (!is_closed) {
	write("The door is already open.\n");
	return 1;
    }
    write("You open the door. Anybody can enter or leave now.\n");
    say(this_player()->query_name() +
	" opened the door. Anybody can enter or leave now.\n");
    is_closed = 0;
    return 1;
} /* open */

close(str) {
    if (!str || str != "door")
	return 0;
    if (is_closed) {
	write("The door is already closed.\n");
	return 1;
    }
    write("You close the door. Nobody can enter or leave now.\n");
    say(this_player()->query_name() +
	" closed the door. Nobody can enter or leave now.\n");
    is_closed = 1;
    write("As the door closes, the room automatically checks if any invisible\n" +
	  "players, monsters or items are present in the room.\n");
    say("As the door closes, the room automatically checks if any invisible\n" +
	"players, monsters or items are present in the room.\n");
    check_for_invisible();
    return 1;
} /* close */

check(str) {
    if (str)
	return 0;
    write("Checking if any invisible\n" +
	  "players, monsters or items are present in the room.\n");
    say("Checking if any invisible\n" +
	"players, monsters or items are present in the room.\n");
    check_for_invisible();
    return 1;
} /* check */

reset(arg) { 
    if (!arg) {
	set_light( 1); 
	is_closed = 0;
    }
} /* reset */

short() { 
    if (set_light(0))
	return "Padrone's Conference Room";
    else
	return "dark room";
}

init() { 
    if (is_closed && call_other(this_player(), "query_name") != "Padrone") {
	write("Sorry, the conference room is occupied.\n");
	write("You'll have to wait outside.\n");
	tell_room(this_object(), call_other(this_player(), "query_name") +
		  " tried to magically enter the\n" +
		  "conference room, but failed (haha!).\n");
	this_player()->move_player("back out again#players/padrone/inside/e_uhall");
    }
    else {
	write("Welcome to Padrone's Conference Room!\n");
	add_action("open", "open");
	add_action("close", "close");
	add_action("check", "check");
	add_action("west",  "west");
    }
} /* init */

west() {
    if (is_closed) {
	write("The door is closed. You must open it before leaving.\n");
	return 1;
    }
    write("Goodbye. Thank you for visiting Padrone's Conference Room.\n");
    this_player()->move_player("west#players/padrone/inside/e_uhall");
    return 1;
} /* west */

print_door() {
    write("The door is ");
    if (is_closed)
	write("closed.\n");
    else
	write("open.\n");
} /* print_door */

long(str) { 
    if (set_light(0) == 0) {
	write("It is dark.\n");
	return;
    } 
    if (str && str == "door") {
	print_door();
	return;
    }
    write("This is Padrone's Conference Room, a spacious and luxuriously furnished\n" +
	  "room with a big table and some audio and video equipment.\n" +
	  "When the door is closed, nobody, not even a wizard (except for Padrone)\n" +
	  "can enter this room. This includes teleporting.\n");
    write("There is a door leading west.\n");
    print_door();
} /* long */

query_closed() {
	return is_closed;
}

check_for_invisible() {
	object an_obj;
	string namestring, shortstring;
	int nr;

	an_obj = first_inventory(this_object());
	nr = 0;
	while (an_obj) {
		shortstring = an_obj->short();
		if (!shortstring) {

			nr += 1;
			write("\n");
			write("WARNING! Invisible object found:\n");
			namestring = an_obj->query_name();
			if (!namestring)
				namestring = "NO NAME";
			write("Name: " + namestring + "\n");
			write("Long description:\n");
			an_obj->long();
			write("\n");
		}
		an_obj = next_inventory(an_obj);
	}
	write("There are " + nr + " invisible objects in this room.\n");
	say("There are " + nr + " invisible objects in this room.\n");
} /* check_for_invisible */
