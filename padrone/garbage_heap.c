/* On Genesis and Nanny, this room is connected to Ingis' area */

#include "std.h"
#include "config.h"

#undef EXTRA_RESET
#define EXTRA_RESET extra_reset(arg);

extra_reset(arg) {

    if (!present("garbage", this_object())) {
	object p1;

	p1 = clone_object("obj/treasure");
	p1->set_id("piece of garbage");
	p1->set_alias("garbage");
	p1->set_short("A piece of garbage");
	p1->set_long("This is a worthless piece of garbage.\n");
	p1->set_weight(1);
	p1->set_value(0);
	move_object(p1, this_object());
    }
    if (!present("junk", this_object())) {
	object p2;

	p2 = clone_object("obj/treasure");
	p2->set_id("piece of junk");
	p2->set_alias("junk");
	p2->set_short("A piece of junk");
	p2->set_long("This is a worthless piece of junk.\n");
	p2->set_weight(1);
	p2->set_value(0);
	move_object(p2, this_object());
    }
} /* extra_reset */

#ifdef EXPORT

ONE_EXIT("players/padrone/vdb1", "west",	/* Not "outside" */
	 "Garbage heap",
	 "You are standing in an example of what unchecked pollution\n" +
	 "can do to the environment - the garbage heap behind Padrone's Castle!\n" +
	 "All sorts of useless junk has been dumped here, and the smell is\n" +
	 "horrible. This is NOT a nice place, and you only want to get outta here!\n", 1)

#else
  /* Not EXPORT, i. e. NANNY or GENESIS */

TWO_EXIT("players/padrone/vdb1", "west",	/* Not "outside" */
	 "players/ingis/twisting", "south",
	 "Garbage heap",
	 "You are standing in an example of what unchecked pollution\n" +
	 "can do to the environment - the garbage heap behind Padrone's Castle!\n" +
	 "All sorts of useless junk has been dumped here, and the smell is\n" +
	 "horrible. This is NOT a nice place, and you only want to get outta here!\n", 1)

#endif
