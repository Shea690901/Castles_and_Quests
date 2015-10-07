/*
 *  heavy machine gun -- Yeah!
 *  Compare M16.
 *  Thomas Padron-McCarthy, padrone@lysator.liu.se
 */

inherit "players/padrone/obj/autowpn";

reset(arg) {
    ::reset(arg);
    if (!arg) {
	set_name("heavy machine gun");
	set_short("A heavy machine gun");
	set_long("This is a heavy machine gun.\n" +
		 "It is black and heavy, and it glitters with oily precision.\n" +
		 "This is no puny M-16 -- this is a TRULY lethal weapon!\n");
	set_value(50);
	set_weight(4);
	set_class(5);

	set_max_bullets(250);
	set_bullets(250);
	set_max_salvo(20);
	set_wc_per_bullet(2);
	set_sound("TOK");
	set_value_per_bullet(2);
	set_monster_reload(1);
    }

} /* reset */


wield(str) {
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

    if(wield_func)
	if(!call_other(wield_func,"wield",this_object())) 
	    return 1;
    if (call_other(this_player(), "query_level", 0) < 10) {
	write("You are confused by the multitude of buttons and the complicated sights.\n");
	write("This weapon is obviously too complicated for you.\n");
	say(call_other(this_player(),"query_name",0)+
	    " failed to wield a heavy machine gun\n");
	return 1;
    }
    write("The weight of the machine gun feels reassuring...\n");
    wielded_by = this_player();
    call_other(this_player(), "wield", this_object());
    wielded = 1;
    return 1;
} /* wield */


id(str)
{

    return    str == "heavy machine gun" || str == "gun"
	   || str == "machine gun" || str == "machinegun";
}
