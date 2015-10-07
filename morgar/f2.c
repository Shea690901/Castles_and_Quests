id(arg) {return arg=="facade";}

short() {
    return "The magic shop is to the west";
}

long() {
    write("This is a facade.\n");
}

init() {
    add_action("move"); add_verb("west");
}

move(str) {
    call_other(this_player(), "move_player", "west#players/morgar/magic");
    return 1;
}

get() {
    /* Change by Padrone: */
    if (this_player()->query_level() >= 20)
      write("Stop that immediately! Don't try to carry away the magic shop!\n");
    return 0;
}

reset(arg) {
    if (arg)
        return;
    move_object(this_object(), "room/yard");
}
