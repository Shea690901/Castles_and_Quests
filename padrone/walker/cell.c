/* walker/cell.c */

#include "walker.h"
#include "std.h"

object demon, demons_chest;

/* For the NEW, IMPROVED monster class: */
string function, type, match;

#undef EXTRA_RESET
#define EXTRA_RESET extra_reset(arg);

#undef EXTRA_INIT
#define EXTRA_INIT \
    if (!this_player()->query_npc()) \
        log_file("padrone", ctime(time()) + ": " + this_player()->query_name() + \
		 " entered the (walking) cell.\n");

extra_reset(arg) {
    object temp;

    throw_out_players();

    if (!demon) {
	demon = clone_object("obj/monster");	/* NEW, IMPROVED monster class! */
	demon->set_name("chaosdemon");
	demon->set_alias("demon");
	demon->set_race("demon");
	demon->set_level(19);
	demon->set_neuter();
	demon->set_hp(1000);
	demon->set_al(1500 - random(3000));
	demon->set_ac(1000);
	demon->set_short("An invulnerable chaosdemon");
	demon->set_long("This is a demon of chaos. It is not evil, not good, not neutral.\n" +
			"It is -- chaotic. It shimmers and wavers like a cloud of poison gas,\n" +
			"but you can still make out some features, like the gleaming teeth,\n" +
			"the dangerously glowing eyes, and the industrial-strength muscles in\n" +
			"what should probably be called arms.\n" +
			"This creature looks invulnerable, and clearly a very special weapon\n" +
			"is needed if you want to hurt it.\n");
	demon->set_aggressive(0);
	demon->set_spell_mess1("The chaosdemon casts a SEVERE INTERNAL DAMAGE AND PAIN spell.");
	demon->set_spell_mess2("The chaosdemon casts a SEVERE INTERNAL DAMAGE AND PAIN spell at you.");
	demon->set_chance(20);
	demon->set_spell_dam(40);
	move_object(demon, this_object());

	/* The NEW, IMPROVED monster calls: */
	if (!function)
	    setup_arrays();
	demon->set_match(this_object(), function, type, match);

	temp = clone_object("obj/weapon");
	temp->set_name("chaosblade");
	temp->set_alias("chaosblade of death");
	temp->set_alt_name("sword");
	temp->set_short("A chaosblade of death");
	temp->set_long("This is a slim, but very heavy, sword that seems to glow with\n" +
		       "soft darkness. It looks strangely unnatural, and it would\n" +
		       "probably be a bad move even to try to wield this weapon.\n" +
		       "Maybe someone else wants it?\n" +
		       "Come to think of it, wasn't there a strange shop on Ingis' Good Alley\n" +
		       "where you could bring this sword and collect a reward?\n");
	temp->set_class(30);
	temp->set_weight(7);
	temp->set_value(2000);
	temp->set_wield_func(this_object());
	move_object(temp, demon);
	demon->init_command("wield chaosblade");

	demons_chest = clone_object("obj/chest");
        move_object(demons_chest, demon);

	temp = clone_object("obj/money");
        temp->set_money(4000);
        move_object(temp, demons_chest);
    }
} /* extra_reset */

/* For the NEW, IMPROVED monster class: */
setup_arrays() {

    function = allocate(3);
    type = allocate(3);
    match = allocate(3);

    function[0] = "handle_arrival";
    type[0] = "arrives";
    match[0] = "";
    function[1] = "handle_leaving";
    type[1] = "leaves";
    match[1] = "";
    type[2] = "disappears";
    match[2] = "";
} /* setup_arrays */

handle_arrival() {
    if (demon && living(demon))
	set_heart_beat(1);
} /* handle_arrival */

handle_leaving() {
    if (demon && !demon->test_if_any_here())
	set_heart_beat(0);
} /* handle_leaving */

wield(obj) {
    string pn;

    if (!this_player())
	return 1;
    pn = this_player()->query_name();
    if (pn == "Chaosdemon")
	return 1;

    write("The sword twists away from your grip, hovers in the air and looks at you.\n");
    write("Then it laughs contemptuously and disappears in a blinding flash.\n");
    write("You think you can hear the words 'Puny mortal!' from somewhere far away...\n");
    move_object(obj, "players/padrone/store");
    say(pn + " fails spectacularly at wielding the chaosblade.\n");
    return 0;
}

heart_beat() {
    int al;

    if (!demon || !living(demon) || !present(demon, this_object())) {
	set_heart_beat(0);
	return;
    }
    al = demon->query_alignment();
    if (al > 0)
	al = -random(1500);
    else
	al = random(1500);
    demon->set_al(al);
    if (al < -1000)
	tell_room(environment(demon), "Now the demon looks totally evil.\n");
    else if (al < 0)
	tell_room(environment(demon), "Now the demon looks evil.\n");
    else if (al < 1000)
	tell_room(environment(demon), "Now the demon looks nice.\n");
    else
	tell_room(environment(demon), "Now the demon looks very nice.\n");
} /* heart_beat */


ONE_EXIT("players/padrone/walker/vault", "south",
	 "Cell inside the walking castle",
	 "This is an air-tight steel room inside the walking castle.\n" +
	 "There are no openings, except for a heavy steel door to the south.\n" +
	 "The floor has been engraved with anti-teleport runes, and on the\n" +
	 "walls you see spells of imprisonment softly glowing in the dim light.\n", 1)


/* The walker-cell is teleport-safe */
realm() { return "NT"; }

throw_out_players() {
    object obj, this_obj;

    obj = first_inventory(this_object());
    while (obj) {
	this_obj = obj;
	obj = next_inventory(obj);
	if (living(this_obj) && !this_obj->query_npc()) {
	    tell_object(this_obj, "Suddenly, you have a feeling of disorientation.\n");
	    this_obj->move_player("out#players/padrone/walker/upper_hall");
	}
    } /* while */
} /* throw_out_players */


/*
 *  Things are being put in the vault by calls to this function!
 *  I used to put them in the vault in the (stationary) castle,
 *  but everybody seems to break in there...
 */
put_in_vault(an_object) {

    if (demon && present(demon, this_object()) && demons_chest)
	/* Yes, ignore any weight limits. The chest is infinitely large... */
	move_object(an_object, demons_chest);
    else
	/* Don't just GIVE treasure away! */
	move_object(an_object, "players/padrone/store");
} /* put_in_vault */
