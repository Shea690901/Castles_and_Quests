/* "players/padrone/obj/crystal_ball.c" -- a crystal ball with information about Lawbringer */

short() {
    return "A crystal ball";
}

long() {
    object lawbringer, env;

    write("This is a small, softly glowing crystal ball.\n" +
	  "As you look into it you see:\n");

    lawbringer = call_other("players/padrone/tower/vault", "return_lawbringer");
    if (!lawbringer) {
	write("    Nothing.\n");
	return;
    }
    write("    " + lawbringer->short());
    env = environment(lawbringer);
    while (env) {
	if (living(env))
	    write(",\n    carried by " + env->short());
	else
	    write(",\n    inside " + env->short());
	env = environment(env);
    }
    write(".\n");
    write("It seems as if this crystal ball has been stored in the same room\n" +
	  "as the mighty sword Lawbringer so long that it has been attuned to it.\n");
} /* long */

id(str) {
    return str == "crystal ball" || str == "ball";
}

query_weight() { return 2; }

get() { return !(environment(this_object())->stop_taking(this_object())); }

query_value() { return 100; }
