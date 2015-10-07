#include "../../../room/std.h"

#undef EXTRA_INIT
#define EXTRA_INIT	extra_init();

#undef EXTRA_LONG
#define EXTRA_LONG	if (extra_long(str)) return;

extra_init() {
    add_action("enter", "enter");
    add_action("type", "type");
}

extra_long(str) {
    if (nanny_id(str)) {
	write("This is the computer Nanny, a Sequent Balance 8000 equipped with 12\n" +
	      "ns32032 cpus, 10MB of RAM and 270MB of hard disk storage.\n" +
	      "It stands in a corner, and on one of the cabinets a hatch is open.\n" +
	      "It might even be possible to climb in.\n" +
	      "You notice a cable leading to a terminal.\n");
	return 1;
    }
    else if (console_id(str)) {
	write("This is a Facit Twist terminal. You notice a cable leading from\n" +
	      "the terminal to the computer Nanny. Obviously this terminal is\n" +
	      "used as console for Nanny.\n" +
	      "The screen says \"login:\". You might try to type something.\n");
	return 1;
    }
    else if (str) {
	write("Well, there is so much junk in this room that there probably is\n" +
	      "a " + str + " somewhere, but you have no chance of finding it!\n");
	return 1;
    }
    else
	return 0;
}


enter(str) {
    if (str && !nanny_id(str))
	return 0;
    call_other(this_player(), "move_player",
	       "into Nanny#players/padrone/lith/inside_nanny");
    return 1;
}

type(str) {
    if (!str) {
	write("You type nothing, and press RETURN.\n" +
	      "The terminal prints \"login:\".\n");
	return 1;
    }
    write("You try to login on Nanny as user " + str + ",\n" +
	  "but just as you get the \"Password:\" prompt\n" +
	  "you are sucked back into the computer!\n\n");
    call_other(this_player(), "move_player", "into the terminal#room/church");
    return 1;
}

nanny_id(str) {
    return str == "nanny" || str == "Nanny" || str == "cabinet" || str == "computer";
}

console_id(str) {
    return str == "console" || str == "terminal" || str == "console terminal";
}

id(str) {
    return str;
}

ONE_EXIT("players/padrone/lith/outside_lysator", "west",
	 "Lysator",
	 "This is Lysator, the Computer Club at the University of Link|ping,\n" +
	 "in Sweden. You are in a small cellar room with concrete walls. It\n" +
	 "is filled with computers from all ages. You notice a DEC-20, some\n" +
	 "Sun workstations, a Sequent machine labeled 'Nanny', and lots and\n" +
	 "lots of terminals. The noise from the cooling system is ear-shattering,\n" +
	 "but it is still very hot in here. And no wonder, with all those\n" +
	 "big machines running at full speed in this little room!\n" +
         "There is a terminal here.\n", 1)
