/* secret_police/cell.c */

#include "std.h"

object spy;
string chat_str, function, type, match;

#undef EXTRA_RESET
#define EXTRA_RESET extra_reset();

extra_reset() {
    if (!chat_str) {

	chat_str = ({
	    "The enemy spy glares at you.\n",
	    "The enemy spy says nothing.\n",
	});
	
	function = allocate(2);
	type = allocate(2);
	match = allocate(2);

	function[0] = "handle_say";
	type[0] = "says";
	match[0] = "";
	type[1] = "tells you:";
	match[1] = " ";
    }

    if (!spy) {
	spy = clone_object("obj/monster");
	spy->set_name("spy");
	spy->set_alias("enemy spy");
	spy->set_short("An enemy spy");
	spy->set_long("This is an enemy spy that has been arrested by the Secret Police.\n" +
		      "He is small, devious, and dressed in a black coat and hat.\n");
	spy->set_level(3);
	spy->set_hp(100);
	spy->set_al(-300);
	spy->set_male();

	spy->set_spell_mess1("The spy hits his opponent with a karate kick.");
	spy->set_spell_mess2("The spy hits you with a karate kick. You are hurt!");
	spy->set_chance(20);
	spy->set_spell_dam(20);
	spy->load_chat(20, chat_str);
	spy->set_match(this_object(), function, type, match);

        move_object(spy, this_object());
    }

} /* extra_reset */

ONE_EXIT("players/padrone/secret_police/interrogation_room", "east",
	 "The Secret Police cell",
	 "This is a small room used by the Secret Police to put spies\n" +
	 "and dangerous terrorists in.\n", 1)

handle_say(str) {
    string who, junk;
    object client;

    if (   (sscanf(str, "%s say%s\n", who, junk) != 2)
	&& (sscanf(str, "%s tell%s\n", who, junk) != 2)) {
	return;
    }
    else {
	client = present(lower_case(who), environment(spy));
	if (client) {
	    say("Spy says: You lie! Take this, you capitalist lackey!\n");
	    spy->attacked_by(client);
	}
    }
} /* handle_say */
