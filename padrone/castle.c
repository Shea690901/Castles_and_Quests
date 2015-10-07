/*
 *  castle.c
 *	This is the facade to the Castle of Padrone.
 *	Latest change: Feb 4, 1991.
 */

#include "config.h"
#define DEST "room/forest6"

object remembered_pad;          /* A pointer to Padrone */

id(str) {
    return    str == "path" || str == "shrubbery"
	   || str == "south" || str == "bushes";
}

short() {
    return "You can see a small path winding south through some shrubbery";
}

long(arg) {
    write("To the south some dense bushes are obstructing the view.\n");
    write("However, there seems to be a path between them.\n");
}

init() {
    add_action("south", "south");
}

south() {

#ifdef NANNY
    /* Birds! Arrrgh!! Go away! Turn! Turn! */
    if (this_player()->query_npc() && this_player()->query_name() == "Bird")
    	return 0;
#endif

    write("You make your way through the bushes...\n");
    this_player()->move_player("south#players/padrone/outside/path1");

    if (!remembered_pad)
        remembered_pad = find_living("padrone");
    if (remembered_pad) {
        tell_object(remembered_pad, "\n");
        tell_object(remembered_pad, "*** Message from your castle: " +
                    this_player()->query_name() + " entered the path.\n");
    }
    return 1;
} /* south */

/*  This is the reset function, that is called with arg 0 when the castle is
 *  loaded. Other objects that have to be loaded, like for example the quest
 *  object, should be loaded from this function. BUT, to speed up game restart,
 *  some of the loading is done later from two different call_out calls.
 */
reset(arg) {
    object sign;

    if (arg) {
	/* This is the periodic reset */
	load_walker();	/* If it has died. It shouldn't, but... */
	return;
    }

    /* This is the first reset, when the castle is loaded */

    call_out("load_walker", 240);	/* Load the walker 4 minutes from now! */
    call_out("load_mirrormaze", 300);	/* Load the mirrormaze 5 minutes from now! */

    /* Load some facades and other objects that we need */
    call_other("players/padrone/outside/front_yard", "short");
    fix_the_quest();
    call_other("players/padrone/secret_police/shop_f", "short");

#ifdef NANNY
    /* On Nanny: Start the weather, and the deposit box service. */
    call_other("players/padrone/weather", "short");
    call_other("players/padrone/deposit/deposit_f", "short");
#endif

    sign = clone_object("players/padrone/obj/thing");
    sign->set_name("sign");
    sign->set_short("A sign pointing south");
    sign->set_long("This is a small white wooden sign on a pole.\n" +
		   "It is pointing south, and there is something written on it.\n");
    sign->set_read("It says: This way to the Castle of Padrone.\n");
    sign->set_can_get(0);
    move_object(sign, DEST);

    /* Load the extra player description, since it's supposed to be autoloading! */
#ifndef GENESIS
    /* Not used on Genesis! */
    destruct(clone_object("players/padrone/obj/appearance"));
#endif
    /* And the secret police badge! */
    destruct(clone_object("players/padrone/secret_police/membership"));

    /* And finally, put this castle facade where it should be! */
    move_object(this_object(), DEST);
} /* reset */

load_walker() {
    /* This call will load the walking castle, if it is not already loaded. */
    call_other("players/padrone/walker/castle", "short");
}

load_mirrormaze() {
    object the_room;

    /* Initialize the magic mirrors and the mirrormaze! */
    the_room = call_other("players/padrone/maze/load_mirrors", "return_me");
    /* There is no reason to keep that room loaded. */
    destruct(the_room);
}

fix_the_quest() {
    object qobj;

    move_object(this_object(), "room/quest_room");
    if (!present("padrone", environment(this_object()))) {
	qobj = clone_object("obj/quest_obj");
	qobj->set_name("padrone");
	qobj->set_hint("Padrone is sad. He built a beautiful walking castle,\n" +
		       "but a gang of pirates stole it and now he cannot\n" +
		       "find it any more. Help him to get it back!\n" +
		       "You don't have to be big and dangerous to solve this quest,\n" +
		       "but it's always a good idea to bring a weapon and some armour...\n");
	move_object(qobj, "room/quest_room");
    }
} /* fix_the_quest */
