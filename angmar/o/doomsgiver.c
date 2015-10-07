status wielded;
string wielded_by;
string name_of_weapon;
string cap_name;
string alt_name;
string alias_name;
string short_desc;
string long_desc;
string read_msg;
int class_of_weapon;
int value;
int local_weight;
object hit_func;
object wield_func;


query_name() { return name_of_weapon; }

long() {
    write(long_desc);
}

reset(arg) {
    if (arg) {
	return;
        set_heart_beat(1); 
    }
    wielded = 0; value = 0;
name_of_weapon="doomsgiver";
cap_name=capitalize(name_of_weapon);
alias_name="Doomsgiver";
short_desc="Doomsgiver";
long_desc=
   "This is a very powerful sword. You feel a magic aura surrounding it.\n"+
   "There is something written on it.\n";
read_msg=
  "The language is very old. You can hardly understand it. But the\n"+
  "sword once seem to have been owned by Angmar himself.\n";
class_of_weapon=22;
value=5000;
local_weight=5;
}

heart_beat() {
  object plr,al;
  if(!wielded) {
     set_heart_beat(0);
     return;
  }
  plr=environment(this_object());
  if(!living(plr)) {
    set_heart_beat(0);
    return;
  }

  al=call_other(plr,"query_alignment");
  if(al>-200) {
    tell_object(plr,"Your Doomsgiver seems to come alive!\n");
    call_other(plr,"drop_one_item",this_object());
    say("The Doomsgiver wriggles out of ");
    say(call_other(plr,"query_name",0));
    say("'s hands.\n");
    set_heart_beat(0);
  }
}

init() {
    if (read_msg) {
	add_action("read"); add_verb("read");
    }
    add_action("wield"); add_verb("wield");
}

wield(str) {
    if (!id(str))
	return 0;
    if (environment() != this_player()) {
	write("You must get it first!\n");
	return 1;
    }
    if (wielded) {
	write("You already wield it!\n");
	return 1;
    }

    if( (call_other(this_player(),"query_alignment",0) <= -200) ||
        (call_other(this_player(),"query_name",0) == "Angmar")) {
            wielded_by = this_player();
            call_other(this_player(),"wield",this_object());
            wielded = 1;
            set_heart_beat(1);
            return 1;
}
    write("You can't wield Angmar's sword. Maybe you're not evil enough...\n");
    say(call_other(this_player(),"query_name",0)+
        " failed to wield Doomsgiver\n");
    return 1;
}

short() {
    if (wielded)
	if(short_desc)
	    return short_desc + " (wielded)";
    return short_desc;
}

weapon_class() {
    return class_of_weapon;
}

id(str) {
  return str == name_of_weapon || str == alt_name || str == alias_name;
}

drop(silently) {
    if (wielded) {
	call_other(wielded_by, "stop_wielding");
	wielded = 0;
	if (!silently)
	    write("You drop your wielded weapon.\n");
    }
    return 0;
}

un_wield() {
    if (wielded)
	wielded = 0;
}

hit(attacker)
{
    if (hit_func)
	return call_other(hit_func,"weapon_hit",attacker);
    return 0;
}


read(str) {
    if (!id(str))
	return 0;
    write(read_msg);
    return 1;
}

query_value() {
    return value;
}

get() { return 1; }

query_weight() { return local_weight; }
