/*  In the mirrormaze.
 *	This is room maze53. In this room each player will encounter his
 *	mirror image. Max one image per player and reset.
 *	"done_list" is used to remember who had their images created
 *	since the last reset. This list is reset each reset (sorry).
 */

#include "maze.h"

string done_list;

#undef EXTRA_EAST
#define EXTRA_EAST \
if (present("anti-" + lower_case(this_player()->query_name()), this_object())) { \
    write("Your mirror image bars your way!\n"); \
    return 1; \
}

#undef EXTRA_RESET
#define EXTRA_RESET done_list = "\n";

#undef EXTRA_INIT
#define EXTRA_INIT make_mirror_image();

MAZE_ROOM("maze43", 0, "maze52", 0)

make_mirror_image() {
    object mirror_image, plr;
    string players_name, players_lc_name, junk1, junk2;
    int players_level, players_ep, players_al, players_hp;

    plr = this_player();
    if (plr->query_npc())
        return 0;

    players_name = plr->query_name();
    players_lc_name = lower_case(players_name);
    players_level = plr->query_level();
    players_hp = plr->query_hp();
    players_ep = plr->query_exp();
    players_al = plr->query_alignment();

    if (present("anti-" + players_lc_name, this_object()))
	return 0;

    if (sscanf(done_list, "%s<" + players_lc_name + ">%s", junk1, junk2) == 2)
        return 0;

        done_list = done_list + "<" + players_lc_name + ">\n";

	mirror_image = clone_object("obj/monster");
	mirror_image->set_name("anti-" + players_lc_name);
	mirror_image->set_alias("mirror image");
	mirror_image->set_level(players_level);
	mirror_image->set_hp(players_hp);

        /*  Ep for the mirror image:
	 *  Half that of the player (max 333K), and adjusted for low hp!
	 */
        if (players_ep > 666666)
	    players_ep = 666666;
        players_ep /= 2;
        players_ep *= players_hp;
        players_ep /= 42 + 8 * players_level;
        mirror_image->set_ep(players_ep);

        mirror_image->set_wc(plr->query_wc());
	mirror_image->set_ac(plr->query_ac() + 2);
		   /* He is made of glass, so he is a little harder than you... */

	if (players_al < -1000)
	    players_al = -1000;
	if (players_al > 1000)
	    players_al = 1000;
	mirror_image->set_al(-players_al);
	mirror_image->set_short("Anti-" + players_lc_name + ", " + players_name + "'s mirror image");
	mirror_image->set_long("Anti-" + players_lc_name + " looks exactly like " + players_name + ".\n");
	mirror_image->set_whimpy();

	if (players_level >= 15) {
	    mirror_image->set_spell_mess1("The mirror_image casts a fire ball.");
	    mirror_image->set_spell_mess2("You are hit by a fire ball.");
	    mirror_image->set_chance(70);
	    mirror_image->set_spell_dam(40);
	}
	else if (players_level >= 10) {
	    mirror_image->set_spell_mess1("The mirror_image casts a shock.");
	    mirror_image->set_spell_mess2("You are hit by a shock.");
	    mirror_image->set_chance(70);
	    mirror_image->set_spell_dam(30);
	}
	else if (players_level >= 5) {
	    mirror_image->set_spell_mess1("The mirror_image casts a magic missile.");
	    mirror_image->set_spell_mess2("You are hit by a magic missile.");
	    mirror_image->set_chance(70);
	    mirror_image->set_spell_dam(20);
	}

	move_object(mirror_image, this_object());
	return mirror_image;
} /* make_mirror_image */
