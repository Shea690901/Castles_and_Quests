#include "std.h"
object paladin, weapon;

#undef EXTRA_RESET
#define EXTRA_RESET extra_reset();

id(str) { return str == "view" || str == "window"; }

#undef EXTRA_LONG
#define EXTRA_LONG\
    if (str == "view" || str == "window") {\
        write("You see a spectacular view of the plains and mountains.\n");\
        return;\
    }

extra_reset() {
    if (!paladin || !living(paladin)) {
        paladin = clone_object("obj/monster");
        call_other(paladin, "set_name", "paladin");
        call_other(paladin, "set_alias", "knight");
        call_other(paladin, "set_level", 19);
        call_other(paladin, "set_hp", 300);
        call_other(paladin, "set_al", 1000);
        call_other(paladin, "set_short", "A noble knight");
        call_other(paladin, "set_long", "A noble paladin.\n");
	move_object(paladin, this_object());
        weapon = clone_object("obj/weapon");
        call_other(weapon, "set_name", "glowing sword");
        call_other(weapon, "set_short", "A softly glowing sword");
        call_other(weapon, "set_alias", "sword");
        call_other(weapon, "set_long",
"It is a long sword of finest workmanship, and it glows with goodness.\n");
        call_other(weapon, "set_class", 20);
        call_other(weapon, "set_value", 1000);
        call_other(weapon, "set_weight", 3);
        call_other(weapon, "set_hit_func", this_object());
        call_other(weapon, "set_wield_func", this_object());
	transfer(weapon, paladin);
	call_other(paladin, "init_command", "wield sword");
    }
}

TWO_EXIT("players/morgar/towertop","up",
	 "players/morgar/tower2","down",
         "Fourth floor of the tower",
         "This is the fourth floor of the tower.  There is an\n" +
         "incredible view out the windows.\n", 1)

weapon_hit(target) {
    int i;
    i = (call_other(this_player(),"query_alignment",0) -
        call_other(target,"query_alignment",0));
    if (i < 0) /* negative attack */ {
	write("The blade seems to just glance off, doing no damage!\n");
	return "miss";
    }
    return 0;
}

wield(arg) {
    int i;
    if (call_other(this_player(), "query_alignment",0) < 200) {
        write("Only a paladin may wield a Holy Avenger.\n");
        return 0;
    }
    write("The Holy Avenger glows brightly.\n");
    return 1;
}
