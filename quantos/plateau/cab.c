#include "std.h"

#define STILL	0
#define DOWN	1
#define UP	2

int level;
int door_is_open;
int time_to_close_door;
int dest;		/* Where we are going. */
int moving_time;	/* How long we are going to move. */
int delay_to_reset;	/* Move back to origin automatically after a delay. */

init() {
    add_action("press"); add_verb("press");
    add_action("press"); add_verb("push");
    add_action("open_door"); add_verb("open");
    add_action("close_door"); add_verb("close");
    add_action("out"); add_verb("out");
}

short() {
    return "taxicab";
}

reset(arg) {
    door_is_open = 0;
    if (arg)
	return;
    set_light(1);
    level = 2;
    dest = 2;
    moving_time = 0;
}

/*
 * Return true if closed door.
 */

query_door() { return !door_is_open; }

long() {
    write ("You are in a taxicab. On a panel in front of you are three\n");
    write ("buttons, numbered 1 to 3.\n");
    if (door_is_open)
	write ("The door of the cab is open.\n");
    if (!door_is_open)
	write ("The door of the cab is closed.\n");
}

press(button) {
    string b;
    if (!button)
	return 0;
    if (door_is_open) {
	write ("You must close the door first.\n");
	return 1;
    }
    if (sscanf(button, "button %s", b) != 1)
	b = button;
    if (moving_time > 0) {
	write("The cab is still moving.\n");
	return 1;
    }
    if (b == "1" || b == "one")
	dest = 1;
    if (b == "2" || b == "two")
	dest = 2;
    if (b == "3" || b == "three")
	dest = 3;
    if (dest == level) {
	write ("You are already here.\n");
	return 1;
    }
    if (dest > level) {
	moving_time = dest - level;
	write ("The cab starts moving with a mighty roar.\n");
	say ("The cab starts moving with a mighty roar.\n");
    }
    if (level > dest) {
	moving_time = level - dest;
	write ("The cab starts driving rapidly toward the city of lights.\n");
	say ("The cab starts driving rapidly toward the city of lights.\n");
    }
    if (dest == 1 || level == 1)
	moving_time += 10;
    moving_time += 1;
    set_heart_beat(1);
    return 1;
}

heart_beat() {
    if (time_to_close_door > 0) {
	time_to_close_door -= 1;
	if (time_to_close_door == 0) {
	    say("The door swings shut.\n");
	    door_is_open = 0;
	}
    }
    if (moving_time <= 0)
	return;
    moving_time -= 1;
    if (moving_time > 0) {
	say("The cab continues...\n");
	return;
    }
    say ("The taxicab screeches to a halt outside your destination.\n");
    set_heart_beat(0);
    level = dest;
    if (level == 2)
	call_other ("players/quantos/plateau/cab_stop", "cab_arrives", 0);
    if (level == 1)
	call_other ("players/quantos/cibola/city_limits", "cab_arrives", 0);
}

open_door(str)
{
    if (str != "door")
	return 0;
    if (door_is_open) {
	write("It is already open!\n");
	return 1;
    }
    if (moving_time > 0) {
	write ("You cannot open the door while the cab is in motion.\n");
	return 1;
    }
    door_is_open = 1;
    time_to_close_door = 3;
    write("Ok.\n");
    say(call_other(this_player(), "query_name", 0) + " opened the door.\n");
    return 1;
}

close_door(str)
{
    if (str != "door")
	return 0;
    if (!door_is_open) {
	write("It is closed!\n");
	return 1;
    }
    door_is_open = 0;
    time_to_close_door = 0;
    write("Ok.\n");
    say(call_other(this_player(), "query_name", 0) + " closed the door.\n");
    return 1;
}

out() {
    if (moving_time > 0) {
	write ("You cannot leave a moving cab.\n");
	return 1;
    }
    if (!door_is_open) {
	write("The door is closed.\n");
	return 1;
    }
    if (level == 2)
	call_other (this_player(), "move_player", "out#players/quantos/plateau/cab_stop");
    if (level == 1)
	call_other (this_player(), "move_player", "out#players/quantos/cibola/city_limits");
    if (level == 3)
	call_other (this_player(), "move_player", "out#players/quantos/villa/driveway");
    return 1;
}

query_level() { return level; }

/*
 * This routine is called from various rooms that the cab connects to.
 */
call_cab(button) {
    if (door_is_open)
	return 0;
    if (moving_time > 0)
	return 0;
    dest = button;
    if (dest == level)
	return 0;
    write("A little white lamp beside the button lights up.\n");
    say("A little white lamp beside the button lights up.\n");
    if (dest > level)
	moving_time = dest - level;
    if (level > dest)
	moving_time = level - dest;
    if (dest == 1 || level == 1)
	moving_time += 10;
    moving_time += 1;
    set_heart_beat(1);
    return 1;
}

id(str) {
    return str == "door" || str == "button" || str == "buttons";
}

/*
 * Only list inventory if not looking at anything special.
 */
can_put_and_get()
{
    return 0;
}
/*
 * Called by others to see if the cab is moving
 */
is_moving() { 
    if (level == dest )
	/* Still */
	return 0;
    if(level > dest)
	/* down */
	return 1;
    /* up */
    return 2;
}
