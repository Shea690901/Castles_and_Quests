id(arg) {return arg=="facade";}

short() {
    return "A bridge crosses the riger to the east";
}

long() {
    write("This is a facade.\n");
}

init() {
    add_action("move"); add_verb("east");
}

move(str) {
    call_other(this_player(), "move_player", "east#players/morgar/bridge");
    return 1;
}

get() {
    return(call_other(this_player(),"query_level",0) >= 20);
}

reset(arg) {
    if (arg)
        return;
    move_object(this_object(), "room/plane9");
}
