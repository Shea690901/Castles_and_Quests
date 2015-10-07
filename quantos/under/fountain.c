/* #include "std.h" /Pell */

reset(arg) {
    if(!arg)
	set_light(1);
    extra_reset();
}

object elemental, money, trident;

extra_reset() {
    if (!elemental || !living (elemental)) {
	elemental = clone_object ("obj/monster");
	call_other (elemental, "set_name", "elemental");
	call_other (elemental, "set_alias", "water elemental");
	call_other (elemental, "set_race", "elemental");
	call_other (elemental, "set_short", "A water elemental");
	call_other (elemental, "set_level", 15);
	call_other (elemental, "set_hp", 250);
	call_other (elemental, "set_wc", 16);
	call_other (elemental, "set_al", -250);
	call_other (elemental, "set_aggressive", 1);
	move_object (elemental, this_object());
#if 0 /* But Quantos! What would an elemental do with money? Eh? :) /Pell */
	money = clone_object ("obj/money");
	call_other (money, "set_money", 250 + random(250));
	move_object (money, elemental);
#endif
	trident = clone_object ("obj/weapon");
	call_other (trident, "set_name", "Neptune's trident");
	call_other (trident, "set_alias", "trident");
	call_other (trident, "set_short", "An ice-blue trident");
	call_other (trident, "set_long", /* Pell */
"The trident feels very cool to your touch. You somehow feel that it\n" +
"doesn't like flaming creatures, like demons.\n"); /* Pell */
	call_other (trident, "set_alt_name", "fireslicer");
	call_other (trident, "set_class", 14);
	call_other (trident, "set_weight", 3);
	call_other (trident, "set_value", 2100);
	call_other (trident, "set_hit_func", this_object());
	move_object (trident, elemental);
    }
}

init() {
    add_action ("exitn"); add_verb ("exit");
    add_action ("down"); add_verb ("down");
    add_action ("down"); add_verb ("dive"); /* Pell */
}

exitn() {
 call_other (this_player(), "move_player", "out#players/quantos/under/maze159");
 return 1;
}

down() {
    write ("You enter a long underwater tunnel, and the current drags you along!\n");
    call_other (this_player(), "move_player", "down#room/sea");
    return 1;
}

long() {
    write ("You are swimming in the fountain. The green light seems much\n");
    write ("more intense now. There is a light suction tugging at your\n");
    write ("feet, and the water is frothing a bit more than is normal.\n");
}

short() {
    return "In the fountain";
}

weapon_hit(attacker) {
    if (call_other (attacker, "id", "fire elemental") ||
	call_other(attacker, "id", "demon") ||
	call_other(attacker, "id", "red dragon")) {
	write ("The trident of Neptune cools the flames of your foe.\n");
	return 10;
    }
    return 0;
}
