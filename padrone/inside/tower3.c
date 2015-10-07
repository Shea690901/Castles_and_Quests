#include "std.h"

object witness;
string chat_str, a_chat_str;

#undef EXTRA_RESET
#define EXTRA_RESET extra_reset(arg);

extra_reset() {
    if (!witness) {
	witness = clone_object("obj/monster");
	witness->set_name("witness");
	witness->set_alias("witness of jehova");
	witness->set_level(3);
	witness->set_al(100);
	witness->set_short("One of Jehova's Witnesses");
	witness->set_long("This is person is a Witness of Jehova.\n" +
			  "He is not actually ugly, and he shows no obvious signs of insanity,\n" +
			  "but he has that unmistakable look of a disciple of Jehova.\n" +
			  "If he came knocking on your door,\n" +
			  "you wouldn't let him in.\n");
	witness->set_aggressive(0);
	witness->set_male();

	witness->set_spell_mess1("Witness tries to exorcise a demon from his attacker.");
	witness->set_spell_mess2("Witness tries to exorcise a demon from you. Ouch! That hurt!");
	witness->set_chance(20);
	witness->set_spell_dam(10);

	if (!chat_str)
	    setup_arrays();
	witness->load_chat(50, chat_str);
	witness->load_a_chat(50, a_chat_str);
	move_object(witness, this_object());
    }
} /* extra_reset */

TWO_EXIT("players/padrone/inside/tower_top", "up",
	 "players/padrone/inside/tower2", "down",
	 "Staircase in the tower",
	 "You are standing on a dark, narrow staircase in the watchtower,\n" +
	 "which is the smaller of the two towers in Padrone's castle.\n" +
	 "If you continue upwards, you will arrive at the top of the tower,\n" +
	 "and can you see light shining down from there.\n", 1)

setup_arrays() {
    chat_str = ({
        "Witness says: Armageddon is close!\n",
        "Witness says: Do you really believe that the world was created by accident?\n",
        "Witness says: 6000 years ago, the world was created. Yes, created!\n",
        "Witness says: The Milennium is close!\n",
        "Witness says: Man was created by a higher intelligence. Isn't that obvious?\n",
        "Witness says: An explosion in a library will not create the Bible!\n",
        "Witness says: Let me give you this book!\n",
        "Witness says: Hallelujah!\n",
        "Witness says: Amen.\n",
        "Witness says: Oh yes, the devil is real. How could he else have fooled\n" +
	"              so many people to think that he doesn't exist?\n",
        "Witness says: Evil spirits sometimes pose as dead people to fool the living.\n",
        "Witness says: No, we don't use the cross as our symbol.\n",
        "Witness says: 144000, that's right.\n"
    });
    a_chat_str = ({
        "Witness says: You are possessed! I exorcise you! Begone, foul spirit!\n",
        "Witness says: Jehova, I am ready!\n",
        "Witness says: Jehova! Help!\n",
        "Witness says: Go away! Can't you see I'm a Witness of Jehova?\n",
    });
} /* setup_arrays */
