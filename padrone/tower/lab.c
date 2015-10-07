#include "std.h"
    
#undef EXTRA_RESET
#define EXTRA_RESET extra_reset();

#undef EXTRA_INIT
#define EXTRA_INIT extra_init();

#undef EXTRA_LONG
#define EXTRA_LONG    if (extra_long(str)) return 1;

object monster, note;

extra_reset() {
    if (!monster) {
	monster = clone_object("obj/monster");
	monster->set_name("half-finished monster");
	monster->set_alias("monster");
	monster->set_level(3);
	monster->set_wc(4);
	monster->set_al(0);
	monster->set_short("A half-finished monster");
	monster->set_long("This is a monster that the Wizard seems to still be working on.\n" +
			  "It has no legs, and only one arm.\n" +
			  "Parts of it are still stored in big glass jars on the table.\n");
	monster->set_aggressive(1);
	monster->set_spell_mess1("The half-finished monster says: Error! Brain not yet inserted.");
	monster->set_spell_mess2("The half-finished monster says: Error! Brain not yet inserted.");
	monster->set_chance(50);
	move_object(monster, this_object());
    }
    
    if (!note || !present(note)) {
	note = clone_object("players/padrone/obj/thing");
	note->set_name("note");
	note->set_alias("paper");
	note->set_short("A note");
	note->set_can_get(1);
	note->set_weight(1);
	note->set_value(1);
	note->set_read_file("/players/padrone/tower/hatnote.txt");
	move_object(note, this_object());
    }
} /* extra_reset */

extra_init() {
    add_action("read", "read");
} /* extra_init */


TWO_EXIT("players/padrone/tower/hall", "west",
	 "players/padrone/tower/garbage_room", "east",
	 "Laboratory",
	 "This is the Wizard's laboratory,\n" +
	 "where he performs his strange and mysterious experiments.\n" +
	 "Tables and shelves are packed with strange and mysterious equipment,\n" +
	 "from test tubes and ancient spellbooks to oscilloscopes and computers.\n" +
	 "A small door leads east. There is a sign on the door.\n", 1)
  
  
read(str) {
    if (str == "sign") {
	write("The sign reads 'GARBAGE ROOM'.\n");
	return 1;
    }
    else
	return 0;
}

extra_long(str) {
    if (str == "sign") {
	write("The sign reads 'GARBAGE ROOM'.\n");
	return 1;
    }
    else if (str) {
	write("Well, there is so much junk in this room that there probably is\n" +
	      "a " + str + " somewhere, but you have no chance of finding it!\n");
	return 1;
    }
    else
	return 0;
}

id(str) {
    return str;
}
