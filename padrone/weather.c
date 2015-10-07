/*
 *  "weather.c" -- the local weather
 *	Since it must be able to move, the weather is a living object.
 *  Thomas Padron-McCarthy padrone@lysator.liu.se 1990
 */

#include "../../obj/living.h"
#define DEST "room/hump"

object curr_room_obj;
string weather, short_desc, long_desc, start_message, stop_message;
int weather_number;
int beat_count, move_count;

short() {
    return 0;
}

long() {
    write(long_desc);
}

reset(arg) {
    if (!arg) {
	/* First reset */
	if (find_living("weather")) {
	    write("Another weather already in operation! Self-destruct!\n");
	    destruct(this_object());
	    return;
	}

	is_invis = 1;
	is_npc = 1;

	/* Monsters CAN hit on it! */
	max_hp = 210000000;
	hit_point = max_hp;
	armour_class = 210000000;

	name = "weather";
	enable_commands();

 	/* We must move_object AFTER enable_commands! */
	move_object(this_object(), DEST);
	curr_room_obj = environment(this_object());
	weather_number = -1;
	change_weather();
	if (weather_number == 5)
	    set_light(-1); /* A local sun eclipse */
	tell_room(curr_room_obj, start_message);
	beat_count = 0;
	move_count = 0;
	set_heart_beat(1);
    }
} /* reset */

heart_beat() {

    age += 1;
    beat_count += 1;
    if (beat_count > 2) {
	move_count += 1;
	if (move_count > 9) {
	    /* Every 30 heartbeats: */	    
	    move_weather();
	    move_count = 0;
	}
	else {
	    /* Every 3 heartbeats: */
	    tell_room(curr_room_obj, short_desc);

	    if (weather_number == 2) {
		/* sunshine! */
		int obj;
		obj = first_inventory(curr_room_obj);
		while (obj) {
		    if (living(obj))
			call_other(obj, "heal_self", 4);
		    obj = next_inventory(curr_room_obj);
		}
	    } /* weather */

	    beat_count = 0;
	}
    }
} /* heart_beat */

id(str) {
    return str == "weather" || str == weather;
}

get() {
    write("You can't pick up the weather.\n");
    return 0;
}

query_name() { return "weather"; }

catch_tell(str)
{
    string who, rest, n;
    object who_object;

    if (sscanf(str, "%s arrives%s", who, rest) != 2)
	return;
    if ((who == "Weather") || (who == "weather"))
	return;
    /* say("Weather says: Ok, I heard: " + str + "\n"); -- debug */
    who_object = present(lower_case(who), curr_room_obj);
    if (who_object)
	tell_object(who_object, long_desc);
} /* catch_tell */

random_move()
{
    int n;
    n = random(4);

    if (n == 0)
	command("west");
    else if (n == 1)
	command("east");
    else if (n == 2)
	command("south");
    else if (n == 3)
	command("north");
} /* random_move */

move_weather(str)
{

    tell_room(curr_room_obj, stop_message);
    if (weather_number == 5)
	set_light(1); /* The local sun eclipse goes away */
    change_weather();

    random_move();
    /* If this room is indoors, we cant go in! */
    if (indoors_room(environment(this_object())))
	move_object(this_object(), curr_room_obj);

    curr_room_obj = environment(this_object());
    tell_room(curr_room_obj, start_message);
    if (weather_number == 5)
	set_light(-1); /* A local sun eclipse */
} /* move_weather */

change_weather()
{
    int n;

    n = random(6);
    while (n == weather_number)
	n = random(6);
    weather_number = n;
    if (n == 0) {
	weather = "rain";
	start_message = "It starts to rain.\n";
	long_desc = "It is raining here. You feel cold and wet.\n";
	short_desc = "It is raining here.\n";
	stop_message = "The rain finally stops.\n";
    }
    else if (n == 1) {
	weather = "snow";
	start_message = "It gets much colder, and it starts to snow.\n";
	long_desc = "It is snowing here. Beautiful white snowflakes fill the air.\n";
	short_desc = "It is snowing here.\n";
	stop_message = "The snowing stops.\n";
    }
    else if (n == 2) {
	weather = "sunshine";
	start_message = "The sun breaks through the clouds.\n";
	long_desc = "The sun is shining here. You feel warm and very happy.\n";
	short_desc = "The sun is shining here. You feel stronger, lying in the sun.\n";
	stop_message = "The sun hides behind a cloud. How sad!\n";
    }
    else if (n == 3) {
	weather = "fog";
	start_message = "It gets a bit colder, and the fog rolls in.\n";
	long_desc = "The fog is thick here. You can almost not see. You feel cold and wet.\n";
	short_desc = "It is foggy here.\n";
	stop_message = "The fog evaporates.\n";
    }
    else if (n == 4) {
	weather = "clouds";
	start_message = "Some big and black clouds are coming in from the horizon.\n";
	long_desc = "It is cloudy here. You feel a bit depressed.\n";
	short_desc = "The weather is cloudy.\n";
	stop_message = "The clouds go away.\n";
    }
    else if (n == 5) {
	weather = "sun eclipse";
	start_message = "Suddenly, a local sun eclipse occurs. It gets dark.\n";
	long_desc = "There is a local sun eclipse here. It is dark.\n";
	short_desc = "There is a local sun eclipse here.\n";
	stop_message = "The sun returns.\n";
    }
} /* change_weather */


indoors_room(the_room) {
    string room_desc, junk1, junk2;

    room_desc = call_other(the_room, "short");
    if (!room_desc)
	return 1;	/* If short not defined - don't enter! */
    room_desc = "." + room_desc + ".";

    if (   sscanf(room_desc, "%sroom%s", junk1, junk2) == 2
	|| sscanf(room_desc, "%soffice%s", junk1, junk2) == 2
	|| sscanf(room_desc, "%ssmith%s", junk1, junk2) == 2
	|| sscanf(room_desc, "%schurch%s", junk1, junk2) == 2
	|| sscanf(room_desc, "%spub%s", junk1, junk2) == 2
	|| sscanf(room_desc, "%sshop%s", junk1, junk2) == 2
	|| sscanf(room_desc, "%spost%s", junk1, junk2) == 2
	|| sscanf(room_desc, "%sbank%s", junk1, junk2) == 2
	|| sscanf(room_desc, "%shall%s", junk1, junk2) == 2
	|| sscanf(room_desc, "%sinside%s", junk1, junk2) == 2
	|| sscanf(room_desc, "%sangmar%s", junk1, junk2) == 2
	|| sscanf(room_desc, "%scorridor%s", junk1, junk2) == 2
	|| sscanf(room_desc, "%sentrance%s", junk1, junk2) == 2
	|| sscanf(room_desc, "%stunnel%s", junk1, junk2) == 2)

	return 1;
    else
	return 0;
} /* indoors_room */
