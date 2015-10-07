int charges,i;

id(str) {
       return str == "scroll";
        }


reset() {
       i=random(6);
       }

long() {
    write("A small magical scroll is here, it feels a bit evil.\n");
    }

short() {
     return "A small magical scroll";
}

query_value()
{
    return 100;
}

init() {
    add_action("read"); add_verb("read");
}

read(arg) {
    if (arg && arg != "scroll") {
       write("read what?\n");
    } else {

       write("As you reads the scroll everything shimmers away...\n");
    if (i == 1)
        call_other(this_player(), "move_player", "X#players/kantele/snake_pit");
    else
    if (i == 2)
        call_other(this_player(), "move_player", "X#room/church");
    else
    if (i == 3)
        call_other(this_player(), "move_player", "X#room/pub2");
    else
    if (i == 4)
        call_other(this_player(), "move_player", "X#room/giant_lair");
    else
    if (i == 5)
        call_other(this_player(), "move_player", "X#players/kantele/bar");
        else
        call_other(this_player(), "move_player", "X#players/kantele/on_roof");
    move_object(this_object(), "players/kantele/store");
    write("The scroll suddenly disappears !\n");
    return 1;
}
}

get() {
    return 1;
}

query_weight() {
    return 1;
}
