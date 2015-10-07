
/* This is the re-setter (resetter) */

short() {
    return "A re-setter";
}

long() {
    write("This is the re-setter, a powerful magic item.\n" +
	  "It looks like a miniature dog, but, by exploiting secrets\n" +
	  "about how the world is made, it can produce astonishing results.\n");
}

init() {
    add_action("do_reset", "reset");
}

id(str) {
    return str == "re-setter" || str == "resetter";
}

reset(arg) {
    write("The re-setter barks: I got a reset with argument " + arg + "!\n");
    say("The re-setter barks: I got a reset with argument " + arg + "!\n");
}

do_reset(str) {
    object obj;

    if (call_other(this_player(), "query_level") < 20) {
	write("This very powerful magic item is for Wizards only.\n");
	return 1;
    }

    if (!str) {
	obj = environment(this_player());
	write("The re-setter resets the room: " +
	      call_other(obj, "short") + ".\n");
	call_other(obj, "reset", 1);
	return 1;
    }
    obj = present(str, this_player());
    if (obj) {
	write("The re-setter resets " +
	      call_other(obj, "short") + ".\n");
	call_other(obj, "reset", 1);
	return 1;
    }
    obj = present(str, environment(this_player()));
    if (obj) {
	write("The re-setter resets " +
	      call_other(obj, "short") + ".\n");
	call_other(obj, "reset", 1);
	return 1;
    }
    obj = find_living(str);
    if (obj) {
	write("The re-setter resets " +
	      call_other(obj, "short") + ".\n");
	call_other(obj, "reset", 1);
	return 1;
    }
    write("The re-setter couldn't find " + str + ".\n");
    return 1;
}

query_weight() { return 1; }

get() { return 1; }

query_value() { return 10; }





