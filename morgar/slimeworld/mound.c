#include "std.h"

THREE_EXIT("players/morgar/slimeworld/entry", "south",
	 "players/morgar/slimeworld/desolate_n", "east",
	 "players/morgar/slimeworld/ruins", "west",
	 "A low mound",
	 "You are on a low mound of spongy soil.  From here you can see\n" +
         "a stinky cesspool to the south, a ruined temple to west, and\n" +
         "desolation to the east.\n", 1)

realm() {
    return("slime");
}
