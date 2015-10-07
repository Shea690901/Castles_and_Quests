/* secret_police/orders.c -- orders from the Secret Police about the Chaosdemon */

string owners_name;

id(str) {
    return    str == "sp_orders"
	   || str == "orders"
	   || str == "order"
	   || str == "secret orders"
	   || str == "secret order"
	   || str == "secret police orders"
	   || str == "police orders"
	   || str == "Secret Police orders";
}

init() {
    add_action("do_read", "read");
}

long() {
    int i;
    write("The orders are in a big, brown envelope:\n\n");
    write("    +-------------------------------------------------------------+\n" +
	  "    !                                                             !\n" +
	  "    !  Secret Federal Imperial Bureau of Domestic Investigations  !\n" +
	  "    !                    *** TOP SECRET ***                       !\n" +
	  "    !        Orders for temporary secret agent " + owners_name + ".");
    i = strlen(owners_name);
    while (i < 18) {
	write(" ");
	i += 1;
    }
    write("!\n");
    write("    !   WARNING: These orders will self-destruct after reading!   !\n");
    write("    !  Do not attempt to drop these orders, or to give them away. !\n" +
	  "    !                                                             !\n" +
	  "    +-------------------------------------------------------------+\n\n");
    write("If you want to read the orders, just 'read orders'.\n");
    write("But remember that you can only read them once!\n");
}

short() {
    return("Some secret orders from the Secret Police");
}

destruct_me() {
    write("Suddenly, the secret orders catch flame and turn to ashes!\n");
    say("Suddenly, the secret orders catch flame and turn to ashes!\n");
    destruct(this_object());
}

init_orders(n) {
    owners_name = capitalize(n);
} /* set_name */

get() {
    return 1;
}

drop() {
    call_out("destruct_me", 1);
    return 0;
}

query_value() {
    return 1;
}

do_read() {
    object lawbringer, env, castle;

    say(this_player()->query_name() + " reads the secret orders.\n");
    write("You read the secret orders.\n\n");

    write("    The wizard Padrone has captured a demon, called the Chaosdemon,\n" +
	  "    and keeps it imprisoned in his walking castle.\n" +
	  "    Your orders are to kill that demon, and to bring back its weapon,\n" +
	  "    the Chaosblade, to your commanding officer, the Captain.\n");
    write("    You will be rewarded.\n\n");

    write("    Further instructions:\n");
    write("    1. You need a special weapon, called the Lawbringer, to kill the demon.\n" +
	  "       It is known to have been stored in Padrone's treasury, and recent\n" +
	  "       intelligence reports indicate that it can be found");
    lawbringer = call_other("players/padrone/tower/vault", "return_lawbringer");
    if (!lawbringer) {
	write("\n       in the treasury in Padron's castle, in the forest west of the village");
    }
    else {
	env = environment(lawbringer);
	while (env) {
	    if (living(env))
		write("\n         carried by " + call_other(env, "short"));
	    else
		write("\n         inside " + call_other(env, "short"));
	    env = environment(env);
	}
    }
    write(".\n");

    write("    2. To be able to enter the cell were the demon is kept,\n" +
	  "       you need the panzer key that can be found in Padrone's treasury.\n");

    write("    3. According to secret information, the walking castle has been stolen\n" +
	  "       by pirates, and ");

    castle = find_object("players/padrone/walker/castle");
    if (castle)
	env = environment(castle);
    else
	env = 0;
    if (env) {
	write("was most recently seen in ");
	write(env->short());
	write(".\n");
    }
    else
	write("has not been seen for a while.\n");
	
    write("    4. Do not (repeat: NOT) try to use the demon's weapon.\n\n");

    write("              Signed: Otto von Bruto, Chief of the Secret Police\n");
    write("\n");

    call_out("destruct_me", 1);
    return 1;
} /* do_read */
