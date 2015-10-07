#include "../../../obj/door.h"

object the_dragon;
status dragon_can_come;
object obj_1, obj_2;	/* Used by the MAKE_DOORS macro */

/* For the NEW, IMPROVED monster class: */
string function, type, match;

id_note(str) {
    return str == "note" || str == "small note" || str == "door note";
}

id(str) {
    return id_note(str);
}

reset(arg) {

    if (!arg) {
	/* First reset */
	set_light( 1);
	dragon_can_come = 1;

	MAKE_DOORS("players/padrone/tower/hall", "north",
		   "players/padrone/tower/rambo_room", "south",
		   "moderate-security",
		   "treasurydoor",
		   "This is a stout wooden door, several inches thick.\n" +
		   "There is a small note nailed to it:\n" +
		   "    'Don't go in here. The guards have gone crazy again.'\n",
		   1, 1, 1)

	    /* Achtung! The text on the note is in two places in this file! */
    }
    else {
	obj_1->set_closed(1);
	obj_1->set_locked(1);
	obj_1->set_both_status();

	if (!the_dragon)
	    dragon_can_come = 1;
    }
}

short() {
	if (set_light(0)) return  	   "The tower hall";
	return "dark room";
}

init() {
	add_action("south", "south");
	add_action("do_read", "read");
	add_action("east", "east");
	add_action("west", "west");
	add_action("up", "up");
	add_action("down", "down");
}

south() {
    this_player()->move_player("south#players/padrone/tower/bedroom");
    return 1;
}
east() {
    this_player()->move_player("east#players/padrone/tower/lab");
    return 1;
}
west() {
    this_player()->move_player("west#players/padrone/tower/poolroom");
    return 1;
}
down() {
    this_player()->move_player("down#players/padrone/tower/tower4");
    return 1;
}
up() {
    string n;

    n = this_player()->query_name();

    if (the_dragon && present(the_dragon, this_object()) && (n != "Padrone")) {
	write("You cannot pass the dragon.\n");
	say(n + " tries to climb the ladder, but the dragon bars the way.\n");
    }
    else if (dragon_can_come && (n != "Padrone")) {
	write("As you try to climb the ladder, an alarm sounds!\n");
	say("As " + n + " tries to climb the ladder, an alarm sounds!\n");
	write("A giant stainless steel dragon shows up to investigate!\n");
	say("A giant stainless steel dragon shows up to investigate!\n");
	make_dragon();
    }
    else
	this_player()->move_player("up#players/padrone/workroom");
    return 1;
}

do_read(str) {
    if (id_note(str)) {
	write("The small note on the north door says:\n" +
	      "    'Don't go in here. The guards have gone crazy again.'\n");
	return 1;
    }
    else
	return 0;
}

long(str) {    
	if (set_light(0) == 0){
		write("It is dark.\n");
		return;
	}
	else if (id_note(str)) {
	    do_read("note");
	}
	else {
	    write("You are in the hall of Padrone's private tower.\n" +
		  "This is a big and spacious hall, so the interior of the tower must\n" +
		  "have been expanded using magic. Several doors lead to other rooms.\n" +
		  "A small ladder leads up to Padrone's private workroom,\n" +
		  "and a stone stairway leads down into the tower.\n" +
		  "There is a small note on the door leading north.\n");
	    write("There are six obvious exits: north, west, south, east, up and down.\n");
	}
}

make_dragon()
{
    object weapon, key;

    the_dragon = clone_object("obj/monster");	/* NEW, IMPROVED monster class! */
    the_dragon->set_name("giant stainless steel dragon");
    the_dragon->set_alias("dragon");
    the_dragon->set_level(19);
    the_dragon->set_hp(400);
    /* the_dragon->set_ep(444444); -- default */
    the_dragon->set_al(100);
    the_dragon->set_short("A giant stainless steel dragon with a machine gun");
    the_dragon->set_long("This is a giant stainless steel dragon.\n" +
			 "Its eyes glow with a fire hotter than molten iron\n" +
			 "and the razor claws have caused severe damage to the (stone) floor.\n" +
			 "The skin seems to be made of several inches of steel.\n" +
			 "It would probably be a very bad move to irritate this dragon...\n");
    the_dragon->set_ac(15);
    /* the_dragon->set_wc(30); */
    the_dragon->set_aggressive(0);
    the_dragon->set_spell_mess1("The dragon breathes fire. Woooosh!");
    the_dragon->set_spell_mess2("You are hit by the the dragon's firebreath! You are horribly burnt.");
    the_dragon->set_chance(20);
    the_dragon->set_spell_dam(40);
    weapon = clone_object("players/padrone/obj/machinegun");
    weapon->set_monsters_reload_at_reset(1);
    move_object(weapon, the_dragon);
    the_dragon->init_command("wield machinegun");

    MAKE_KEY(key, "moderate-security", "treasurydoor")
    move_object(key, the_dragon);

    /* The NEW, IMPROVED monster calls: */
    if (!function)
	setup_arrays();
    the_dragon->set_match(this_object(), function, type, match);

    move_object(the_dragon, this_object());
    dragon_can_come = 0;
} /* make_the_dragon */


/* For the NEW, IMPROVED monster class: */
setup_arrays() {

    function = allocate(1);
    type = allocate(1);
    match = allocate(1);

    function[0] = "ticket_check";
    type[0] = "arrives";
    match[0] = "";
} /* setup_arrays */


ticket_check(str) {
    string who, rest;
    object suspect;

    if (sscanf(str, "%s arrives%s", who, rest) != 2)
	return;		/* Some strange error! */
    suspect = present(lower_case(who), this_object());
    if (!suspect)
	return;		/* Already gone! */
    if (!present("castle ticket", suspect)) {
	/* A player/monster without a ticket has arrived! -- ATTACK! */
	/* No -- don't. */
	say("Giant stainless steel dragon immediately notices that " +
	    who + " hasn't got a ticket.\n");
	say("Giant stainless steel dragon says: You'd better get yourself a ticket.\n");
	/* the_dragon->attacked_by(suspect); */
    }
} /* ticket_check */
