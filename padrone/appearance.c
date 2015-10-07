/* A description. Like Adam's faces! */

string description;

id(str) {
    return str == "appearance";
} /* id */

long(str) {
    write(extra_look() + ".\n");
} /* long */

/* Set the description string. */
set_description(d) {
    string a, b;
    if (sscanf(d, "%s^!%s", a, b) == 2)
	d = a;	/* If someone makes a description with ^! in it... */
    description = d;
} /* set_description */

/* It is auto-loading, and the description string is always the same. */
query_auto_load() {
    object env;
    env = environment(this_object());
    if (!living(env) || env->is_npc())
	return 0;
    else
	return "players/padrone/obj/appearance" + ":" + description;
} /* query_auto_load */

/* Set the description string from the auto-load. */
init_arg(d) {
    description = d;
} /* init_arg */

/* It cannot be dropped. */
drop() {
    return 1;
} /* drop */

/* This will be printed when looking at the player! */
extra_look() {
    object env;
    string pronoun;

    pronoun = environment(this_object())->query_pronoun();
    if (!pronoun)
	return 0;
    else
	return capitalize(pronoun) + " " + description;
} /* extra_look */
