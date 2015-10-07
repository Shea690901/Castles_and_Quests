
/* The Wizardsbane -- A wizard-destructing weapon! */

inherit "obj/weapon";

object remembered_victim;	/* The wiz being destroyed */

reset(arg) {
    ::reset(arg);
    if (!arg) {
	/* First reset */
	set_name("wizardsbane");
	set_alt_name("axe");
	set_short("A big and heavy double-edged axe named Wizardsbane");
	set_long("The axe is engraved with strange pictures and runes.\n" +
		 "The pictures seem to be of powerful wizards being horribly\n" +
		 "mutilated, sliced in two, and physically abused in general.\n" +
		 "And you avoid looking at the runes, they don't look nice.\n");
	set_class(20);
	set_value(50);
	set_weight(4);
        set_hit_func(this_object());
        /* Wield has to handled specially, since both functions would be called "wield". */
	remembered_victim = 0;
    }
} /* reset */

wield(str) {	/* This "wield" is used instead of weapon::wield */
    if (!id(str))
	return 0;
    if (environment() != this_player()) {
	/* write("You must get it first!\n"); */
	return 0;
    }
    if (wielded) {
	write("You already wield it!\n");
	return 1;
    }

    /* Wizardsbane code */
    {
	write("As you wield the Wizardsbane, you feel a strange and\n" +
	      "frightful power travel up your arms - the power to\n" +
	      "utterly destroy those who cannot be killed...\n");
    } /* End of Wizardsbane code */

    if(wield_func)
	if(!call_other(wield_func,"wield",this_object())) 
	    return 1;
    wielded_by = this_player();
    call_other(this_player(), "wield", this_object());
    wielded = 1;
    return 1;    
}/* wield */

weapon_hit(victim)
{
    string vn;

    vn = victim->query_name();
    if (victim->query_level() < 20) {
	if (!random(3))
	    write("Bah! " + vn + " is a much too easy victim for the mighty Wizardsbane.\n");
	return -10;
    }
    else if (victim->query_npc()) {
	if (!random(3))
	    write("Bah! " + vn + " is a common monster. Hardly a proper target for the Wizardsbane.\n");
	return -10;
    }

    write("The Wizardsbane sings with joy as it bites into the flesh of " + vn + "!\n");
    say("The Wizardsbane sings with joy as it bites into the flesh of " + vn + "!\n");
    write("The runes on its blade glow with a light that hurts the eye.\n");
    say("The runes on its blade glow with a light that hurts the eye.\n");

    if (!remembered_victim) {
	remembered_victim = victim;
	call_out("destroy1", 1);
    }
    return 10;
} /* weapon_hit */

destroy1() {
    string vn;
    int n;
    object the_room, the_corpse;

    if (wielded_by && remembered_victim && present(remembered_victim, environment(wielded_by))) {
	the_room = environment(wielded_by);
	vn = remembered_victim->query_name();
	tell_room(the_room, vn + " is annihilated by the Wizardsbane!\n");
	n = destruct_contents(remembered_victim);
	tell_room(the_room, vn + " and " + n + " other (carried) objects were destroyed.\n");

	wielded_by->stop_fight();
	remembered_victim->stop_fight();

	the_corpse = clone_object("obj/corpse");
	the_corpse->set_name(vn);
	move_object(the_corpse, environment(remembered_victim));

	call_out("destroy2", 1);
    }
} /* destroy1 */

destroy2() {
    if (remembered_victim)
	destruct(remembered_victim);
} /* destroy2 */

destruct_contents(mama_obj) {
    object an_obj, this_obj;
    int nr_destroyed;

    nr_destroyed = 0;
    an_obj  = first_inventory(mama_obj);
  
    while (an_obj) {
	this_obj = an_obj;
	an_obj = next_inventory(an_obj);
	if (!living(this_obj) || call_other(this_obj, "query_npc")) {
	    nr_destroyed += destruct_contents(this_obj);
	    destruct(this_obj);
	    nr_destroyed += 1;
	}
    }

    return nr_destroyed;
} /* destruct_contents */
