/*
 *  m16 -- the automatic weapon
 *  This object (m16) inherits from the generic automatic weapon object,
 *  which inherits from the even more generic weapon object.
 *  Thomas Padron-McCarthy, padrone@lysator.liu.se
 *
 */

inherit "players/padrone/obj/autowpn";

reset(arg) {
    ::reset(arg);
    if (!arg) {
	set_name("M-16");
	set_alias("m-16");
	set_alt_name("m16");
	set_class(5);		/* When used as a club */
	set_weight(2);
	set_value(20);
	set_short("An M-16");
	set_long("It looks like a truly lethal weapon -- black and menacing...\n" +
		 "There is some small red print on the weapon.\n");
	set_read("You read the small red print on the weapon. It says:\n" +
		 "    Assault Rifle M/16. Property of the USMC.\n");
	set_max_bullets(20);
	set_bullets(20);
	set_max_salvo(20);
	set_wc_per_bullet(1);
	set_sound("BLAM");
	set_value_per_bullet(1);
	set_monster_reload(1);
    }
} /* reset */
