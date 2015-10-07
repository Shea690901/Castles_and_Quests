/* uglagroks_room.c */

#include "../config.h"

object uglagrok;

/* For the NEW, IMPROVED monster class: */
string chat_str, a_chat_str, function, type, match;

#undef EXTRA_RESET
#define EXTRA_RESET  extra_reset(arg);

extra_reset(arg) {
    object mazemap, mirrorrobe, weapon;

    if (!uglagrok) {
	uglagrok = clone_object("obj/monster");		/* NEW, IMPROVED monster class! */
	uglagrok->set_name("uglagrok");
	uglagrok->set_alias("mirrormage");
	uglagrok->set_level(17);
	uglagrok->set_hp(300);
	uglagrok->set_al(200);
	uglagrok->set_short("Uglagrok the mirrormage (reflected)");
	uglagrok->set_long("This is Uglagrok, the old wizened magician who once - many years\n" +
			   "ago - created the mirrormaze. Because of this remarkable feat, he\n" +
			   "is known as the mirrormage.\n" +
			   "Uglagrok has devoted his life to the study of optics, and the special\n" +
			   "flavour of magic connected to mirrors. Now he is old, his body is bent\n" +
			   "and his hair is white - but his wisdom and knowledge is greater than ever.\n");
	uglagrok->set_aggressive(0);
	uglagrok->set_spell_mess1("Uglagrok breaks a small mirror and throws the splinters.");
	uglagrok->set_spell_mess2("Uglagrok breaks a small mirror and throws the splinters at you.\n" +
				  "    And yes, they are magical...");
	uglagrok->set_chance(40);
	uglagrok->set_spell_dam(40);
	move_object(uglagrok, this_object());

	/* The NEW, IMPROVED monster calls: */
	if (!chat_str)
	    setup_arrays();
	uglagrok->load_chat(10, chat_str);
	uglagrok->set_match(this_object(), function, type, match);

	mirrorrobe = clone_object("obj/armour");
        mirrorrobe->set_name("mirrorrobe");
        mirrorrobe->set_alias("robe");
        mirrorrobe->set_type("cloak");
        mirrorrobe->set_ac(1);
        mirrorrobe->set_value(500);
        mirrorrobe->set_weight(2);
        mirrorrobe->set_short("A robe covered with tiny mirrors");
        mirrorrobe->set_long("The robe is made of thick black velvet that has been covered with\n" +
		             "small, circular mirrors. The effect is beautiful, if a bit strange.\n" +
       		             "The robe should protect you very well against blows, though.\n");
        move_object(mirrorrobe, uglagrok);
	uglagrok->add_weight(2);
	uglagrok->init_command("wear mirrorrobe");

	weapon = clone_object("obj/weapon");
        weapon->set_name("mirrordagger");
        weapon->set_alt_name("dagger");
        weapon->set_alias("mirror dagger");
        weapon->set_class(6);
        weapon->set_value(300);
        weapon->set_weight(1);
        weapon->set_short("A mirrordagger");
        weapon->set_long("A small, curious dagger. The handle is made of ivory and seems\n" +
			 "ordinary enough, but the blade looks as if it was made of a splinter\n" +
			 "from a mirror. How strange! And there is something written on it, too!\n");
        weapon->set_read("It says: DANGER: This is the Dagger of Reversion. Handle with care!\n");
        weapon->set_hit_func(this_object());
        weapon->set_wield_func(this_object());
        move_object(weapon, uglagrok);
	uglagrok->init_command("wield mirrordagger");

	mazemap = clone_object("players/padrone/obj/thing");
	mazemap->set_name("map");
	mazemap->set_alias("mazemap");
	mazemap->set_short("A map of the mirrormaze");
	mazemap->set_long("This is a map of the mirrormaze.\n" +
          "It is very old, written in paled ink on a sheet of parchment,\n" +
          "but some of the writing seems strangely fresh.\n");
	mazemap->set_can_get(1);
	mazemap->set_weight(1);
	mazemap->set_value(800);
#ifdef NANNY
	mazemap->set_read_file("/players/padrone/maze/nanny_map.txt");
#endif
#ifdef GENESIS
	mazemap->set_read_file("/players/padrone/maze/genesis_map.txt");
#endif
#ifdef IGOR
	mazemap->set_read_file("/players/padrone/maze/igor_map.txt");
#endif
#ifdef EXPORT
	mazemap->set_read_file("/players/padrone/maze/export_map.txt");
#endif
        move_object(mazemap, uglagrok);

	uglagrok->set_ac(4);       	/* Must be done after all wear commands! */
    }
} /* extra_init */

/*  The mirrordagger has 10% chance of reversing the target's alignment!
 *	This works both on monsters and players, but not
 *	if a wizard hits a player.
 */
weapon_hit(victim) {
    int old_al, adjustment;
    string victims_name;

    if (random(10))
	return 0;

    write("You feel the small dagger move in your hand. Something has happened...\n");
    tell_object(victim, "The small dagger hits you -- and something horrible happens!\n");

    victims_name = victim->query_name();

    if(present("EVIL_mark", victim)) {
	/* En EVIL cultist! */
	write("Unfortunately, " + victims_name +
	      " is protected by the mark of EVIL.\n");
	tell_object(victim, "Luckily, you are protected by your mark of EVIL.\n");
	return 0;
    }
    if(present("bath_badge", victim)) {
	/* A knight of the Bath! */
	write("Unfortunately, " + victims_name +
	      " is a member of the Bath, and therefore protected.\n");
	tell_object(victim, "Luckily, you are a member of the Bath, and therefore protected.\n");
	return 0;
    }

    old_al = victim->query_alignment();
    if (victim->query_npc()) {
	victim->set_al(-old_al);
    }
    else {
	adjustment = - old_al - (old_al * 9) / 10;
	victim->add_alignment(adjustment);
    }

    say("    Suddenly, " + victims_name);
    write("    Suddenly, " + victims_name);
    if (old_al < 0) {
	say(" looks much nicer than before.\n");
	write(" looks much nicer than before.\n");
    }
    else if (old_al > 0) {
	say(" doesn't look as nice as before.\n");
	write(" doesn't look as nice as before.\n");
    }
    else {
	say(" looks just as neutral as before.\n");
	write(" looks just as neutral as before.\n");
    }
    return 0;
} /* weapon_hit */

wield() {
    write("The dagger is clearly not a very good weapon, but when you\n" +
	  "wield it you have a feeling of strange and powerful magic\n" +
	  "waiting to be released...\n");
    return 1;
} /* wield */

handle_arrival(str)
{
    say("Uglagrok says: What?!? An intruder! Get out of here immediately!\n");
} /* handle_arrival */


handle_say(str) {
    string who, phrase;

    if (   (sscanf(str, "%s says: %s\n", who, phrase) != 2)
	&& (sscanf(str, "%s says \"%s\"\n", who, phrase) != 2)	/* Morgar's say with quotes! */
	&& (sscanf(str, "%s tells you: %s\n", who, phrase) != 2)) {
	say("Uglagrok looks brain damaged.\n");
	return;
    }
    if (who == "Uglagrok")
	return;

    say("Uglagrok says: Stop talking, stupid! Just get out and STAY out!\n");
} /* handle_say */


/* Expanded from the std.h macros and edited: */

reset(arg) {
    if (!arg)
	set_light(1);
    extra_reset(arg);
}

short() {
    if (set_light(0))
	return "Uglagrok's workroom";
    return "dark room";
}

init() {
    add_action("north", "north");
    add_action("ouch", "south");
    add_action("ouch", "east");
    add_action("ouch", "west");
}

north() {
    this_player()->move_player("north#players/padrone/maze/uglagroks_bathroom");
    return 1;
}

ouch() {
    write("Ouch! That was just a mirror!\n");
    return 1;
}

long(str) {
    if (set_light(0) == 0) {
	write("It is dark.\n");
	return;
    }
    write("You are in a small room that seems to have been cut out from\n" +
	  "the very living rock somewhere deep, deep down, below the face\n" +
	  "of the earth. The walls are covered with big mirrors, and smaller\n" +
	  "mirrors clutter every surface in the room, along with mysterious\n" +
	  "optical instruments.\n"+
	  "    There are four obvious exits, north, south, east and west.\n");
}


/* For the NEW, IMPROVED monster class: */
setup_arrays() {

    /* Peaceful chatting */
    chat_str = ({
	"Uglagrok frowns.\n",
	"Uglagrok glares at you.\n",
	"Uglagrok burps rudely.\n",
	"Uglagrok groans loudly.\n",
	"Uglagrok sighs deeply.\n",
	"Uglagrok says: What are you doing here?\n",
	"Uglagrok says: Why don't you leave? Now, for example.\n",
	"Uglagrok says: You really ARE stupid, aren't you?\n",
	"Uglagrok complains: I made this room just to get away from people like you!\n",
	"Uglagrok complains: I built my workroom 60 miles down in the rock, and the idiots STILL come here.\n",
	"Uglagrok mutters: I want to be alone!\n",
	"Uglagrok mutters: This is a private room!\n"
    });

    function = allocate(3);
    type = allocate(3);
    match = allocate(3);

    function[0] = "handle_say";
    type[0] = "says";
    match[0] = "";
    type[1] = "tells you:";
    match[1] = " ";
    function[2] = "handle_arrival";
    type[2] = "arrives";
    match[2] = "";
} /* setup_arrays */
