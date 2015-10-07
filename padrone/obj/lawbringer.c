/*
 *  The Lawbringer of Balance -- yet another sword
 *  Thomas Padron-McCarthy, padrone@lysator.liu.se
 *
 *  Note. To kill the chaosdemon, it has to create the corpse,
 *  move the objects, and add ep to the player.
 *  Check that this is consistent with the current LPmud version!
 *  Oct 18, 1990 ... Feb 9, 1991.
 */

inherit "obj/weapon";

reset(arg) {
    ::reset(arg);
    if (!arg) {
	/* First reset */
	set_name("lawbringer");
	set_alt_name("sword");
	set_short("The Lawbringer of Balance");
	set_long("This is the legendary Lawbringer of Balance.\n" +
		 "Many believe that this sword was forged in ancient times\n" +
		 "by a dwarven king with a hammer borrowed from a god,\n" +
		 "using a dragon's breath to heat the steel.\n" +
		 "Then nine Great Wizards of Law enchanted the blade with a powerful\n" +
		 "spell, and it was thus created one of the most formidable weapons\n" +
		 "ever to be seen on this Earth. It is even rumoured that the Lawbringer\n" +
		 "has a mind of its own, that it loves the balanced and neutral and hates\n" +
		 "the unbalanced and extreme... But naturally, those who are worthy to\n" +
		 "wield such a weapon are few.\n");
	set_class(23);
	set_value(7000);
	set_weight(4);
        set_hit_func(this_object());
        /* Wield has to handled specially, since both functions would be called "wield". */
	call_out("check_neutrality", 60);
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

    /* Lawbringer code */
    {
	int abs_al;
	abs_al = get_abs_alignment(this_player());
	if (abs_al < 20) {
	    /* -19..+19, inclusive */
	    write("The weapon glows briefly with a soft, approving light.\n");
	}
	else if (abs_al < 40) {
	    /* Inside -39..+39 inclusive -- neutral */
	}
	else {
	    /* Outside neutrality */
	    write("You are too unbalanced to use this weapon.\n");
	    return 1;
	}
    } /* End of Lawbringer code */

    if(wield_func)
	if(!call_other(wield_func,"wield",this_object())) 
	    return 1;
    wielded_by = this_player();
    call_other(this_player(), "wield", this_object());
    wielded = 1;
    return 1;
}/* wield */

destruct_demon(the_demon) {
    object the_corpse, loopobj, obj;

    if (the_demon && wielded_by) {
	/* Sigh! The stupid demon is still alive! */
	tell_room(environment(wielded_by),
		  "As the mighty Lawbringer cuts through the unholy flesh\n" +
		  "of the blasphemous Chaosdemon, the demon is destroyed!\n");
	wielded_by->add_exp(the_demon->query_exp() / 80);
	the_corpse = clone_object("obj/corpse");
	the_corpse->set_name("chaosdemon");
	move_object(the_corpse, environment(the_demon));
	loopobj = first_inventory(the_demon);
	while (loopobj) {
	    obj = loopobj;
	    loopobj = next_inventory(loopobj);
	    obj->drop();
	    move_object(obj, the_corpse);
	}
	destruct(the_demon);
    }
} /* destruct_demon */

weapon_hit(victim)
{
    int temp;

    if (call_other(victim, "query_name") == "Chaosdemon") {
	call_other(victim, "set_hp", 0);
	call_other(victim, "set_ac", 0);
	call_out("destruct_demon", 1, victim);
	return 0;
    }

    /* This sword hates those who are not neutral! */
    temp = - get_abs_alignment(wielded_by) / 10 + get_abs_alignment(victim) / 100;
    if (temp > 10)
	temp = 10; /* But there is a limit to its hate... */
    return temp;
} /* weapon_hit */

check_neutrality() {	/* Called every 60 seconds... */
    int abs_al;

    if (wielded) {
	abs_al = get_abs_alignment(wielded_by);
	if (abs_al < 20) {
	    /* -19..+19, inclusive */
	    tell_object(wielded_by, "Suddenly, you feel a strange kinship to your sword, and you feel stronger!\n");
	    call_other(wielded_by, "heal_self", 1+random(2));
	}
	else if (abs_al < 40) {
	    /* Inside -39..+39 inclusive -- still neutral */
	    tell_object(wielded_by, "Your sword seems to think that you are somewhat unbalanced...\n");
	}
	else if (abs_al < 100) {
	    /* Strayed from neutrality, but still inside -99..+99 inclusive */
	    tell_object(wielded_by, "Suddenly, your sword jumps from your grip! You have strayed from neutrality.\n");
	    call_other(wielded_by, "stop_wielding");
	}
	else {
	    /* Outside -99..+99 inclusive -- really strayed from neutrality */
	    tell_object(wielded_by, "Suddenly, your sword jumps from your grip," +
			" cuts you and disappears!\n");
	    tell_object(wielded_by, "You have strayed far from neutrality.\n");
	    call_other(wielded_by, "stop_wielding");
	    wielded = 0;
	    call_other(wielded_by, "hit_player", class_of_weapon);
	    call_other(wielded_by, "add_weight", - local_weight);
	    call_other("players/padrone/tower/vault", "put_back_lawbringer", this_object());
	}
    } /* if wielded */

    call_out("check_neutrality", 60);
} /* check_neutrality */

get_abs_alignment(x) {
    int temp;

    temp = call_other(x, "query_alignment");
    if (temp < 0)
	return 0 - temp;
    else
	return temp;
} /* get_abs_alignment */
