#include "std.h"

id(str) { return str == "view" || str == "window"; }

#undef EXTRA_LONG
#define EXTRA_LONG\
    if (str == "view" || str == "window") {\
        write("You see a spectacular view of the plains and mountains.\n");\
        return;\
    }

#undef EXTRA_RESET
#define EXTRA_RESET\
    if (!present("amulet"))\
        move_object(clone_object("players/morgar/amulet"), this_object());

ONE_EXIT("players/morgar/tower2","east",
	 "A balcony",
	 "From this balcony you can see a great deal of the forest and town\n" +
	 "along with a spectacular view of the mountains.\n", 1)
