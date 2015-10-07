/*
 *  The Walking Castle - a moving castle for LPmud.
 *  This is the new, perfect, bug-free version (version 4).
 *  Latest change of this file: Feb 22, 1991.
 *  Author: Thomas Padron-McCarthy (Email: padrone@lysator.liu.se) 1990
 *  Copyright: No. Do anything you want with it. Share and enjoy.
 *             Except, don't sell it and don't claim you wrote it.
 *
 *  The castle walks around randomly in the /room area, but when
 *  driven by a player it can enter the /player areas too.
 *  It should not be possible to enter rooms that are indoors.
 *
 *  players/padrone/walker/castle.c -- the "castle.c" for the walking castle
 *
 *	It is from this object the castle is controlled.
 *	Everything happens here, commands are sent here and
 *	messages are sent back if something happens.
 *
 *	Since it must be able to move, the castle should really be
 *	a living object, but since (in later versions of LPmud)
 *	living objects cannot define commands, we use a special
 *	"invisible castle mover" ["players/padrone/walker/mover.c"]
 *	that does the walking and then moves the castle.
 *
 *	We assume that the castle rooms are on a subdir on a player dir,
 *	and if it isn't called "players/padrone/walker", you are
 *	in serious trouble.
 *
 *  Version 2, with call_out and without pointers to the rooms
 *    (since it is now possible to do tell_room without a pointer).
 *  Version 3, with a separate object defining the commands (climb etc),
 *    since living objects cannot define commands any more.
 *
 *  Version 4: The castle is not alive - we use an invisible castle mover
 *    instead. It doesn't autowalk out of the "/room" rooms.
 *    With automatic restart after call_out errors.
 *    You need a move_player that can take an object as a second argument.
 *    You also need arrays, at least if you want to use the pub
 *    as it is ["players/padrone/walker/pub.c"].
 *
 *  You can change DEST and MOVE_DELAY in "players/padrone/walker/walker.h".
 *  In the export version, DEMON should NOT be defined.
 *
 *  On LPmuds using American spelling, you will have to change the #define
 *  of ARMOUR in "walker.h" from "armour" to "armor".
 *  Or even better, learn how to spell. Like me doo.
 *
 */

#include "walker.h"
/* This object is not alive, so we do NOT include /obj/living.h. */

object latest_room_object, latest_driver;
status drawbridge_down, airborne, on_the_move;
int nr_call_outs, start_time, latest_call_out_time;
string latest_direction, latest_tell_bridge;

short() {
    if (airborne)
	return "A castle is flying high up in the sky";
    else
	return "A castle is standing here on its giant legs";
} /* short */

long() {
    if (airborne) {
	write("It is too high up for any details to be seen.\n");
	return;
    }
    write("This looks like an ordinary castle with walls, towers and a drawbridge\n" +
	  "- except for the fact that it is standing on a pair of giant legs!\n" +
	  "You understand that this must be the famous walking castle.\n");
    if (drawbridge_down)
	write("The drawbridge is down, so you can enter the castle easily.\n");
    else
	write("The drawbridge is up and the gates are closed.\n");
    write("A rope ladder is hanging down from an opening in the underside\n" +
	  "of the castle, and it seems possible to climb up that way.\n");
    if (this_player() && this_player()->query_level() > 19) {
	write("---\n");
	show_stats();
    }
} /* long */

reset(arg) {

    if (!arg) {
	/* First reset */
	move_object(this_object(), DEST);
	call_other(CASTLE_MOVER, "come_here");

	drawbridge_down = 0;
	airborne = 0;
	start_time = time();
	nr_call_outs = 0;

	call_out("automove", MOVE_DELAY);
	/* No heartbeat is required, as we use call_out. */
    }
    else {
	/* Periodic reset */
	error_check();
    }

    latest_driver = 0;
    on_the_move = 0;
} /* reset */

callable_castle_reset() {
    move_object(this_object(), DEST);
    call_other(CASTLE_MOVER, "come_here");
    set_drawbridge_down(0);
    set_airborne(0);
    call_other(BRIDGE, "reset", 1);
    error_check();
} /* callable_castle_reset */

show_stats() {
    write("Walking castle status:\n");
    write("  This is Padrone's Walking Castle, version " + WALKER_VERSION + ".\n");
    write("  start_time = " + ctime(start_time) +
	  " (" + (time() - start_time) + " seconds ago)\n");
    write("  latest_call_out_time = " + ctime(latest_call_out_time) +
	  " (" + (time() - latest_call_out_time) + " seconds ago)\n");
    write("  nr_call_outs = " + nr_call_outs + ", move_delay = " + MOVE_DELAY + " seconds\n");
    write("  drawbridge_down = " + drawbridge_down + ", airborne = " + airborne + "\n");
    write("  environment = "); write(environment(this_object())); write("\n");
    write("  latest_driver = "); write(latest_driver);
    if (latest_driver)
	write(" (\"" + latest_driver->query_name() + "\")");
    write(", latest_direction = "); write(latest_direction);
    write("\n");
} /* show_stats */

/* This function is called by call_out to move the castle: */
automove() {
    string direction;

    nr_call_outs += 1;
    latest_call_out_time = time();
    if (call_other(BRIDGE, "pilot_is_alive")) {
	/* The pilot is alive on the bridge */
	direction = random_direction();
	move_castle(direction, 1);
    }
    call_out("automove", MOVE_DELAY);
} /* automove */

id(str) {
    return    str == "castle"
	   || str == "walking castle"
	   || (str == "flying castle" && airborne);
}

get() { return 0; }

query_name() { return "castle"; }
query_drawbridge_down() { return drawbridge_down; }
query_airborne() { return airborne; }
query_environment() { return environment(this_object()); }

who_drove_it_here() { return latest_driver; }

set_drawbridge_down(f) {
    on_the_move = 1;	/* So the messages are not repeated to the bridge. */
    if (f && !drawbridge_down) {
	if (!airborne)
	    tell_room(environment(this_object()),
		      "You see the drawbridge of the walking castle coming down.\n");
	tell_room(GATE_ROOM, "You see the drawbridge being lowered.\n");
	tell_room(GATE_CONTROL, "You hear a grinding sound from the east.\n");
	tell_room(BRIDGE, "You see the drawbridge being lowered.\n");
    }
    else if (!f && drawbridge_down) {
	if (!airborne)
	    tell_room(environment(this_object()),
		      "You see the drawbridge of the walking castle being raised.\n");
	tell_room(GATE_ROOM, "You see the drawbridge being raised.\n");
	tell_room(GATE_CONTROL, "You hear a grinding sound from the east.\n");
	tell_room(BRIDGE, "You see the drawbridge being raised.\n");
    }
    drawbridge_down = f;
    on_the_move = 0;
} /* set_drawbridge_down */

set_airborne(f) {
    on_the_move = 1;	/* So the messages are not repeated to the bridge. */
    if (f && !airborne) {
	tell_room(environment(this_object()),
		  "Suddenly, the walking castle takes off and soars up into the sky!\n" +
		  "This is not only a walking castle, but also a flying one!\n");
	tell_room(BRIDGE, "The ground outside the window disappears.\n");
	tell_room(ROPE_LADDER, "The ground below disappears.\n");
	if (drawbridge_down)
	    tell_room(GATE_ROOM, "The ground outside the open gate disappears.\n");
    }
    else if (!f && airborne) {
	tell_room(environment(this_object()), "Suddenly, a flying castle lands! You are amazed!\n" +
		  "This is the famous walking castle, that also can fly through the skies.\n");
	tell_room(BRIDGE,
		  "The eagle has landed. Now you can see the ground outside the window.\n");
	tell_room(ROPE_LADDER, "Now you can see the ground below you.\n");
	if (drawbridge_down)
	    tell_room(GATE_ROOM, "Now you can see the ground outside the open gates.\n");
    }
    airborne = f;
    on_the_move = 0;
} /* set_airborne */


/*  This is the big "move the castle" function.
 *  It is called either from automove (in this object),
 *  or when a player moves the joystick on the bridge.
 */
move_castle(direction, auto_moving)
{
    object old_room_object, new_room_object;

    on_the_move = 1;
    latest_driver = this_player();	/* Even if it is 0! */
    latest_direction = direction;

    old_room_object = environment(this_object());

    /*  The invisible castle mover can quite possibly be somewhere else
     *  (or it could have been destructed):
     */
    call_other(CASTLE_MOVER, "come_here");

    /*  Now we tell the invisible castle mover to move in direction 'direction'.
     *  The bridge is supposed to filter away things like
     *  'move joystick kill giant'.
     */
    call_other(CASTLE_MOVER, "init_command", direction);

    new_room_object = call_other(CASTLE_MOVER, "query_environment");

    /*  Now the object "old_room_object" is the location where
     *  the castle is currently standing, and "new_room_object"
     *  is the new location, the location where the invisible castle mover
     *  just has moved into, and that we are trying to enter!
     *  We can not enter the new location if
     *    a) the two locations are the same (i. e. she couldn't move), OR
     *    b) the new room is indoors AND we are not already indoors.
     *  Those cases will cause the castle to "fail to enter".
     *  If we are auto-walking, we can ALSO not enter if
     *    c) the new room is not in /room AND we are now in /room, OR
     *    d) the new room is the goal room for the quest.
     *  Those cases will cause the castle simply not to move.
     *  Case d) is of course unnecessary in the export version.
     *  To save time: If the new room is the same as the previous room
     *  we were in (latest_room_object), then we know we can go there,
     *  so we'll just enter.
     */

    if (auto_moving) {
	/* The castle is auto-walking, i. e. the pilot is alive on the bridge */
	if (   (new_room_object != latest_room_object)
	    && (   (!room_room(new_room_object) && room_room(old_room_object))
		|| (file_name(new_room_object) == "players/padrone/outside/finish_quest"))) {
	    /* Auto-walking to a place we cannot auto-walk to (and not the latest room). */
	    on_the_move = 0;
	    call_other(CASTLE_MOVER, "come_here");	/* Because of her catch_tell()! */
	    return;
	}
	/* Auto-walking, and we are allowed to auto-walk into this place */
	tell_room(BRIDGE, "The pilot moves the joystick " + direction + ".\n");
    }

    if (   (new_room_object != latest_room_object)
        && (indoors_room(new_room_object) && !indoors_room(old_room_object))) {
	/*  Failed to move. But we will NOT print all the "failed to move" messages
	 *  here, since it is (remotely) possible that the move_object() below
	 *  could fail. Therefore, try it, and if we don't end up where we
	 *  are supposed to, THEN we know that we "failed to move".
	 */
    }
    else {
	move_object(this_object(), new_room_object);
    }

    if (environment(this_object()) == old_room_object) {
	/* Still in the same room. We couldn't move that way. */
	tell_room(old_room_object, "The castle tries to move " + direction + " but fails.\n");
	tell_room(BRIDGE, "The castle tries to move " + direction + " but fails.\n");
	tell_room(ROPE_LADDER, "The castle tries to move " + direction + " but fails.\n");
	if (drawbridge_down)
	    tell_room(GATE_ROOM, "The castle tries to move " + direction + " but fails.\n");
	on_the_move = 0;
	call_other(CASTLE_MOVER, "come_here");	/* Because of her catch_tell()! */
	return;
    }

    latest_room_object = old_room_object;
    /* And just to be on the very safe side: */
    new_room_object = environment(this_object());

    if (airborne)
	tell_room(old_room_object, "The castle flies away " + direction + ".\n");
    else
	tell_room(old_room_object, "The castle takes a giant step and leaves " + direction + ".\n");

    if (airborne)
	tell_room(new_room_object, "High up in the sky, a castle comes flying.\n");
    else
	tell_room(new_room_object, "A castle comes walking on its giant legs.\n");
    if (airborne) {    
	tell_room(BRIDGE, "The castle flies...\n");
	tell_room(ROPE_LADDER, "The castle flies...\n");
    }
    else {
	tell_room(BRIDGE, "The castle takes a giant step " + direction +
		  " and arrives in " + new_room_object->short() + ".\n");
	tell_room(ROPE_LADDER, "The castle takes a giant step " + direction +
		  "! You almost fall down.\n");
    }

    if (drawbridge_down) {
	if (airborne)
	    tell_room(GATE_ROOM, "The castle flies...\n");
	else
	    tell_room(GATE_ROOM, "The castle takes a giant step " + direction + "!\n");
    }

    on_the_move = 0;

    /*
     *  The castle comes walking into a new room...
     *  Step on the monsters! Hahahahaaaa! (Sorry)
     *  Only do this if there are players in the room, so the castle
     *  doesn't walk around stomping monsters all by itself,
     *  leaving heaps of treasure everywhere.
     *  Also, only step on monsters when on automatic drive
     *  (i. e. pirate-driven) -- we don't want the players to
     *  use the castle as a weapon (what cowardice that would be!).
     *  And don't step on the invisible castle mover.
     */
    if (!airborne) {
	int obj, this_obj;
	string monstername;
	status players_in_room;

	players_in_room = 0;
	obj = first_inventory(new_room_object);
	while (obj && !players_in_room) {
	    if (living(obj) && !obj->query_npc())
		players_in_room = 1;
	    obj = next_inventory(obj);
	}
	if (!players_in_room)
	    return;	/* Noone to see it */
	if (!call_other(BRIDGE, "pilot_is_alive"))
	    return;	/* Castle driven by players */

	obj = first_inventory(new_room_object);
	while (obj) {

	    this_obj = obj;
	    obj = next_inventory(obj);
	    if (   !random(30) && living(this_obj) && this_obj->query_npc()
		&& file_name(this_obj) != CASTLE_MOVER) {

		monstername = this_obj->query_name();
		on_the_move = 1;	/* So the messages are not repeated to the bridge. */
		tell_room(BRIDGE, "You notice that " + monstername +
			  " disappears under one of the giant feet.\n");
		tell_room(new_room_object, "It steps on the poor " + monstername +
			  "! How horrible!\n");
		on_the_move = 0;
		this_obj->hit_player(1000);
		return;
	    }
	}
    }
} /* move_castle */

random_direction() {
    int n;
    n = random(4);
    if (n == 0)
	return "west";
    else if (n == 1)
	return "east";
    else if (n == 2)
	return "south";
    else if (n == 3)
	return "north";
} /* random_direction */

/* See if the room is one of the "/room" rooms. */
room_room(the_room) {
    string the_name, junk;

    the_name = file_name(the_room);
    return the_name && sscanf(the_name, "room/%s", junk) == 1;
} /* room_room */

/* Try to see if the room is indoors. */
indoors_room(the_room) {
    string room_desc, junk1, junk2;

    room_desc = the_room->short();
    if (!room_desc)
	return 1;	/* If short not defined - don't enter! */
    room_desc = "." + lower_case(room_desc) + ".";

    return    sscanf(room_desc, "%sroom%s", junk1, junk2) == 2
	   || sscanf(room_desc, "%soffice%s", junk1, junk2) == 2
           || sscanf(room_desc, "%ssmith%s", junk1, junk2) == 2
   	   || sscanf(room_desc, "%schurch%s", junk1, junk2) == 2
	   || sscanf(room_desc, "%spub%s", junk1, junk2) == 2
	   || sscanf(room_desc, "%sbar%s", junk1, junk2) == 2
	   || sscanf(room_desc, "%sshop%s", junk1, junk2) == 2
	   || sscanf(room_desc, "%spost%s", junk1, junk2) == 2
	   || sscanf(room_desc, "%sbank%s", junk1, junk2) == 2
	   || sscanf(room_desc, "%shall%s", junk1, junk2) == 2
	   || sscanf(room_desc, "%sinside%s", junk1, junk2) == 2
	   || sscanf(room_desc, "%scorridor%s", junk1, junk2) == 2
	   || sscanf(room_desc, "%sentrance%s", junk1, junk2) == 2
	   || sscanf(room_desc, "%sguild%s", junk1, junk2) == 2
	   || sscanf(room_desc, "%stunnel%s", junk1, junk2) == 2;
} /* indoors_room */

/*----- The commands that are defined by the walking castle object: ------*/

init() {
    add_action("enter", "enter");
    add_action("climb", "climb");
} /* init */

enter(str) {
    if (!id(str))
	return 0;
    else if (airborne) {
	write("The castle is flying high up in the sky. You cannot enter.\n");
	return 1;
    }
    else if (!drawbridge_down) {
	write("The drawbridge is up and the gates are closed.\n");
	return 1;
    }
    write("You enter the castle through the main gate.\n");
    this_player()->move_player("into castle", GATE_ROOM);
    return 1;
} /* enter */


climb(str) {
    if (!id(str) && str != "ladder" && str != "rope ladder"  && str != "rope" && str != "up")
	return 0;
    else if (airborne) {
	write("The castle is flying high up in the sky.\n");
	return 1;
    }
    write("You climb the rope ladder.\n");
    this_player()->move_player("up on the rope ladder", ROPE_LADDER);
    return 1;
} /* climb */


/*  Check if the castle has crashed.
 *	If the function "automove" has not been called in more than
 *	3 * MOVE_DELAY seconds, we guess that the castle's call_out
 *	has crashed, something that can happen if it tries to enter
 *	a room with errors.
 *	In that case we will use another object, the CASTLE_RESTARTER,
 *	to destruct the castle and start it again.
 */
error_check() {
    object the_castle, the_castle_env, the_mover, the_mover_env;

    if (time() - latest_call_out_time < 3 * MOVE_DELAY)
	return;	/* All was, probably, ok. */

    WALKER_LOG(ctime(time()) + ": Going to restart the walking castle...\n")

    the_castle = this_object();
    the_castle_env = environment(the_castle);

    if (the_castle_env) {
	WALKER_LOG("   It was in " + file_name(the_castle_env) + ".\n")
    }
    else {
	WALKER_LOG("   It was in no room.\n")
    }

    the_mover = find_object(CASTLE_MOVER);
    if (!the_mover) {
	WALKER_LOG("   The mover has disappeared.\n")
    }
    else {
	the_mover_env = environment(the_mover);
	destruct(the_mover);
	if (the_mover_env) {
	    WALKER_LOG("   The mover was in " + file_name(the_mover_env) + ".\n")
	}
	else {
	    WALKER_LOG("   The mover was in no room.\n")
	}
    }

    WALKER_LOG("   Latest direction was " + latest_direction + ".\n")
    WALKER_LOG("   Latest message was: " + latest_tell_bridge)

    call_other(CASTLE_RESTARTER, "restart_castle");
} /* error_check */

tell_bridge(str) {
    latest_tell_bridge = str;
	/* If there is an error, we will write this message to the log. */
    if (!on_the_move && !airborne)
	tell_room(BRIDGE, "Outside the windows, " + str);
} /* tell_bridge */
