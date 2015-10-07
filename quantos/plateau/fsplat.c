/* #include "std.h" /Pell */

reset (arg) {
    if(!arg)
	set_light(1);
    extra_reset();
}

object spider, fang;

extra_reset() {
    if (!spider || !living(spider)) {
	spider = clone_object("obj/monster");
	call_other (spider, "set_name", "spider");
	call_other (spider, "set_alias", "tarantula");
	call_other (spider, "set_race", "arachnid");
	call_other (spider, "set_short", "A giant tarantula");
	call_other (spider, "set_level", 12);
	call_other (spider, "set_hp", 200);
	call_other (spider, "set_wc", 20);
	call_other (spider, "set_ac", 2);
	call_other (spider, "set_move_at_reset", 1);
/*	call_other (spider, "set_can_kill", 1); /Pell */
	call_other (spider, "set_whimpy", 1);
	call_other (spider, "set_aggressive", 1);
	call_other (spider, "set_init_ob", this_object());
	move_object (spider, this_object());

	fang = clone_object("obj/weapon");
	call_other (fang, "set_name", "fang");
	call_other (fang, "set_short", "A poisonous fang");
	call_other (fang, "set_class", 10);
	call_other (fang, "set_weight", 2);
	call_other (fang, "set_value", 500);
	move_object (fang, spider);
    }
}

monster_init (obj) {
    if (call_other (obj, "query_name") == "scorpion") {return 0;}
    return 1;
}

init() {
    add_action ("north"); add_verb ("north");
    add_action ("south"); add_verb ("south");
    add_action ("south"); add_verb ("east"); /* Pell */
    add_action ("west"); add_verb ("west");
}

north() {
    call_other (this_player(), "move_player", "north#players/quantos/plateau/splat");
    return 1;
}

west() {
    write ("As you step to the west, you feel the ground give way beneath your feet!\n");
    write ("You hit the ground hard!\n");
    call_other (this_player(), "hit_player", random(10));
    call_other (this_player(), "move_player", "west#players/quantos/under/sinkhole");
    return 1;
}

south() {
    write ("The climb is too steep, and you would not survive the fall.\n");
    return 1;
}

long() {
    write ("You are at the far southern edge of the plateau. Down to the\n");
    write ("east, you can see an expansive forest. The plateau continues\n");
    write ("to the north and west.\n");
}

short() {
    return "Far south plateau";
}
