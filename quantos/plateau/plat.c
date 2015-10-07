/* #include "std.h" /Pell */

reset (arg) {
    if (!arg)
	set_light(1);
    extra_reset();
}

object rattler, money, rattle;

extra_reset() {
    if (!rattler || !living(rattler)) {
	rattler = clone_object ("obj/monster");
	call_other (rattler, "set_name", "snake");
	call_other (rattler, "set_alias", "rattlesnake");
	call_other (rattler, "set_race", "snake");
	call_other (rattler, "set_short", "A giant rattlesnake");
	call_other (rattler, "set_level", 12);
	call_other (rattler, "set_hp", 225);
	call_other (rattler, "set_wc", 12);
	call_other (rattler, "set_ac", 2);
	call_other (rattler, "set_al", -75);
	call_other (rattler, "set_aggressive", 1);
/*	call_other (rattler, "set_can_kill", 1); /Pell */
	call_other (rattler, "set_whimpy", 1);
	call_other (rattler, "set_move_at_reset", 1);
	call_other (rattler, "set_spell_mess1", "The snake tries to attack!"); /* Pell */
	call_other (rattler, "set_spell_mess2", "The snake crushes you!");
	call_other (rattler, "set_chance", 36);
	call_other (rattler, "set_spell_dam", 20);
	move_object (rattler, this_object());

#if 0	       	/* Money on a snake?? Sorry, Quantos... :) /Pell */
	money = clone_object ("obj/money");
	call_other (money, "set_money", random(300));
	move_object (money, rattler);
#endif
	rattle = clone_object ("obj/treasure");
	call_other (rattle, "set_id", "rattle");
	call_other (rattle, "set_short", "A rattlesnake's rattle");
	call_other (rattle, "set_value", 350);
	move_object (rattle, rattler);
    }
}

init() {
    add_action ("east"); add_verb ("east");
    add_action ("west"); add_verb ("west");
    add_action ("north"); add_verb ("north");
    add_action ("south"); add_verb ("south");
}

east() {
    call_other (this_player(), "move_player", "east#players/quantos/desert/gulch3");
    return 1;
}

west() {
    call_other (this_player(), "move_player", "west#players/quantos/plateau/wplat");
    return 1;
}

north() {
    call_other (this_player(), "move_player", "north#players/quantos/plateau/nplat");
    return 1;
}

south() {
    call_other (this_player(), "move_player", "south#players/quantos/plateau/splat");
    return 1;
}

long() {
    write ("You are on a plateau overlooking the desert.\n");
    write ("Far to the west, you can see a building of some kind.\n");
    write ("Looking down to the northeast, you see a busy troll village.\n");
    write ("To the north, south, and west, the plateau stretches on. You\n");
    write ("are beginning to notice a proliferation of fauna, such as yucca\n");
    write ("and cacti. To the far northwest, you can see the telltale spires\n");
    write ("of a large city.\n");
}

short() {
    return "A desert plateau";
}
