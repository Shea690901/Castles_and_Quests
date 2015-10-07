/*
 *  dungeon.c
 *	This is the room where the dungeon, i. e. the dung_room
 *	objects, are stored.
 */

#include "std.h"

string directions, shortdirections;
int opposite, delta_x, delta_y, delta_z;

#undef EXTRA_RESET
#define EXTRA_RESET extra_reset();

ONE_EXIT("players/padrone/workroom", "out",
	 "Dungeon room storage room",
	 "Dungeon room storage room.\n", 1)

find_dungeon_room(x, y, z) {
    object the_room;

    the_room = first_inventory(this_object());
    while (the_room) {
	if (the_room->match_xyz(x, y, z))
	    return the_room;
	the_room = next_inventory(the_room);
    }
}

extra_reset() {

    directions =
	({"up", "down", "north", "south", "east", "west",
	  "northwest", "northeast", "southwest", "southeast"});
    shortdirections =
	({"u", "d", "n", "s", "e", "w",
	  "nw", "ne", "sw", "se"});
    opposite = ({1, 0, 3, 2, 5, 4, 9, 8, 7, 6});
    delta_x = ({0, 0, 0, 0, 1, -1, -1, 1, -1, 1});
    delta_y = ({0, 0, 1, -1, 0, 0, 1, 1, -1, -1});
    delta_z = ({1, -1, 0, 0, 0, 0, 0, 0, 0, 0});
} /* extra_reset */

query_delta_x(dir_nr) { return delta_x[dir_nr]; }
query_delta_y(dir_nr) { return delta_y[dir_nr]; }
query_delta_z(dir_nr) { return delta_z[dir_nr]; }
query_opposite(dir_nr) { return opposite[dir_nr]; }
query_directions(dir_nr) { return directions; }

dir_to_nr(str) {
    int i;

    i = 0;
    while (i < 10) {
	if (str == directions[i])
	    return i;
	i += 1;
    }
    i = 0;
    while (i < 10) {
	if (str == shortdirections[i])
	    return i;
	i += 1;
    }
    return -1;
} /* dir_to_nr */

make_monster(dungeon_level) {
    object m;
    int ml;

    if (dungeon_level > 5 && !random(3)) {
	m = clone_object("obj/monster");
	m->set_name("dwarf");
	m->set_alias("martial-arts dwarf");
	m->set_alt_name("unarmed dwarf");
	m->set_level(10);
	m->set_male();
	m->set_wc(15);
	m->set_ac(6);
	m->set_hp(200);
	m->set_short("A small, unarmed dwarf");
	m->set_long("This is a small dwarf. He is about three feet tall,\n" +
		    "he has a big, dark beard, and he looks nice and friendly.\n" +
		    "He has no weapons and no armour, and he looks at you\n" +
		    "with his big brown eyes.\n");
	m->set_spell_mess1("This is a Martial-Arts Dwarf. He kicks his opponent very, very hard.");
	m->set_spell_mess2("This is a Martial-Arts Dwarf. He kicks you with a sickening sound.");
	m->set_chance(50);
	m->set_spell_damage(20);
	m->set_al(100);
	return m;
    }

    m = clone_object("obj/monster");
    m->set_alias("mole");
    ml = random(dungeon_level + 1) + 1;
    if (ml > 19)
	ml = 19;
    m->set_level(ml);
    m->set_wc(ml + 3);
    m->set_ac(ml / 2);
    m->set_hp(50 + ml*10);
    if (ml == 19) {
	m->set_name("mole king");
	m->set_alt_name("king");
	m->set_short("A mole king");
	m->set_long("This is a mole king, who rules over a tribe of moles.\n" +
		      "He is huge, and he looks really dangerous.\n");
	m->set_spell_mess1("The mole king uses his instinctive earth magic to hurt his enemy.");
	m->set_spell_mess2("The mole king uses his instinctive earth magic to hurt you.");
	m->set_chance(20);
	m->set_spell_damage(40);
	m->set_aggressive(1);
    }
    else if (ml == 18) {
	m->set_name("mole prince");
	m->set_alt_name("prince");
	m->set_short("A mole prince");
	m->set_long("This is a mole prince, a son of the mole king.\n" +
		      "He is very big, and he looks really dangerous.\n");
	m->set_aggressive(1);
    }
    else if (ml > 15) {
	m->set_name("giant mole");
	m->set_short("A giant mole");
	m->set_long("This is a very big mole.\n");
	m->set_aggressive(1);
    }
    else if (ml > 10) {
	m->set_name("very big mole");
	m->set_short("A very big mole");
	m->set_long("This is a very big mole.\n");
	m->set_aggressive(1);
    }
    else if (ml > 5) {
	m->set_name("big mole");
	m->set_short("A big mole");
	m->set_long("This is a big mole.\n");
	m->set_aggressive(1);
    }
    else if (ml > 2) {
	m->set_name("mole");
	m->set_short("A mole");
	m->set_long("This is a mole. It lives under the ground.\n");
    }
    else {
	m->set_name("small mole");
	m->set_short("A small mole");
	m->set_long("This is a small mole. It lives under the ground.\n");
    }
    return m;
} /* make_monster */
    
