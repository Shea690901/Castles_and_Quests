#include "std.h"

object guard;

/* For the NEW, IMPROVED monster class: */
string chat_str, a_chat_str, function, type, match;

#undef EXTRA_RESET
#define EXTRA_RESET extra_reset(arg);

extra_reset(arg) {

    if (!guard || !living(guard)) {
	object axe, helmet;
	
	guard = clone_object("obj/monster");		/* NEW, IMPROVED monster class! */
	guard->set_name("guard");
	guard->set_alias("drunk guard");
	guard->set_level(2);
	guard->set_hp(20);
	guard->set_al(15);
	guard->set_short("A somewhat hurt and very drunk guard");
        guard->set_long("This man seems to be a castle guard from a castle somewhere.\n" +
                        "He has obviously been in a fight, and now he is trying to forget\n" +
		        "his problems with the help of alcohol. He is roaring drunk.\n");
	guard->set_aggressive(0);
	
	/* The NEW, IMPROVED monster calls: */
	if (!chat_str)
	    setup_arrays();
	guard->load_chat(20, chat_str);
	move_object(guard, this_object());
	
	axe = clone_object("obj/weapon");
	axe->set_name("hand axe");
	axe->set_class(9);
	axe->set_value(25);
	axe->set_weight(2);
	axe->set_alt_name("axe");
	axe->set_short("A hand axe");
	move_object(axe, guard);
	guard->init_command("wield axe");
	
	helmet = clone_object("obj/armour");
	helmet->set_name("metal helmet");
	helmet->set_ac(1);
	helmet->set_weight(3);
	helmet->set_value(75);
	helmet->set_alias("helmet");
	helmet->set_type("helmet");
	helmet->set_short("a metal helmet");
	helmet->set_long("a metal helmet\n");
	move_object(helmet, guard);
	guard->init_command("wear helmet");
    }
} /* extra_reset */

TWO_EXIT("players/padrone/outside/crosspath1", "east",
	 "players/padrone/outside/small_lake", "south",
	 "North shore",
	 "You are at the northern shore of a small lake in the forest.\n" +
	 "The trees are impressingly beautiful, high and green,\n" +
	 "and in the clear water you can see a reflection of the blue sky.\n",
	 1)

/* For the NEW, IMPROVED monster class: */
setup_arrays() {
    chat_str = ({
	"The guard says: The bashtardsh shneaked up on ush.\n",
	"The guard says: They attacked us right in the middle of the plainsh.\n",
	"The guard says: Bloody MILLION of thoshe piratsh!\n",
	"The guard says: They jusht took the castle...\n",
	"The guard says: I wash lucky to get away alive.\n",
	"The guard says: Oh BOY will the Wish be pished when he hearsh about thish!\n",
	"The guard says: Who knowsh where the caschtle isch now?\n",
	"The guard says: They could have taken it anywhere by now! Yesh!\n",
	"The guard says: We were juscht walking around out in the plainsch up north.\n",
	"The guard says: Real nishe cashtle. Too bad the piratsh shtole it.\n",
	"The guard says: They are not really that tough, those piratsh...\n",
	"The guard says: A few guysh like you could handle this, you know.\n",
	"The guard says: That cashtle could be really usheful, you know.\n",
	"The guard says: I think they climbed up the rope ladder...\n",
	"The guard says: We were up north, in the plainsh.\n",
	"The guard seems to fall, but takes a step and recovers.\n",
	"The guard hiccups.\n",
	"The guard looks drunk.\n",
	"The guard burps.\n",
    });
} /* setup_arrays */
