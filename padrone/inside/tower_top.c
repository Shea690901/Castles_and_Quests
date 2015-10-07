#include "std.h"

#undef EXTRA_LONG
#define EXTRA_LONG if (id_view(str)) { look_at_view(); return 1; }

id_view(str) {
    return str == "view" || str == "the view";
}

id(str) {
    return id_view(str);
}

look_at_view() {
    object castle, env;

    say(this_player()->query_name() + " looks at the view from the tower.\n");
    write("You look at the view from the tower.\n");
    cat("/players/padrone/inside/tower_view.txt");
    castle = find_object("players/padrone/walker/castle");
    if (castle)
	env = environment(castle);
    else
	env = 0;
    if (env)
	write("    Far away, close to " + env->short() + ",\n" +
	      "    you think you can see a strange castle standing on two giant legs.\n");
} /* look_at_view */

ONE_EXIT("players/padrone/inside/tower3", "down",
	 "Top of the watchtower",
	 "You are standing at the top of the watchtower,\n" +
	 "the smaller of the two towers in Padrone's castle.\n" +
	 "Even though this tower is not as high as the main tower,\n" +
	 "which you can see across the castle yard,\n" +
	 "the view over the surrounding countryside is beautiful.\n" +
	 "Maybe you should look at the view?\n", 1)
