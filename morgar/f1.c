id(arg) {return arg=="facade";}

short() {
    return "The smithy is to the west";
}

long() {
    write("This is a facade.\n");
}

init() {
    add_action("move"); add_verb("west");
}

move(str) {
    call_other(this_player(), "move_player", "west#players/morgar/smithy");
    return 1;
}

get() {
    return(call_other(this_player(),"query_level",0) >= 20);
}

reset(arg) {
    if (arg)
        return;
    move_object(this_object(), "room/narr_alley");
}
