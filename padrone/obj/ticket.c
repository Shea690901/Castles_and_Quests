/* ticket.c -- a ticket to the Castle of Padrone */

int ticket_number;

short() {
    return "A ticket to the Castle of Padrone";
}

reset(arg) {
    if (!arg)
	ticket_number = random(1000) + 1000;
}

long(str) {
    if (!read(str))
        front();
}

front() {
    write("The ticket is printed on high-quality paper, and the front side says:\n");
    write("    +-------------------------------------------+\n" +
          "    |        THE  CASTLE  OF  PADRONE           |\n" +
          "    |    This ticket is valid for entrance.     |\n" +
          "    |          Price: 20 gold coins             |\n" +
          "    | Do not discard the ticket while inside!   |\n" +
          "    |  The Castle of Padrone is situated in     |\n" +
          "    | the beautiful forest west of the village: |\n" +
          "    |  past the troll, and south at the slope.  |\n" +
          "    +-------------------------------------------+\n");
    write("This ticket has number " + ticket_number + ".\n");
    write("There is something printed on the back side.\n");
} /* front */

back() {
    write("On the back side of the ticket there is a map:\n");
    write("    +-------------------------------------------+\n" +
          "    |       |      |        |                   |\n" +
          "    |   --SLOPE--FOREST--CLEARING---> Village   |\n" +
          "    |       |               |                   |\n" +
          "    |     FOREST                                |\n" +
          "    |       |                                   |\n" +
          "    |   --FOREST--FOREST--                      |\n" +
          "    |       |       |                           |\n" +
          "    |               V                           |\n" +
          "    |          The Castle                       |\n" +
          "    +-------------------------------------------+\n");
} /* back */

init() {
    add_action("read", "read");
}

front_id(str) {
    return    str == "front" || str == "front side" || str == "frontside"
           || str == "front of ticket" || str == "front side of ticket";
}

back_id(str) {
    return    str == "back" || str == "back side" || str == "backside"
           || str == "back of ticket" || str == "back side of ticket"
           || str == "backside of ticket";
}

ticket_id(str) {
    return str == "ticket" || str == "castle ticket";
}

id(str) {
    return ticket_id(str) || front_id(str) || back_id(str);
}

read(str) {
    if (ticket_id(str) || front_id(str)) {
        front();
        return 1;
    }
    else if (back_id(str)) {
        back();
        return 1;
    }
    else
        return 0;
} /* read */

get() { return 1; }
query_weight() { return 1; }
query_value() { return 20; }

set_ticket_number(n) { ticket_number = n; }
query_ticket_number(n) { return ticket_number; }
