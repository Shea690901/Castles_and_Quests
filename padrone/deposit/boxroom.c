/*  boxroom.c -- where we store the safe-deposit boxes
 *  NOTE: To work in 2.0 and later, this room has to be in /room or /obj!
 *	Thomas Padron-McCarthy (Padrone), padrone@lysator.liu.se, 1990
 *	Share and enjoy! No rights reserved except the right to reserve rights.
 *	This file latest updated February 9, 1991 by Padrone.
 */

/* This room is in /room or /obj: */
#include "std.h"
#include "../players/padrone/deposit/deposit.h"

/* A player name + an amount of gold coins on each line: */
string client_list;
/* Used to return true if adjust_list found the player in the list: */
status found_player;

/*  The function "save_this_room" saves this room on two files, both
 *  "/room/boxroom.o" and "/room/boxroom.bak.o".
 *  If there is a crash, and "/room/boxroom.o" is reset or damaged,
 *  then "/room/boxroom.bak.o" should still be usable.
 *  But to stop both files from being overwritten by corrupted data
 *  after a crash, "save_this_room" will only work if the variable
 *  "safe_guard" has the value "Everything is OK.".
 *
 *  What to do if the save files are damaged and the "safe_guard"
 *  warning is printed:
 *	1. Try to find and old save file.
 *	2. Compare to the log file ("/log/padrone.deposit"),
 *	   and, if necessary, use the commands "depositstat" and
 *	   "adjust" in this room.
 */
string safe_guard;

#undef EXTRA_RESET
#define EXTRA_RESET extra_reset(arg);

#undef EXTRA_INIT
#define EXTRA_INIT extra_init();

safe_guard_warning(str) {
    write("*** Error in the deposit box service (in " + str + ").\n");
    write("*** Please ask a wizard to fix it (look in \"/room/boxroom.c\").\n");
    log_file(LOGFILE, ctime(time()) + ": safe_guard: Error in " + str + ".\n");
    log_file(LOGFILE, ctime(time()) + ": client_list = '" + client_list + "'\n");

} /* safe_guard_warning */

save_this_room() {
    if (safe_guard != "Everything is OK.") {
        safe_guard_warning("save_this_room");
	return;
    }
    save_object(BOXROOM);
    save_object(BOXROOM + ".bak");
}

extra_reset(arg)
{
    if (!arg) {
	client_list = "";
	safe_guard = "Not OK.";
	restore_object(BOXROOM);
	if (safe_guard != "Everything is OK.") {
	    /* Oops - save file was corrupted. Try to load the backup file! */
	    log_file(LOGFILE, ctime(time()) + ": Save file corrupted - trying to load backup file.\n");
	    restore_object(BOXROOM + ".bak");
	    if (safe_guard != "Everything is OK.") {
		/* The backup file was damaged too! */
		safe_guard_warning("extra_reset");
	    }
	}
    }
}

extra_init()
{
    add_action("cmd_depositstat", "depositstat");
    add_action("cmd_adjust", "adjust");
}


/*  This function updates the entry in client_list of the player
 *  with the name client_name (always capitalized!),
 *  by adding the amount adjustment to the amount in the entry.
 *  If the player has no entry, a new entry is (silently) created.
 *  If the list is in an illegal format, it is reset.
 */
adjust_list(client_name, adjustment)
{
    string new_list, rest_of_list, a_player;
    int res, a_value, value_from_list, sum;

    /* log_file(LOGFILE, "Adjusting: " + client_name + " " + adjustment + "\n"); -- just for debugging! */

    rest_of_list = client_list;
    new_list = "";
    found_player = 0;
    /* found_player is a global variable, used to return a found-flag */
    value_from_list = 0;

    while (!found_player && rest_of_list != "") {

	res = sscanf(rest_of_list, "%s %d\n%s",
		     a_player, a_value, rest_of_list);

	if (res == 2)
	    rest_of_list = "";
	else if (res != 3) {
	    write("*** Error. The list of clients was corrupt, and has been reset.\n");
	    log_file(LOGFILE, ctime(time()) + ": ERROR! Corrupt client_list ( " +
		     res + "): '" + client_list + "'\n");
	    client_list = "";
	    save_this_room();
	    return -1;
	}

	if (a_player == client_name) {
	    /* Found it! */
	    value_from_list = a_value;
	    new_list = new_list + rest_of_list;
	    found_player = 1;
	}
	else
	    new_list = new_list + a_player + " " + a_value + "\n";
    } /* while entries left in new_list */

    sum = value_from_list + adjustment;
    new_list = new_list + client_name + " " + sum + "\n";
    client_list = new_list;

    /* save_object(BOXROOM); -- No! Do it when we are finished! */
    return sum;
} /* adjust_list */


/*  Check if the player named client_name (always capitalized!)
 *  is in the list of clients. Return 1 or 0.
 */
is_client(client_name)
{
    string format, b, a;
    int v;

    format = client_name + " %d\n";
    if (sscanf(client_list, format,  v) == 1)
	return 1;
    format = "%s" + client_name + " %d\n";
    if (sscanf(client_list, format, b, v) == 2)
	return 1;
    return 0;
} /* is_client */


/*  Return the box of the player named client_name (always capitalized!).
 *  If the box has disappeared, and the player is in the client list,
 *  then (silently) create a new box.
 *  If no box present, and the player is not in the client list, return 0.
 */
find_my_box(client_name, verbose)
{
    object the_box;

    client_name = this_player()->query_name();
    if (client_name == "Someone") {
	write("Sorry. We cannot help invisible clients. Have a nice day.\n");
        return 0;
    }
    the_box = present("box-of-" +  lower_case(client_name));
    if (!the_box) {
	if (is_client(client_name)) {
	    write("Oh. There was a big hole in that box. Some items may have been lost...\n");
	    the_box = make_my_box(client_name);
	}
	else if (verbose) {
	    write("I am sorry, but we do not have a deposit box under that name. Goodbye.\n");
	}
    }
    return the_box;
} /* find_my_box */


/*  Make a box for a client named client_name,
 *  and put that box in the boxroom.
 *  Do not touch the list of clients in this function.
 *  The box is returned.
 */
make_my_box(client_name)
{
    object the_box;

    if (present("box-of-" + lower_case(client_name))) {
	write("Error. You already have a box. This cannot happen!\n");
	return 0;
    }
    the_box = clone_object("players/padrone/deposit/box");
    the_box->set_owner(lower_case(client_name));
    move_object(the_box, this_object());
    return the_box;
} /* make_my_box */


rent()
{
    object the_money;
    string client_name;

    client_name = this_player()->query_name();

    if (client_name == "Someone") {
	write("Sorry. We cannot help invisible clients.\n");
        return 1;
    }
    if (this_player()->query_money() < FEE) {
	write("But you don't have " + FEE + " gold coins.\n");
	return 1;
    }
    if (find_my_box(client_name, 0)) {
	write("But you already have a box. You cannot rent another!\n");
	return 1;
    }

    log_file(LOGFILE, ctime(time()) + ": " + client_name + " rented a box for " + FEE + " coins.\n");

    adjust_list(client_name, 0);
    make_my_box(client_name);
    write("You pay " + FEE + " gold coins.\n" +
	  "You now have access to a personal maximum-security safe-deposit box.\n" +
	  "The management wishes to congratulate you on a wise choice,\n" +
	  "and hopes that your future dealings with this establishment\n" +
	  "will turn out to be perfectly to your liking.\n");
    this_player()->add_money(-FEE);
    if (this_player()->query_level() < 20) {
	the_money = clone_object("obj/money");
	the_money->set_money(FEE);
	call_other("players/padrone/walker/cell", "put_in_vault", the_money);
    }
    save_this_room();
    return 1;
} /* rent */


complain()
{
    string client_name;
    int list_val, box_val, comp;
    object the_box;

    client_name = this_player()->query_name();
    say("You notice that " + client_name + " files a complaint.\n");
    log_file(LOGFILE, ctime(time()) + ": " + client_name + " complained.\n");
    if (client_name == "Someone") {
	write("Sorry. We cannot help invisible clients.\n");
        return 1;
    }
    if (is_client(client_name)) {
	list_val = adjust_list(client_name, 0);
	write("Yes, you are in our list of clients, and we have your box here.\n");
	the_box = find_my_box(client_name, 1);
	box_val = the_box->query_boxvalue();
	write("It says here that you have stored items to a value of " +
	      list_val + " gold coins,\n");
	write("and your box contains items to a value of " +
	      box_val + " gold coins.\n");
	comp = list_val - box_val;
	if (comp < 0) {
	    write("Strange. This should never happen...\n");
	    log_file(LOGFILE, ctime(time()) + ": ERROR: box_val (" + box_val + ") > list_val (" +
                     list_val + ") for " + client_name + "\n");
	    adjust_list(client_name, -comp);
	}
	else if (comp > 0) {
	    write("It looks like we have lost some of your items.\n");
	    write("You are entitled to " + comp + " gold coins in compensation.\n");
	    write("The management is very sorry that this has happened,\n" +
		  "but, nevertheless, wishes to express their genuine interest\n" +
		  "in the welfare of the clients.\n");
	    write("The compensation has now been paid to you.\n");
	    log_file(LOGFILE, ctime(time()) + ": " + client_name + " got " + comp + " in compensation.\n");
	    this_player()->add_money(comp);
	    adjust_list(client_name, -comp);
        }
	else {
	    write("According to our files, you are not entitled to any compensation.\n");
        }
	save_this_room();
        return 1;
    }
    write("Sorry, but you are not in our list of clients.\n");
    return 1;
} /* complain */


list_my_box(item_string)
{
    string client_name;
    object the_box, the_item;

    client_name = this_player()->query_name();
    the_box = find_my_box(client_name, 1);
    if (!the_box)
	return 1;
    the_item = first_inventory(the_box);
    if (the_item)
	write("The contents of your box:\n");
    else
	write("Your box is empty.\n");
    while(the_item) {
	write(the_item->short() + ".\n");
	the_item = next_inventory(the_item);
    }
} /* list_my_box */


/*  Stores the (single!) item the_item in the box the_box.
 *  It returns the value of that object (or MAX_INSURANCE).
 *  If it wasn't stored (or if it had no value!), 0 is returned.
 */
store_one_item(the_item, the_box, verbose) {
    string item_short, client_name;
    int weight, value;

    if (the_item->drop()) {
	if (verbose)
	    write("I can't take it from you!\n");
	return 0;
    }
    client_name = this_player()->query_name();
    weight = the_item->query_weight();
    this_player()->add_weight(-weight);

    item_short = the_item->short();
    /* log_file(LOGFILE, "store: " + client_name + " " + item_short + "\n"); -- just for debugging! */

    move_object(the_item, the_box);
    say(capitalize(client_name) + " stores " + item_short + ".\n");
    write("You store " + item_short + ".\n");

    value = the_item->query_value();
    if (value > INSURANCE_LIMIT)
	value = INSURANCE_LIMIT;
    return value;
} /* store_one_item */


store_item(item_string)
{
    string client_name;
    object the_box, this_ob, ob;
    int adjustment, this_value;

    client_name = this_player()->query_name();
    the_box = find_my_box(client_name, 1);
    if (!the_box)
	return 1;
    if (item_string == "all") {
	adjustment = 0;
	ob = first_inventory(this_player());
	while(ob) {
	    this_ob = ob;
	    ob = next_inventory(ob);

	    this_value = store_one_item(this_ob, the_box, 0);
	    adjustment += this_value;
	}
    }
    else {
	this_ob = present(item_string, this_player());
	if (!this_ob) {
	    write("You don't have a " + item_string + ".\n");
	    return 0;
	}
	adjustment = store_one_item(this_ob, the_box, 1);
    }

    adjust_list(client_name, adjustment);
    save_this_room();
    write("Ok.\n");
    return 1;
} /* store_item */


/*  Retrieves the (single!) item the_item from the box the_box.
 *  It returns the value of that object (or MAX_INSURANCE).
 *  If it wasn't retrieved (or if it had no value!), 0 is returned.
 */
retrieve_one_item(the_item, the_box, verbose) {
    string item_short, client_name;
    int value;

    item_short = the_item->short();
    if (!this_player()->add_weight(the_item->query_weight())) {
	/* if (verbose) -- always! */
	write(item_short + ": You can't carry that much.\n");
	return 0;
    }
    client_name = this_player()->query_name();
    /* log_file(LOGFILE, "retrieve: " + client_name + " " + item_short + "\n"); -- just for debugging! */

    move_object(the_item, this_player());
    say(capitalize(client_name) + " retrieves " + item_short + ".\n");
    write("You retrieve " + item_short + ".\n");

    value = the_item->query_value();
    if (value > INSURANCE_LIMIT)
	value = INSURANCE_LIMIT;
    return value;
} /* retrieve_one_item */


retrieve_item(item_string)
{
    string client_name;
    object the_box, this_ob, ob;
    int neg_adjustment, this_value;

    client_name = this_player()->query_name();
    the_box = find_my_box(client_name, 1);
    if (!the_box)
	return 1;
    if (item_string == "all") {
	neg_adjustment = 0;
	ob = first_inventory(the_box);
	while(ob) {
	    this_ob = ob;
	    ob = next_inventory(ob);

	    this_value = retrieve_one_item(this_ob, the_box, 1);
	    neg_adjustment += this_value;
	}
    }
    else {
	this_ob = present(item_string, the_box);
	if (!this_ob) {
	    write("No such item in the box: " + item_string + ".\n");
	    return 0;
	}
	neg_adjustment = retrieve_one_item(this_ob, the_box, 1);
    }

    adjust_list(client_name, - neg_adjustment);
    save_this_room();
    write("Ok.\n");
    return 1;
} /* retrieve_item */


cmd_depositstat()
{
    write("The deposit status:\n");
    write(client_list);
    return 1;
} /* cmd_depositstat */


cmd_adjust(str) {
    string who, sum;

    if (!str || sscanf(str, "%s %d", who, sum) != 2)
	write("Syntax ERROR in adjust. Usage: adjust WHO AMOUNT\n");
    else {
	who = capitalize(who);
	adjust_list(who, sum);
	save_this_room();
	write("Ok.\n");
    }
    return 1;
} /* cmd_adjust */


ONE_EXIT(DEPOSIT, FROM_BOXROOM,
	 "Deposit Storage Room",
	 "This is the storage room for the deposit service.\n" +
         "Use the command \"depositstat\" here.\n", 1)
