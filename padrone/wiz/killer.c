
/* This is the (silent) killer */

short() {
    return "A killing device";
}

long() {
    write("This is a killing device.\n" +
	  "It really looks horribly dangerous!\n" +
	  "There is some small red print on it.\n");
}

read(str) {
    if (!id(str) && str != "print" && str != "small print"
	&& str != "small red print" && str != "red print")
	return 0;
    write("It says 'Usage: zap [ monster ] [ hitpoints ]'.\n");
    return 1;
}

init() {
    add_action("do_kill", "zap");
    add_action("read", "read");
}

id(str) {
    return str == "killer" || str == "device" || str == "killing device";
}

reset(arg) {
}

do_kill(str) {
    object victim;
    string player_name, victim_name;
    int how_hard;

    if (this_player() != environment(this_object()))
	return 0;
    player_name = call_other(this_player(), "query_name");
    if (call_other(this_player(), "query_level") < 20) {
	write("This dangerous item is for Wizards only,\n" +
	      "and you only manage to shoot yourself in the foot.\n" +
	      "Luckily, you are not hurt.\n");
	say(player_name + " tried to operate the killing device,\n" +
	    "but failed and ended up just looking stupid.\n");
	return 1;
    }

    if (!str) {
	victim = call_other(this_player(), "query_attack");
	if (!victim) {
	    write("Yes, but who are you ging to kill?\n");
	    return 1;
	}
	how_hard = 1000;
    }
    else if (sscanf(str, "%d", how_hard) == 1) {
	victim = call_other(this_player(), "query_attack");
	if (!victim) {
	    write("Yes, but who are you ging to kill?\n");
	    return 1;
	}
    }
    else if (sscanf(str, "%s %d", victim_name, how_hard) == 2) {
	victim = present(victim_name, environment(this_player()));
    }
    else if (sscanf(str, "%s", victim_name) == 1) {
	victim = present(victim_name, environment(this_player()));
	how_hard = 1000;
    }
    if (!victim) {
	write("The killing device couldn't find \"" + victim_name + "\" here.\n");
	return 1;
    }
    if (victim == this_player()) {
	write("No. You'd better not.\n");
	return 1;
    }
    write("You hit " + call_other(victim, "query_name") +
	  " with a shockbolt of " + how_hard + " volts.\n");
    say(call_other(this_player(), "query_name") + " hit " +
	call_other(victim, "query_name") +
	" with a shockbolt of " + how_hard + " volts.\n");
    tell_object(victim, "You are hit by a shockbolt of " + how_hard + " volts.\n");
    tell_object(victim, "You are hit by a shockbolt of " + how_hard + " volts.\n");
    call_other(victim, "hit_player", how_hard);
    return 1;
} /* do_kill */

query_weight() { return 1; }

get() { return 1; }

query_value() { return 10; }
