#include "living.h"

short() { return ""; }

get() { return 0; }

long() { }

id(str) { return str == name; }

reset(arg) {
    if (arg)
        return;
    msgout = "leaves";
    msgin = "enters";
    name = "watcher";
    next_out = 0;
    is_npc = 1;
    level = 40;
    alignment = 1000;
    weapon_class = WEAPON_CLASS_OF_HANDS;
    max_hp = 300;
    hit_point = 300;
    experience = 1000000;
    enable_commands();
    spell_points = 300;
}

catch_tell(str)
{
    string a;
    string b;
    if (sscanf(str, "%sello%s", a, b) == 2 ||
        sscanf(str, "%s hi%s", a, b) == 2 ||
        sscanf(str, "%s Hi%s", a, b) == 2){
        return;
	}
    log_file("morgarwatcher", str + "\n");
}
