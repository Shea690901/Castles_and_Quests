/*
 *  AUTOMATIC WEAPON (autowpn) -- Yeah!
 *  This is a generic automatic weapon, a subclass of the genericer WEAPON object.
 *  Clone or specialize it to get M16:s, machine guns, pulse rifles
 *  -- or even non-automatic weapons!
 *  Thomas Padron-McCarthy, padrone@lysator.liu.se
 *  This version uses the gender functions in /obj/living.c!
 */


inherit "obj/weapon";

/* AUTOWPN's extra variables */ 
int max_bullets;	/* How many bullets when full? */
int nr_bullets;		/* How many bullets now? */
int max_salvo;		/* Max nr of shots fired each round */
int wc_per_bullet;     	/* Weapon class per shot fired */
string sound;		/* Sound, "BANG" for example */
/* Note that class_of_weapon applies when the weapon is used as a club! */
status click_done;	/* 1 when wielder has tried to fire empty weapon */
int value_per_bullet;	/* Added to 'value' */
status monster_reload;	/*  If true, NPC:s will automatically reload their weapons
			 *  when they are empty, not just at reset.
			 */

reset(arg) {
    ::reset(arg);
    if (!arg) {
	max_bullets = 0;
	nr_bullets = max_bullets;
	max_salvo = 20;
	wc_per_bullet = 1;
	sound = "BANG";
	click_done = 0;
	value_per_bullet = 1;
	set_name("uninitialized generic automatic weapon");
	set_weight(10);		/* Initialized as very heavy */
	monster_reload = 0;
    }
    else if (nr_bullets == 0 && click_done && wielded_by && wielded_by->query_npc()) {
	/* Wielded by a monster: reload! */
	do_monster_reload();
    }
} /* reset */

long() {
    ::long();
    /* Special for AUTOWPN: */
    if (nr_bullets == 0)
	write("Unfortunately, there are no bullets left.\n");
    else if (nr_bullets == 1)
	write("There is only one bullet left in it.\n");
    else
	write("There are " + nr_bullets + " bullets left in it.\n");
} /* long */

init() {
    ::init();
    add_action("wield", "wield");
    add_action("do_reload_command", "reload");
}

do_reload_command(str)
{
    if (!id(str))
	return 0;
    if (environment() != this_player()) {
	write("You must get it first!\n");
	return 1;
    }
    write("You are not allowed to reload this weapon!\n");
    return 1;
} /* do_reload_command */

do_monster_reload() {
    string printstring;
    printstring = wielded_by->query_name() + " reloads " +
	wielded_by->query_possessive() + " " + name_of_weapon + ".\n";
    write(printstring);
    say(printstring);
    nr_bullets = max_bullets;
    click_done = 0;
} /* do_monster_reload */

id(str) {
    return str == name_of_weapon || str == alt_name || str == alias_name
           || str == "gun" || str == "automatic weapon";
}

/* Here is the most important part of the AUTOWPN code: */
/* Note that we have to compensate for class_of_weapon if not used as club. */
hit(attacker)
{
    int nr_fired, i;
    string ratata;
    int wc;

    if (nr_bullets == 0) {
	if (click_done) {
	    if (monster_reload && wielded_by->query_npc()) {
		/* Wielded by a monster: reload! */
		do_monster_reload();
		wc = -class_of_weapon; /* Compensate! */
	    }
	    else {
		tell_object(wielded_by,
			    "You swing your empty " + name_of_weapon +
			    " and try to smash " +
			    call_other(attacker, "query_name", 0) +
			    ".\n");
		say(call_other(this_player(),"query_name",0) +
		    " swings " + this_player()->query_possessive() +
		    " empty " + name_of_weapon + " and tries to smash " +
		    call_other(attacker, "query_name", 0) +
		    ".\n");
		wc = 0;	/* Used as club, use class_of_weapon! */
	    }
	}
	else {
	    tell_object(wielded_by, "Click! Click! Click! No bullets!\n");
	    say(call_other(wielded_by, "query_name",0) +
		" presses the trigger of " + this_player()->query_possessive() +
		" " + name_of_weapon +
		", but nothing happens.\n");
	    click_done = 1;
	    wc = -class_of_weapon; /* Compensate! */
	}
    }
    else {
	tell_object(wielded_by,
		    "You open fire on " +
		    call_other(attacker, "query_name", 0) +
		    " with your " + name_of_weapon + "!\n");
	say(call_other(this_player(),"query_name",0) +
	    " opens fire on " +
	    call_other(attacker, "query_name", 0) +
	    " with " + this_player()->query_possessive() + " " + name_of_weapon + "!\n");

	if (nr_bullets < max_salvo)
	    nr_fired = random(nr_bullets) + 1;
	else
	    nr_fired = random(max_salvo) + 1;
	nr_bullets = nr_bullets - nr_fired;
	ratata = sound;
	i = nr_fired - 1;
	while (i > 0) {
	    i = i - 1;
	    ratata = ratata + "-" + sound;
	}
	ratata = ratata + "!\n";
	say(ratata);
	write(ratata);
	wc = wc_per_bullet * nr_fired - class_of_weapon; /* Compensate! */
    }

    if (hit_func)
	return wc + call_other(hit_func,"weapon_hit",attacker);
    else
	return wc;
} /* hit -- heavily modified for AUTOWPN */

query_value() {
    return value + nr_bullets * value_per_bullet;
}

/* Use these functions to set AUTOWPN's extra variables: */ 
set_max_bullets(n) { max_bullets = n; }
set_bullets(n) { nr_bullets = n; }
set_max_salvo(n) { max_salvo = n; }
set_wc_per_bullet(n) { wc_per_bullet = n; }
set_sound(s) { sound = s; }
set_value_per_bullet(n) { value_per_bullet = n; }
set_monster_reload(s) { monster_reload = s; }
