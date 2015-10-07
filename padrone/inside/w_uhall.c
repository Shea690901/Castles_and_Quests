#include "std.h"

#undef EXTRA_MOVE1
#define EXTRA_MOVE1  if (extra_move1()) return 1;

#undef EXTRA_MOVE2
#define EXTRA_MOVE2  if (extra_move2()) return 1;

extra_move1() {
    object guest;

    guest = call_other("players/padrone/inside/w_guest", "query_occupied");
    if (guest) {
	write("Sorry, that room is occupied by " +
	      guest->query_name() + ".\n");
	write("You'll have to wait outside.\n");
	return 1;
    }
    else
	return 0;
} /* extra_move1 */

extra_move2() {
    object guest;

    guest = call_other("players/padrone/inside/bathroom", "query_occupied");
    if (guest) {
	write("Sorry, the bathroom is occupied by " +
	      guest->query_name() + ".\n");
	write("You'll have to wait outside.\n");
	return 1;
    }
    else
	return 0;
} /* extra_move2 */


THREE_EXIT("players/padrone/inside/w_guest", "north",
	   "players/padrone/inside/bathroom", "south",
	   "players/padrone/inside/m_uhall", "east",
	   "Upper hall",
	   "You are in the west end of the upper hall.\n" +
	   "The bathroom is to the south, and the West Guestroom is to the north.\n" +
	   "The hall extends to the east.\n", 1)
