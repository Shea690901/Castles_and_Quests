#include "std.h"
    
object mathilda;

/* For the NEW, IMPROVED monster class: */
string chat_str, a_chat_str, function, type, match;

#undef EXTRA_RESET
#define EXTRA_RESET extra_reset();

extra_reset() {
    if (!mathilda)
	make_mathilda();
}

TWO_EXIT("players/padrone/outside/crossing", "north",
	 "players/padrone/outside/front_yard", "south",
	 "A small path",
	 "You are on a small path winding through the bushes.\n", 1)
  
/* --------- The code for Mathilda is below this line --------- */
  
make_mathilda() {
    object dagger, bag, torch;
    
    mathilda = clone_object("obj/monster");		/* NEW, IMPROVED monster class! */
    mathilda->set_name("mathilda");
    mathilda->set_level(2);
    mathilda->set_ep(100);
    mathilda->set_hp(7);
    mathilda->set_al(150);
    mathilda->set_short("Mathilda the small thief (good)");
    mathilda->set_long("Mathilda is a dressed in black clothes, and she carries a dagger\n" +
		       "and a bag to carry things in. She is probably a thief.\n" +
		       "But something terrible has happened to Mathilda, and she\n" +
		       "is horribly hurt. She will probably die any minute now.\n");
    mathilda->set_aggressive(0);
    mathilda->set_spell_mess1("Mathilda bleeds a little.");
    mathilda->set_spell_mess2("Mathilda bleeds on you.");
    mathilda->set_chance(20);
    mathilda->set_spell_dam(0);
    
    move_object(mathilda, this_object());
    /* The NEW, IMPROVED monster calls: */
    if (!chat_str)
	setup_arrays();
    mathilda->load_chat(20, chat_str);
    
    dagger = clone_object("obj/weapon");
    dagger->set_name("dagger");
    dagger->set_class(7);
    dagger->set_value(10);
    dagger->set_weight(1);
    dagger->set_short("A dagger");
    dagger->set_long("This is an ordinary dagger, like the ones thieves often carry.\n");
    move_object(dagger, mathilda);
    mathilda->init_command("wield dagger");
    
    bag = clone_object("obj/bag");
    move_object(bag, mathilda);
    
    torch = clone_object("obj/torch");
    torch->set_name("torch");
    torch->set_fuel(2000);
    torch->set_weight(1);
    move_object(torch, bag);
} /* make_mathilda */

/* For the NEW, IMPROVED monster class: */
setup_arrays() {
    chat_str = ({
	"Mathilda groans.\n",
	"Mathilda groans loudly.\n",
	"Mathilda looks very bad.\n",
	"Mathilda coughs. She looks real bad now.\n",
	"Mathilda says: Oh, why didn't I buy that ticket...\n",
	"Mathilda says: As soon as I got in there, they saw that I had no ticket.\n",
	"Mathilda says: Whatever you do, don't forget to buy a ticket!\n",
	"Mathilda says: I think I'm going to die.\n",
	"Mathilda says: I should have bought a ticket at the gate... Arrrgh!\n",
	"Mathilda says: Don't you EVER drop your ticket while inside.\n",
	"Mathilda says: Don't make my mistake. Buy a ticket! Arrrgh!\n",
	"Mathilda says: The castle south of here... The ticket... Arrrgh...\n",
	"Mathilda says: The giants were bad, but the dragon was worse.\n",
	"Mathilda says: If you don't have a ticket, all of them will attack you!\n"
    });
} /* setup_arrays */
