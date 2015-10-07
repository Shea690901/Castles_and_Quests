#include <living.h>

/*
 * The heart beat is started in living.h when we are attacked.
 */

reset(arg)
{
    if (arg)
       return;
    max_hp = 50;
    hit_point = 50;
    level = 3;
    experience = 1500;
    weapon_class = 10;
    is_npc = 1;
    name = "elf";
    cap_name = "Elf";
    alignment = 20;
    enable_commands();
}

short() {
   return "An elf";
}

long() {
    write("An elf.\n");
    if (hit_point > max_hp - 5)
       write("The elf seems to be in a good shape.\n");
}

id(str) { return str == name; }

heart_beat()
{
    age += 1;
    if (!attack())
	set_heart_beat(0);
}


query_kill_elf(){ return 1;}
