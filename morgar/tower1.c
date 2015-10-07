#include "std.h"

id(str) { return str == "view" || str == "window"; }

#undef EXTRA_LONG
#define EXTRA_LONG\
    if (str == "view" || str == "window") {\
        write("You see a spectacular view of the plains and mountains.\n");\
        return;\
    }

THREE_EXIT("players/morgar/tower2","up",
	 "players/morgar/pentagram","east",
	 "players/morgar/hall", "down",
	 "Tower, second floor",
	 "The second level of the tower of the gates.  There is an ornately\n" +
	 "embelleshed pentagram on the floor in an alcove to the east.\n" +
	 "There is a beautiful view of the forests and montains out the\n" +
	 "windows.\n", 1)
