/* This is the object file for the charm */
string following;
object target;
short() { return 0; }
long(str) { write("You are charmed.\n"); }
id(str) { return str == "charm"; }
add_weight() { return; }
query_value() { return; }
get() { return 1; }
drop() { return 1; }
quit() {
    destruct(this_object());
    call_other(this_player(), "quit");
}
startfollow(arg) {
    set_heart_beat(0);
    following=arg;
    target = find_living(following);
    set_heart_beat(1);
}
heart_beat() {
    if (!present(target,environment(environment(this_object())))) {
        tell_object(environment(this_object()),"You follow "+following+".\n");
        tell_room(environment(environment(this_object())),
            call_other(environment(this_object()), "query_name") +
            " follows " + following + "\n");
    move_object(environment(this_object()),environment(target));
        tell_room(environment(environment(this_object())),
            call_other(environment(this_object()), "query_name") +
            " arrives, following " + following + "\n");
}
}
query_stats() {
    if (following == 0) {
        write ("Not following anyone.\n");
        return 0;
    }
    write ("Following "+following+"\n");
    return 1;
}
