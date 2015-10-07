#define DEST "room/vill_shore"

id(str) { return str == "castle"; }

short() {
   return "To the south you can see the Castle of Angmar";
}

long() {
    write("This is the castle of Angmar.\n");
    write("Angmar, the necromancer, has not been seen in\n");
    write("this world for hundreds of years. Rumours say that\n");
    write("he is long dead. His castle, however, still stands\n");
    write("here as a monument of Evil, and it is quite possible\n");
    write("that the ghastly creatures conjured by Angmar still\n");
    write("lurks inside, guarding his immense riches.\n");
}


init() {
    add_action("south"); add_verb("south");
}

south() {
call_other(this_player(), "move_player", "into castle#players/angmar/castle/inside.c");
    return 1;
}

reset(arg) {
    object quest;
    if(arg) return;
    move_object(this_object(), DEST);
    quest=clone_object("obj/quest_obj");
    call_other(quest,"set_hint",
      "No adventurer can call himself adventurer if he hasn't\n"+
      "broken into Angmar's treasury!\n");
    call_other(quest,"set_name","angmar");
    quest->set_points(100);
    quest->set_short("Break into Angmar's treasury");
    move_object(quest,"room/quest_room");
}

