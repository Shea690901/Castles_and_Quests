/* front_yard.c -- Padrone's front yard */

object the_guard;
int ticket_number;
status guard_can_come;
string function, type, match;

reset(arg) {
    object this_ticket, nothing;
    status found;
    
    if (!arg) {
	set_light(1);
	ticket_number = 0;
	guard_can_come = 1;
    }

    nothing = clone_object("obj/treasure");
    move_object(nothing, "room/vill_road1");
    if (!present("ticket", environment(nothing))) {
	this_ticket = make_ticket();
	move_object(this_ticket, "room/vill_road1");
    }
    destruct(nothing);
    if (!the_guard)
	guard_can_come = 1;

    return;
} /* reset */

short() {
    if (set_light(0))
	return "Padrone's front yard";
    return "dark room";
}

init() {
    add_action("north", "north");
    add_action("east", "east");
    add_action("west", "west");
    add_action("buy", "buy");
    add_action("south", "south");
    add_action("enter", "enter");
    add_action("read", "read");
} /* init */

north() {
    this_player()->move_player("north#players/padrone/outside/path3");
    return 1;
}

east() {
    this_player()->move_player("east#players/padrone/outside/ne");
    return 1;
}

west() {
    this_player()->move_player("west#players/padrone/outside/nw");
    return 1;
}

id_gate(str) {
    return str == "door" || str == "gate";
}

id_sign(str) {
    return str == "sign";
}

id_fountain(str) {
    return str == "fountain";
}

id_slot(str) {
    return str == "slot";
}

id_castle(str) {
    return str && (   str == "castle" || str == "building"
		   || lower_case(str) == "castle of padrone");
}

id(str) {
    return    id_gate(str) || id_sign(str) || id_fountain(str)
	   || id_slot(str) || id_castle(str);
}

long(str) {
    if (set_light(0) == 0){
	write("It is dark.\n");
	return 1;
    }
    if (id_sign(str)) {
	read_sign();
	return 1;
    }
    else if (id_fountain(str)) {
	write("This is a beautiful fountain. It is not very useful, however.\n");
	return 1;
    }
    else if (id_castle(str)) {
	write("This is the Castle of Padrone.\n" +
	      "It is a large building made of grey stone, with two tall towers:\n" +
	      "a smaller tower at its northwestern corner, and a bigger one\n" +
	      "at its southeast. In that big tower, Padrone himself lives.\n");
	write("Even though it's made of stone and built in the middle of the\n" +
	      "dark, looming forest, this castle does not give an impression of\n" +
	      "darkness or raw power, but rather of friendly magic and helpfulness,\n" +
	      "with a somber undertone of law and order.\n");
	return 1;
    }
    else if (id_slot(str)) {
	write("Due to the high crime rate, all money for tickets is now directly\n" +
	      "transferred to the treasury by being put in this magic slot.\n");
	return 1;
    }
    else {
	write("You are standing in a small open space in the middle of the forest,\n" +
	      "just in front of a large building made of grey stone - the famous\n" +
	      "Castle of Padrone, the well-known Wizard of (among other things)\n" +
	      "Law and Balance.\n" +
	      "The front yard is surrounded by trees, and there is a fountain here.\n" +
	      "You can enter the castle by going south, through the main gate.\n" +
	      "A small path leads all the way round the castle, and you can follow\n" +
	      "it either to the west or to the east.\n" +
	      "North, another path leads through the forest, back to the more\n" +
	      "populated and civilized parts of the world.\n" +
	      "There is a sign beside the gate.\n");
	write("    There are four obvious exits: north, south, east and west.\n");
	return 1;
    }
}

buy(str) {
    object this_ticket, the_money;

    if (str != "ticket")
	return 0;
    else if (!the_guard || !present(the_guard, this_object()))
	write("And from whom are you going to buy that ticket?\n");
    else if (present("castle ticket", this_player()))
	write("But you already have a ticket!\n");
    else if (this_player()->query_money(0) < 20)
	write("But you don't have 20 gold coins.\n");
    else if (!this_player()->add_weight(1))
	write("You can't carry that much.\n");
    else {
	write("The guard sells you a ticket for 20 gold coins,\n");
	write("and deposits the money in a slot in the wall.\n");
	this_ticket = make_ticket();
	this_player()->add_money(-20);
	the_money = clone_object("obj/money");
	the_money->set_money(20);
	call_other("players/padrone/walker/cell", "put_in_vault", the_money);
	say(this_player()->query_name() + " buys a ticket from the guard.\n");
	this_ticket = make_ticket();
	move_object(this_ticket, this_player());
    }
    return 1;
} /* buy */

enter(str) {
    if (!str || id_castle(str))
	return south();
    else
	return 0;
} /* enter */

south() {
    if (the_guard && present(the_guard, this_object())) {
	if (present("castle ticket", this_player())) {
	    write("The guard smiles and says: Welcome to the Castle of Padrone!\n");
	    say("The guard smiles and says: Welcome to the Castle of Padrone!\n");
	}
	else {
	    write("The guard says: Excuse me, but the tickets cost 20 gold pieces.\n");
	    say("The guard says: Excuse me, but the tickets cost 20 gold pieces.\n");
	    write("The guard blocks your way.\n");
	    return 1;
	}
    }
    else {
	write("As you try to pass through the gate, you step on a hidden button.\n");
	write("A bell rings somewhere inside the castle, ");
	if (!guard_can_come) {
	    write("but nothing more seems to happen.\n");
	}
	else {
	    write("and a guard arrives.\n");
	    guard_can_come = 0;
	    
	    the_guard = clone_object("obj/monster");
	    the_guard->set_name("guard");
	    the_guard->set_level(1);
	    the_guard->set_hp(50);
	    the_guard->set_al(50);
	    the_guard->set_short("A guard");
	    the_guard->set_long("This is a guard dressed in a grey uniform.\n" +
				"He sells tickets to the the Castle, and stops\n" +
				"people without tickets from entering.\n");
	    the_guard->set_aggressive(0);

	    if (!function)
		setup_arrays();
	    the_guard->set_match(this_object(), function, type, match);

	    move_object(the_guard, this_object());
	    return 1;
	}
    }
    this_player()->move_player("south#players/padrone/inside/gate_room");
    return 1;
}

read(str)
{
    if (!id_sign(str))
	return 0;
    read_sign();
    return 1;
}

read_sign()
{
    say(this_player()->query_name() + " reads the sign beside the gate.\n");
    cat("/players/padrone/outside/gate_sign.txt");
}

make_ticket()
{
    object ticket;
    
    ticket_number = ticket_number + 1;
    ticket = clone_object("players/padrone/obj/ticket");
    ticket->set_ticket_number(ticket_number);
    return ticket;
} /* make_ticket */

handle_arrival(str)
{
    string who, rest, n;
    
    if (   present(the_guard, this_object())	/* The guard is in the front yard */
	&& present("walking castle", this_object())) {	/* And so is the walking castle */
	say("Guard says: Could you please move that walking castle somewhere else?\n");
	call_out("say_where", 4);
    }
} /* handle_arrival */

say_where() {
    say("Guard says: Try to put it in the open place east of the crossing.\n");
}

setup_arrays() {
    
    function = allocate(1);
    type = allocate(1);
    match = allocate(1);
    
    function[0] = "handle_arrival";
    type[0] = "arrives";
    match[0] = "";
} /* setup_arrays */
