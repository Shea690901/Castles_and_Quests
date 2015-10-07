#include "std.h"

#undef EXTRA_MOVE1
#define EXTRA_MOVE1  if (extra_move1()) return 1;

#undef EXTRA_MOVE3
#define EXTRA_MOVE3  if (extra_move3()) return 1;

extra_move1() {
    object guest;

    guest = call_other("players/padrone/inside/e_guest", "query_occupied");
    if (guest) {
	write("Sorry, that room is occupied by " +
	      guest->query_name() + ".\n");
	write("You'll have to wait outside.\n");
	return 1;
    }
    else
	return 0;
} /* extra_move1 */

extra_move3() {
    object conf;

    conf = call_other("players/padrone/inside/conf_room", "query_closed");
    if (conf) {
	write("Sorry, the conference room is currently occupied.\n");
	write("You'll have to wait outside.\n");
	return 1;
    }
    else
	return 0;
} /* extra_move3 */


THREE_EXIT("players/padrone/inside/e_guest", "north",
	   "players/padrone/inside/m_uhall", "west",
	   "players/padrone/inside/conf_room", "east",
	   "Upper hall",
	   "You are in the east end of the upper hall.\n" +
	   "The East Guestroom is to the north, and the hall extends to the west.\n" +
	   "The Conference Room is to the east.\n", 1)
