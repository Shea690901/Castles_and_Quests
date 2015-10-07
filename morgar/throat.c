/* This is the object file for the sore throat */

short() { return "Sore throat"; }

long(str) { write("This is what you get for shouting too much.\n"); }

init() {
    add_action("try_shout"); add_verb("shout");
    add_action("quit"); add_verb("quit");
}

id(str) { return str == "throat"; }

add_weight() { return; }

query_value() { return; }

try_shout() {
    write("You can't shout with a sore throat!\n");
    say(call_other(this_player(), "query_name") + " makes croaking sounds.\n");
    return 1;
}

get() { return 1; }

drop() { return 1; }

quit() {
    destruct(this_object());
    call_other(this_player(), "quit");
}
