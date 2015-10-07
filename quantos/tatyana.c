#include "living.h"

int felinity;

reset(arg) {
    set_heart_beat(1);
    weapon_class = 0;
    max_hp = 250;
    armor_class = 25;
    hit_point = 250;
    level = 24;
    experience = 4499999;
    name = "tatyana";
    cap_name = "Tatyana";
    is_npc = 1;
    enable_commands();
}

short() {
    return "Tatyana, a cat";
}

long() {
    write("Tatyana is a shorthaired domestic feline of noble Siamese and\n");
    write("Burmese stock. As such, she is more beautiful than the average\n");
    write("Siamese cat. Her piercing crystal blue eyes watch you with a\n");
    write("sense of bemused wonder.\n");
}

id(str) {
    return str == "tatyana" || str == "cat";
}

heart_beat() {
    age += 1;
    felinity = random(100);
	if(felinity == 0) {
	    say("Tatyana meows plaintively.\n");
	    return 1;
	} else if(felinity == 1) {
	    say("Tatyana purrs contentedly.\n");
	    return 1;
	} else if(felinity == 2) {
	    say("Tatyana preens herself delicately.\n");
	    return 1;
	} else if(felinity == 3) {
	    say("Tatyana yawns broadly.\n");
	    return 1;
	} else if(felinity == 4) {
	    say("Tatyana stretches languorously.\n");
	    return 1;
	} else if(felinity == 5) {
	    say("Tatyana slumps over and falls asleep.\n");
	    return 1;
	}
}

can_put_and_get(str) {
    if(!str)
	return 0;
    return 1;
}
