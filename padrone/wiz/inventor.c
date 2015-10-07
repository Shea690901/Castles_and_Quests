/* This is the inventor, that prints an extended inventory of things */

status longflag, zellskiflag;
object current_environment;

short() {
    return "An inventor";
}

long() {
    write("This is the inventor, a small but sometimes very useful magic item.\n" +
	  "With this tool you can see EVERYTHING contained in another item.\n" +
	  "The inventor understands three commands: inventory, long-inventory\n" +
	  "and zellski-inventory (or inv, li and zi).\n" +
	  "You can give arguments, even of the type 'bag in corpse in harry'.\n");
}

init() {
    add_action("short_inventory", "inventory");
    add_action("short_inventory", "invent");
    add_action("short_inventory", "inv");
    add_action("long_inventory", "long-inventory");
    add_action("long_inventory", "long-invent");
    add_action("long_inventory", "long-inv");
    add_action("long_inventory", "li");
    add_action("zellski_inventory", "zellski-inventory");
    add_action("zellski_inventory", "zellski-inv");
    add_action("zellski_inventory", "z-inv");
    add_action("zellski_inventory", "zi");
}

id(str) {
    return str == "inventor";
}

reset(arg) {

}

short_inventory(str) {
    if (!wizcheck())
	return 1;
    longflag = 0;
    zellskiflag = 0;
    inventory(str);
    return 1;
}

long_inventory(str) {
    if (!wizcheck())
	return 1;
    longflag = 1;
    zellskiflag = 0;
    inventory(str);
    return 1;
}

zellski_inventory(str) {
    if (!wizcheck())
	return 1;
    longflag = 0;
    zellskiflag = 1;
    inventory(str);
    return 1;
}

wizcheck() {
    if (this_player()->query_level() < 20) {
	write("The inventor says \"fzzzzzzzt\" and nothing happens.\n");
	write("You guess that it can only be used by wizards.\n");
	return 0;
    }
    return 1;
}
inventory(str) {
    object obj;

    if (!str) {
	obj = environment(this_player());
	inventory_of_object(obj);
	return 1;
    }
    current_environment = environment(this_player());
    if (sneak_in(str) != -1)
	inventory_of_object(current_environment);
    return 1;
} /* inventory */

query_weight() { return 1; }

get() { return 1; }

query_value() { return 10; }

inventory_of_object(mama_obj) {
    object an_obj, this_obj;
    int nr;
    string namestring, shortstring, the_creator;

    if (zellskiflag) {
	write("Inventory of ");
	write(mama_obj);
	write(":\n");
    }
    else
	write("Inventory of " + mama_obj->short() + ":\n");

    an_obj  = first_inventory(mama_obj);
    nr = 0;
    while (an_obj) {
	this_obj = an_obj;
	an_obj = next_inventory(an_obj);
	write("    " + nr + ": ");

	if (zellskiflag) {
	    write(this_obj);
	}
	else {
	    namestring = call_other(this_obj, "query_name");
	    if (namestring)
		write(namestring);
	    else
		write("NO NAME");
	    write(" (");
	    shortstring = call_other(this_obj, "short");
	    if (shortstring)
		write(shortstring);
	    else
		write("NO SHORT DESCRIPTION");
	    write(")");
	}

	the_creator = creator(this_obj);
	write(" -- " + the_creator);
	write("\n");
	if (longflag) {
	    call_other(this_obj, "long");
	    write("\n");
	}
	nr = nr + 1;
    } /* while */
} /* inventory_of_object */

sneak_in(str) {
    string outer, inner;
    object the_obj;

    /* write("entering sneak_in(" + str + ")\n"); */


    if (sscanf(str, "%s in %s", inner, outer) == 2) {
        if (sneak_in(outer) == -1)
	    return -1;
    }
    else
	inner = str;

    /* write("present(" + inner + ", ...)\n"); */

    the_obj = present(inner, current_environment);
    if (the_obj)
	current_environment = the_obj;
    else {
	write("Couldn't find " + inner + " in " +
	      call_other(current_environment, "short") + ".\n");
	return -1;
    }

    /* write("leaving sneak_in(" + str + ")\n"); */
    return 0;
} /* sneak_in */
