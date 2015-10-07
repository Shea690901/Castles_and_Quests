#include "../living.h"

/*
 * The heart beat is started in living.h when we are attacked.
 */

reset(arg)
{
    if (arg)
       return;
    max_hp = 30;
    hit_point = 30;
    level = 3;
    experience = 2000;
    weapon_class = WEAPON_CLASS_OF_HANDS;
    is_npc = 1;
    name = "rat";
    cap_name = "Rat";
    alignment = -10;
    enable_commands();
}

short() {
   return "A rat";
}

long() {
    write("A very ugly and smelly rat.");
    if (hit_point > max_hp - 5)
       write("The rat seems to be in a good shape.\n");
}

id(str) { return str == name; }

heart_beat()
{
    age += 1;
    if (!attack())
	set_heart_beat(0);
}
