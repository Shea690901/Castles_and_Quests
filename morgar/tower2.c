#include "std.h"

id(str) { return str == "view" || str == "window"; }

#undef EXTRA_LONG
#define EXTRA_LONG\
    if (str == "view" || str == "window") {\
        write("You see a spectacular view of the plains and mountains.\n");\
        return;\
    }

THREE_EXIT("players/morgar/tower3","up",
	 "players/morgar/tower1", "down",
	 "players/morgar/balcony", "west",
	 "Tower, third floor",
         "The third floor of the tower of the gates.\n" +
	 "There is a beautiful view of the forests and montains from the\n" +
	 "western balcony.\n", 1)

