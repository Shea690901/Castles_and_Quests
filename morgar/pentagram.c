#include "std.h"

#undef EXTRA_RESET

#define EXTRA_RESET extra_reset();

ONE_EXIT("players/morgar/tower1","west",
	 "Pentagram",
         "You are standing inside of an ornate pentagram.\n", 1)

extra_reset() {
    object book;
    if (!present("book")) {
        book=clone_object("players/morgar/book");
        move_object(book,this_object());
    }
}
