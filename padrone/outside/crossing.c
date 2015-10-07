/*  crossing.c
 *	In this room Sir Obliterator the anti-paladin is defined.
 *	He is on a quest for prince Violens...
 *  Latest update: Feb 9, 1990
 */

#include "std.h"

object sign;
object obliterator, follow, last_talker, violens, sword;
string follow_name;
status found_him;

/* For the NEW, IMPROVED monster class: */
string chat_str, a_chat_str, function, type, match;

/* If you change this, change obli_hit_func.c too: */
#define WEAPON_CLASS	20	/* Unmodified class of unholy avenger. Never unmodified! */

#undef EXTRA_RESET
#define EXTRA_RESET extra_reset();

extra_reset() {

    if (!obliterator)
	make_obliterator();
    
    if (!sign) {
	sign = clone_object("players/padrone/obj/thing");
	sign->set_name("sign");
	sign->set_short("A sign pointing south");
	sign->set_long("This is a small white wooden sign on a pole.\n" +
		       "It is pointing south, and there is something written on it.\n");
	sign->set_read("It says: This way to the Castle of Padrone.\n");
	sign->set_can_get(0);
	move_object(sign, this_object());
    }
} /* extra_reset */

FOUR_EXIT("players/padrone/outside/path2", "north",
	  "players/padrone/outside/path3", "south",
	  "players/padrone/outside/crosspath1", "west",
	  "players/padrone/outside/crosspath2", "east",
	  "Crossing",
	  "You are at a crossing, where two small paths are\n" +
	  "crossing each other in the forest.\n", 1)
  
/* --------- The code for Obliterator is below this line --------- */
  
make_obliterator() {
    object special_sword, talker, thing;
      
    follow = 0;
    follow_name = 0;
    last_talker = 0;
    found_him = 0;
    violens = 0;
      
    obliterator = clone_object("obj/monster");	/* NEW, IMPROVED monster class! */
    obliterator->set_name("obliterator");
    obliterator->set_alias("sir obliterator");
    obliterator->set_level(19);
    obliterator->set_hp(250);
    obliterator->set_al(-1000);
    obliterator->set_short("Sir Obliterator, the anti-paladin");
    obliterator->set_long("Sir Obliterator is an evil anti-paladin.\n" +
			  "He is dressed in black, has a grim look on his face, and is quite\n" +
			  "obviously very, very dangerous. You are lucky today, however,\n" +
			  "because he doesn't seem to be the least interested in you.\n" +
			  "Sir Obliterator is on an important mission -- a matter of life\n" +
			  "and death! Well, mostly death, really...\n");
    obliterator->set_aggressive(0);
    obliterator->set_spell_mess1("Sir Obliterator kicks his opponent hard with his combat boots.");
    obliterator->set_spell_mess2("Sir Obliterator kicks you hard with his combat boots.");
    obliterator->set_chance(20);
    obliterator->set_spell_dam(20);
    obliterator->set_dead_ob(this_object());
    move_object(obliterator, this_object());
    
    /* The NEW, IMPROVED monster calls: */
    if (!chat_str)
	setup_arrays();
    obliterator->load_chat(10, chat_str);
    obliterator->load_a_chat(20, a_chat_str);
    obliterator->set_match(this_object(), function, type, match);
    
    thing = clone_object("obj/treasure");
    thing->set_id("amulet");
    thing->set_alias("big black iron amulet");
    thing->set_short("A big black iron amulet");
    thing->set_long("This is Sir Obliterator's teleport device, a big and heavy black amulet\n" +
		    "made of iron, engraved with some evil-looking runes. You cannot use\n" +
		    "it to teleport, since it was made specifically for Sir Obliterator.\n");
    thing->set_weight(4);
    thing->set_value(20);
    move_object(thing, obliterator);
    
    thing = clone_object("obj/armour");
    thing->set_name("chainmail");
    thing->set_alias("armour");
    thing->set_type("armour");
    thing->set_ac(3);
    thing->set_value(500);
    thing->set_weight(5);
    thing->set_short("A suit of chainmail");
    move_object(thing, obliterator);
    obliterator->add_weight(5);
    obliterator->init_command("wear chainmail");
    
    thing = clone_object("obj/armour");
    thing->set_name("shield");
    thing->set_alias("big black shield");
    thing->set_type("shield");
    thing->set_ac(1);
    thing->set_value(100);
    thing->set_weight(5);
    thing->set_short("A big black shield with a picture painted on it");
    thing->set_long("The shield is big, black but not very beautiful.\n" +
		    "There is a picture painted on it, a picture of a dead\n" +
		    "young prince being eaten by a black dragon.\n");
    move_object(thing, obliterator);
    obliterator->add_weight(6);
    obliterator->init_command("wear shield");
    
    thing = clone_object("obj/armour");
    thing->set_name("metal helmet");
    thing->set_ac(1);
    thing->set_weight(2);
    thing->set_value(75);
    thing->set_alias("helmet");
    thing->set_type("helmet");
    thing->set_short("A metal helmet");
    thing->set_long("A metal helmet.\n");
    move_object(thing, obliterator);
    obliterator->add_weight(2);
    obliterator->init_command("wear helmet");
    
    thing = clone_object("obj/armour");
    thing->set_name("combat boots");
    thing->set_ac(1);
    thing->set_weight(1);
    thing->set_value(75);
    thing->set_alias("boots");
    thing->set_type("boot");
    thing->set_short("A pair of combat boots");
    move_object(thing, obliterator);
    obliterator->add_weight(1);
    obliterator->init_command("wear boots");
    
    sword = clone_object("obj/weapon");
    sword->set_name("black longsword");
    sword->set_alt_name("longsword");
    sword->set_alias("sword");
    sword->set_class(16);
    sword->set_value(200);
    sword->set_weight(3);
    sword->set_short("A black longsword");
    sword->set_long("This is the black longsword of Sir Obliterator, the anti-paladin.\n" +
		    "As a weapon it's not really that impressing, but Sir Obliterator\n" +
		    "obviously thinks it is quite sufficient for the random encounters\n" +
		    "he will have while he is on his quest - those nerds who actually\n" +
		    "are stupid enough to attack him. Him!\n" +
		    "For his real mission, though, he has another weapon...\n");
    sword->set_hit_func(this_object());
    move_object(sword, obliterator);
    obliterator->add_weight(3);
    obliterator->init_command("wield sword");
    
    special_sword = clone_object("obj/weapon");
    special_sword->set_name("unholy avenger");
    special_sword->set_alt_name("avenger");
    special_sword->set_alias("sword");
    special_sword->set_class(WEAPON_CLASS);
    special_sword->set_value(8000);
    special_sword->set_weight(6);
    special_sword->set_short("An Unholy Avenger of Specified Annihilation");
    special_sword->set_long("What a horrible weapon! It is black as night, cold as ice and heavy\n" +
			    "as a gravestone soaked in blood. You shiver with fear just from\n" +
			    "looking at this evil, evil, evil thing.\n" +
			    "But you understand that this is a very special weapon, existing\n" +
			    "only for a single purpose. Somewhere, someone has made this sword,\n" +
			    "infested it with pure evil, and filled it with a hate that burns\n" +
			    "for a single being in the world...\n");
    move_object(special_sword, "players/padrone/outside/obli_hit_func");
    special_sword->set_hit_func(environment(special_sword));
    special_sword->set_wield_func(this_object());
    move_object(special_sword, obliterator);
      
    /* Adjusted for his extra strength and agility, to match Violens: */
    obliterator->set_ac(9);
    obliterator->set_wc(30);
} /* make_obliterator */

/* Used by the longsword! The Unholy Avenger uses weapon_hit in obli_hit_func.c! */
weapon_hit(victim) {
    
    if (   environment(sword) == obliterator
	&& obliterator->query_attack() == victim
	&& victim->query_npc()
	&& victim->query_name() != "Violens"
	&& environment(obliterator) != this_object()) {
	
	/*  Obliterator is using his longsword to fight an NPC,
	 *  that is not Violens, in a place other than the crossing!
	 */
	
	say("Sir Obliterator says: I don't have time for this ridiculous fighting!\n");
	say("Sir Obliterator disappears in a puff of smoke.\n");
	move_object(obliterator, this_object());
	say("Sir Obliterator arrives in a puff of smoke.\n");
    }
    return 0;
} /* weapon_hit */

wield() {
    if (call_other(this_player(), "query_alignment") > -200) {
	write("This sword is not for you. Your personality is much too nice.\n");
	return 0;
    }
    else {
	write("Beware! This sword might not be as good as you believe it is.\n");
	return 1;
    }
} /* wield */


check_violens(str) {
    if (found_him && !violens) {
	say("Sir Obliterator says: Done! My quest is solved!\n");
	say("Sir Obliterator disappears in a puff of smoke.\n");
	move_object(obliterator, "players/padrone/store");
	obliterator->hit_player(1000000);
	return 1;
    }
    if (!found_him) {
	violens = present("violens", environment(obliterator));
	if (violens) {
	    found_him = 1;
	    /* Stop talking: */
	    obliterator->load_chat(0, chat_str);
	    obliterator->load_a_chat(0, a_chat_str);
	    say("Sir Obliterator says: Well then! We meet at last, you bastard!\n");
	    obliterator->init_command("wield unholy avenger");
	    obliterator->set_wc(35);	/* He might still fight a player */
	    obliterator->attacked_by(violens);
	    return 1;
	}
    }
    return 0;
} /* check_violens */

handle_say(str) {
    object talker;
    string who, phrase, a, b, dir, where;
    int oa, na, add;
    
    if (check_violens())
	return;
    else if (violens && present(violens, environment(obliterator)))
	return;
    
    if (   (sscanf(str, "%s says: %s\n", who, phrase) != 2)
	&& (sscanf(str, "%s says \"%s\"\n", who, phrase) != 2)	/* Morgar's say with quotes! */
	&& (sscanf(str, "%s tells you: %s\n", who, phrase) != 2)) {
	say("Sir Obliterator looks brain damaged.\n");
	return;
    }
    if ((who == "Sir Obliterator") || (who == "Obliterator"))
	return;
    phrase = lower_case(str);	/* Use the whole sentence, including "X says: " */
    talker = find_living(lower_case(who));
    if (!talker) {
	say("Sir Obliterator looks confused.\n");
	return;
    }
    where = 0;
    if (sscanf(phrase, "%snorth%s", a, b) == 2) {
	where = "north";
    }
    else if (sscanf(phrase, "%ssouth%s", a, b) == 2) {
	where = "south";
    }
    else if (sscanf(phrase, "%seast%s", a, b) == 2) {
	where = "east";
    }
    else if (sscanf(phrase, "%swest%s", a, b) == 2) {
	where = "west";
    }
    else if (sscanf(phrase, "%ssoutheast%s", a, b) == 2) {
	where = "southeast";
    }
    else if (sscanf(phrase, "%ssouthwest%s", a, b) == 2) {
	where = "southwest";
    }
    else if (sscanf(phrase, "%snortheast%s", a, b) == 2) {
	where = "northeast";
    }
    else if (sscanf(phrase, "%snorthwest%s", a, b) == 2) {
	where = "northwest";
    }
    if (where) {
	say("Sir Obliterator says: " + capitalize(where) +
	    ", you say! Thank you for your information!\n");
	last_talker = talker;
	obliterator->init_command(where);
	return;
    }
    if (sscanf(phrase, "%sfollow%s", a, b) == 2) {
	say("Sir Obliterator says: Well then, " + who +
	    ", now lead me to prince Violens!\n");
	last_talker = 0;
	follow = talker;
	follow_name = capitalize(who);
	return;
    }
    if (sscanf(phrase, "%sviolens%s", a, b) == 2) {
	say("Sir Obliterator says: Yes! Yes! Tell me where he is!\n");
	return;
    }
    say("Sir Obliterator says: Stop talking nonsense! Tell me where prince Violens is!\n");
    return;
} /* handle_say */

handle_arrival(str)
{
    string who, rest, n;
    
    if (check_violens())
	return;
    else if (violens && present(violens, environment(obliterator)))
	return;
    
    if (sscanf(str, "%s arrives%s", who, rest) != 2) {
	say("Sir Obliterator looks brain damaged.\n");
	return;
    }
    if (   who != "Sir Obliterator" && who != "Obliterator"
	&& who != "Violens")
	say("Sir Obliterator says: Excuse me, " + who +
	    ", but have you seen prince Violens?\n");
} /* handle_arrival */

handle_leaving(str)
{
    string who, rest, n;
    
    if (check_violens())
	return;
    
    if (sscanf(str, "%s leaves %s.\n", who, rest) != 2) {
	say("Sir Obliterator looks brain damaged.\n");
	return;
    }
    else if ((who == "Sir Obliterator") || (who == "Obliterator"))
	return;
    else if (who == "Violens") {
	obliterator->init_command(rest);
	check_violens();
    }
    else if (violens && present(violens, environment(obliterator))) {
	return;
    }
    else if (who == follow_name) {
	obliterator->init_command(rest);
	if (!found_him) {
	    if (check_violens() && present(follow, environment(obliterator))) {
		say("Sir Obliterator says: Here is your reward, " + follow_name + ".\n");
		say("Sir Obliterator gives 200 coins to " + follow_name + ".\n");
		call_other(follow, "add_money", 200);
		tell_object(follow, "You feel more evil, having sold prince Violens to the anti-paladin.\n");
		call_other(follow, "add_alignment", -200);
		follow = 0;
		follow_name = 0;
	    }
	}
	else
	    check_violens();
    }
    else if (random(4)) {
	object enemy;
	
	/* Not following anyone: 75% chance of following anybody */
	enemy = obliterator->query_attack();
	if (!enemy || enemy->query_name() != who)
	    obliterator->init_command(rest);
	check_violens();
    }
} /* handle_leaving */


/* Called when Obliterator died */
monster_died(poor_obliterator)
{
    object murderer, corpse;
    
    murderer = obliterator->query_attack();
    if (murderer && murderer == violens) {
	say("Sir Obliterator says: Ouch! I didn't know he was THAT tough!\n");
	say("In his dying breath Sir Obliterator mumbles a spell of teleport.\n");
	say("Sir Obliterator disappears in a puff of smoke.\n");
	move_object(obliterator, "players/padrone/store");
	corpse = present("corpse of obliterator", environment(murderer));
	if (corpse)
	    move_object(corpse, "players/padrone/store");
	return 0;
    }
    return 0;
} /* monster_died */


/* For the NEW, IMPROVED monster class: */
setup_arrays() {
    
    function = allocate(6);
    type = allocate(6);
    match = allocate(6);
    
    function[0] = "handle_say";
    type[0] = "says";
    match[0] = "";
    type[1] = "tells you:";
    match[1] = " ";
    function[2] = "handle_arrival";
    type[2] = "arrives";
    match[2] = "";
    function[3] = "handle_leaving";
    type[3] = "leaves";
    match[3] = "";
    function[4] = "check_violens";
    type[4] = "died";
    match[4] = "";
    type[5] = "killed";
    match[5] = "";
    
    chat_str = ({
	"Sir Obliterator says: Excuse me, Sir! Have you seen a prince called Violens?\n",
	"Sir Obliterator says: Can you show me to prince Violens?\n",
	"Sir Obliterator says: You! Where is that bastard Violens?\n",
	"Sir Obliterator says: In which direction can I find prince Violens?\n",
	"Sir Obliterator says: You! Peasant! Show me to prince Violens!\n",
	"Sir Obliterator says: Have you seen a prince who calls himself Violens?\n",
	"Sir Obliterator says: I need to find a prince called Violens.\n",
	"Sir Obliterator says: Take me to Violens!\n",
	"Sir Obliterator says: I have a message for prince Violens.\n",
	"Sir Obliterator says: I am fulfilling a quest that has been laid upon me.\n",
	"Sir Obliterator says: I'm on a mission from God. But not that God.\n",
	"Sir Obliterator looks dangerous.\n",
	"Obliterator looks at you threateningly.\n",
	"Sir Obliterator says: 200 gold coins if you lead me to prince Violens!\n",
	"Sir Obliterator says: Take me to Violens and earn 200 gold coins!\n"
    });

    a_chat_str = ({
	"Sir Obliterator grins evilly.\n",
	"Sir Obliterator says: Begone, jerk! I have other things to do!\n",
	"Sir Obliterator says: Don't try to stop me!\n",
	"Sir Obliterator says: So, you are a friend of Violens, are you?\n",
	"Sir Obliterator laughs insanely.\n",
	"Sir Obliterator says: Don't think you can even TOUCH me, you nerd!\n",
	"Sir Obliterator says: Who put you up to this? Violens?\n",
	"Sir Obliterator says: Prepare to die!\n",
	"Sir Obliterator says: If you run away, I will not kill you. Not now, that is.\n"
    });
} /* setup_arrays */
