#define NAME "quantos"
#define DEST "room/forest2"
/*
 * This is just the facade to a castle. If you want to enable the
 * "enter" command, move the player to a hall or something (which
 * you have to desert/design yourself).
 * The predefined string DEST is where a player should come when he
 * leaves the castle.
 *
 * This file is loaded automatically from "init_file". We have to move
 * ourself to where we are supposed to be.
 */

id(str) { return str == "castle"; }

short() {
    return("To the north, the trees grow sparse. You can see sand dunes\n" +
    "through the branches. There is a new sign here");
}

long() {
    write("-------------------------------------------------------------------\n");
    write("|           W E L C O M E   T O   D E S E R T W O R L D           |\n");
    write("|                                                                 |\n");
    write("|      Just north of this area lies a relatively new realm :      |\n");
    write("|      DESERTWORLD! A world of adventure and excitement, with     |\n");
    write("|      *all-new* *all-different* monsters and treasures to be     |\n");
    write("|      seen. And if you happen to get thirsty during your         |\n");
    write("|      stay, feel free to check out the *BRAND NEW* oasis,        |\n");
    write("|      just two steps to the north and one to the east!           |\n");
    write("|                                                                 |\n");
    write("|      Enjoy your stay!                       The Management      |\n");
    write("-------------------------------------------------------------------\n");
}

init() {
    add_action("move"); add_verb("north");
    add_action("read"); add_verb("read");
    add_action("read"); add_verb("look");
}

move() {
    object ob;
    call_other(this_player(),"move_player", "north" + "#" + "players/quantos/desert/des_ent");
    return 1;
}

read(str) {
    if (str == "sign" || str == "at sign") {
	long();
	return 1;
    }
}

enter(str) {
    if (!id(str))
	return 0;
    call_other(this_player(),"move_player" ,"into the desert#players/quantos/desert/des_ent"); /* Pell */
    return 1;
}

reset(arg) {
    if (arg)
	return;
    move_object(this_object(), DEST);
}
