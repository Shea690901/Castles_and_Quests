#include "std.h"

object smallsign, bigsign, note;

#undef EXTRA_RESET
#define EXTRA_RESET extra_reset(arg);

#undef EXTRA_INIT
#define EXTRA_INIT  extra_init();

extra_init() {
    add_action("do_say", "say");
    add_action("do_exit", "exit");
    add_action("do_exit", "out");
} /* extra_init */

do_exit() {
    this_player()->move_player("out#players/padrone/inside/courtyard");
    return 1;
}

do_say(str) {
    string version;

    /* say pmf version ... */

    if (sscanf(str, "pmf version %s", version) == 1) {
        log_file("padrone", ctime(time()) + ": "
                 + this_player()->query_name() +
		 " (level " + this_player()->query_level() +
                 ") is using pmf version " + version + ".\n");
    }
    return 0;
} /* do_say */

extra_reset(arg) {
    if (arg)
	return;

    smallsign = clone_object("players/padrone/obj/thing");
    smallsign->set_name("small sign");
    smallsign->set_alias("sign");
    smallsign->set_short("A small sign is nailed to the wall, just below the big one");
    smallsign->set_long("The sign is titled \"How to get pmf\".\nMaybe you should read it?\n");
    smallsign->set_read_file("/players/padrone/inside/pmf_smallsign.txt");
    smallsign->set_can_get(0);
    move_object(smallsign, this_object());

    note = clone_object("players/padrone/obj/thing");
    note->set_name("note");
    note->set_alias("note about pmf");
    note->set_short("A note about pmf");
    note->set_read_file("/players/padrone/inside/pmf_note.txt");
    note->set_can_get(1);
    note->set_weight(1);
    move_object(note, this_object());

    bigsign = clone_object("players/padrone/obj/thing");
    bigsign->set_name("big sign");
    bigsign->set_alias("sign");
    bigsign->set_short("A big sign is nailed to the wall, just above the small one");
    bigsign->set_long("The sign is titled \"About pmf - Padrone's MudFrontend\".\nMaybe you should read it?\n");
    bigsign->set_read_file("/players/padrone/inside/pmf_bigsign.txt");
    bigsign->set_can_get(0);
    move_object(bigsign, this_object());
} /* extra_reset */

ONE_EXIT("players/padrone/inside/courtyard", "northwest",
	 "PMF Office",
	 "You are in a small office in the Castle of Padrone.\n" +
         "It is the office of PMF Inc, and it is\n" +
         "furnished in a simple but tasteful style,\n" +
         "meaning that it is totally empty except for two signs\n" +
         "that have been nailed to the wall: a big one, and a small one.\n" +
         "You also see that someone has engraved the strange word\n" +
         "PMF_QUERY_VERSION\n" +
         "on the floor here. You have no idea what that means.\n", 1)
