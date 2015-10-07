#include "std.h"

TWO_EXIT("players/morgar/underworld/entry", "east",
         "players/morgar/underworld/chasm", "down",
         "Brink of a chasm",
         "You are near the eastern end of a large underground cavern, but you\n" +
         "are prevented from going west by a large chasm.  It is completely\n" +
         "dark here.  In the distace you can hear an eerie drip, drip, drip\n" +
         "of water.  It looks as though it would be possible to climb down\n" +
         "here.  You are uneasy about doing so, however, as you feel that a\n" +
         "great evil lies below you.\n", 0)

realm() { return("under"); }
