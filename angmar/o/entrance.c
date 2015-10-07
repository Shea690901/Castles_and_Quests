#include <living.h>

string callfunc,callroom;
string next_out;
object next_dest,callobject;


reset(arg) {
    if (arg)
	return;
    name = "listener";
    next_out = 0;
    is_npc = 1;
    level = 40;
    max_hp = 300;
    hit_point = 300;
    enable_commands();
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

