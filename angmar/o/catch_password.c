#include <living.h>

/*
 * This is a listener. It listen to the players an communicate
 * with the environment
 */

string callfunc,callroom;
string next_out;
object next_dest,callobject;

short() {
    return 0;
}

get() { return 0; }

long() {
}

id(str) { return 0; }

reset(arg) {
    if (arg)
	return;
    msgout = "leaves";
    msgin = "enters";
    name = "listener";
    next_out = 0;
    is_npc = 1;
    level = 40;
    alignment = 0;
    weapon_class = WEAPON_CLASS_OF_HANDS;
    max_hp = 300;
    hit_point = 300;
    experience = 100000;
    enable_commands();
    spell_points = 300;
    is_invis = 1; 
}

set_object(obj) {
  callobject=obj;
}

set_room(str) {
  callroom=str;
}

catch_tell(str)
{
    object from;
    from = this_player();
    if (!from)
	return;	/* Not from a real player. */
    if(callobject) call_other(callobject, callfunc , str);
    else if(callroom) call_other(callroom, callfunc , str);
    else {
      set_heart_beat(0);
      destruct(this_object());
    }
}

/*
 * Always let the heart_beat do the talking, to simulate delay.
 */

heart_beat()
{
    if (next_out) {
	tell_object(next_dest, next_out);
	next_out = 0;
    }
    set_heart_beat(0);
}

set_call(str)
{
    callfunc = str;
}

