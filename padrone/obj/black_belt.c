/* black_belt.c */

inherit "obj/armour";

object player;

init() {
    ::init();
    add_action("kick", "kick");
}

int kick_number;

reset(arg) {
    ::reset(arg);
    if (!arg) {
	/* First reset */
	set_name("black belt");
	set_alias("belt");
	set_type("belt");
	set_short("A black belt");
	set_long("This is a black belt made of satin.\n");
	set_ac(1);
	set_value(10);
	set_weight(1);
	kick_number = 0;
    }
    else {
	/* Periodical reset */
    }
} /* reset */

wear(str) {
    status was_worn;
    int wear_res;

    was_worn = (worn_by == this_player());
    wear_res = ::wear(str);
    if (!was_worn && (worn_by == this_player()))
	write("You feel inspired to try some kicking...\n");
    return wear_res;
} /* wear */

kick(str) {
    object who;
    string kicktype, cap_name;

    if (worn_by != this_player())
	return 0;

    cap_name = this_player()->query_name();
    if (!str) {
	say(cap_name + " shows an excellent karate kick.\n");
	write("You show an excellent karate kick.\n");
	return 1;
    }
    who = present(lower_case(str), environment(this_player()));
    if (!who)
	return 0;
    if (!living(who)) {
	say(cap_name + " kicks the " + str + ".\n");
	write("You kick the " + str + ".\n");
	return 1;
    }
    str = capitalize(str);
    if (who == this_player()) {
	say(cap_name + " kicks " + str + ". What a stupid thing to do!\n");
	write("You kick yourself. What a stupid thing to do!\n");
	return 1;
    }
    kick_number += 1;
    if (kick_number > 9)
	kick_number = 1;
    if (kick_number == 1)
	kicktype = "";
    else if (kick_number == 2)
	kicktype = " with a hard kick";
    else if (kick_number == 3)
	kicktype = " with a very hard kick";
    else if (kick_number == 4)
	kicktype = " with a bone-crushing sound";
    else if (kick_number == 5)
	kicktype = " with a flying kick";
    else if (kick_number == 6)
	kicktype = " with a horse kick";
    else if (kick_number == 7)
	kicktype = " with a combat kick";
    else if (kick_number == 8)
	kicktype = " unusually hard";
    else if (kick_number == 9)
	kicktype = " with a sickening KLOFF";
    tell_object(who, cap_name + " kicks you" + kicktype + ".   OUCH!!\n");
    say(cap_name + " kicks " + str + kicktype + ".\n", who);
    write("You kick " + str + kicktype + ".\n");
    return 1;
} /* kick */
