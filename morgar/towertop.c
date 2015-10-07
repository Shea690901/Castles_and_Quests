#include "std.h"

id(str) { return str == "view"; }

#undef EXTRA_LONG
#define EXTRA_LONG\
    if (str == "view" || str == "window") {\
        write("You see a spectacular view of the plains and mountains.\n");\
        return;\
    }

ONE_EXIT("players/morgar/tower3","down",
	 "Top of the tower",
	 "The roof of the tower of the gates.\n" +
	 "There is a beautiful view of the forests and mountains from here.\n" +
	 "Stairs lead back into the tower.\n", 1)
