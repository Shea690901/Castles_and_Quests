#include "std.h"

id(str) {
    return str == "bed" || str == "waterbed" || str == "water bed";
}

#undef EXTRA_LONG
#define EXTRA_LONG \
    if (id(str)) { \
	write("It looks very comfortable, but don't bother searching in it.\n" + \
	      "There are no rings of healing in this bed.\n" + \
	      "Try Kitiara's bed, in Kantele mansion, instead...\n"); \
	return; \
    }

THREE_EXIT("players/padrone/tower/hall", "north",
	   "players/padrone/tower/wardrobe", "east",
	   "players/padrone/tower/poolroom", "northwest",
	   "Bedroom",
	   "You are now in the Wizard's bedroom.\n" +
	   "The light is soft, the carpets are thick, the furniture is luxurious,\n" +
	   "and in the middle of the room there is a huge waterbed with down pillows.\n" +
	   "You are lucky, because it seems like the Wizard is not here.\n" +
	   "If he had been, he would surely have transformed you into a newt\n" +
	   "for this unprecedented intrusion!\n" +
	   "To the east a door leads into a wardrobe.\n", 1)
