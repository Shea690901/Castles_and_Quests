#include "std.h"

object eliza, client;

/* For the NEW, IMPROVED monster class: */
string chat_str, a_chat_str, function, type, match;

#undef EXTRA_RESET
#define EXTRA_RESET  if (!eliza) start_eliza();

#undef EXTRA_INIT
#define EXTRA_INIT  extra_init();

extra_init() {
    add_action("do_exit", "exit");
    add_action("do_exit", "out");
} /* extra_init */

do_exit() {
    this_player()->move_player("out#players/padrone/inside/courtyard");
    return 1;
}

ONE_EXIT("players/padrone/inside/courtyard", "southeast",
	 "Eliza's office",
	 "This is Eliza's office. Eliza is a psychiatrist,\n" +
	 "and usually she meets her clients here.\n" +
	 "But some days she takes the afternoon off and\n" +
	 "just walks around talking to people.\n", 1)

start_eliza() {

    eliza = clone_object("obj/monster");	/* NEW, IMPROVED monster class! */
    eliza->set_name("eliza");
    eliza->set_alias("Eliza");
    /* eliza->set_short("Eliza the psychiatrist"); */
    eliza->set_long("This is Eliza, a professional psychiatrist.\n" +
		    "She is middle-aged and a bit plump, and she looks at you\n" +
		    "understandingly.\n");
    eliza->set_level(3);
    eliza->set_female();
    eliza->set_al(100);
    eliza->set_aggressive(0);
    eliza->set_spell_mess1("Eliza gives some medicine to her patient.");
    eliza->set_spell_mess2("Eliza forces some vile-tasting medicine down your throat.");
    eliza->set_chance(10);
    eliza->set_spell_dam(10);
    
    move_object(call_other("players/padrone/outside/front_yard", "make_ticket"), eliza);
    move_object(eliza, this_object());
    
    /* The NEW, IMPROVED monster calls: */
    if (!chat_str)
	setup_arrays();
    eliza->load_chat(5, chat_str);
    eliza->load_a_chat(40, a_chat_str);
    eliza->set_match(this_object(), function, type, match);
} /* start_eliza */

notify(str) {
    say("Eliza says: " + str + "\n");
    write("Eliza says: " + str + "\n");
}

handle_say(str) {
    string who, phrase, a, b;
    int n;

    if (   (sscanf(str, "%s says: %s\n", who, phrase) != 2)
	&& (sscanf(str, "%s says \"%s\"\n", who, phrase) != 2)	/* Morgar's say with quotes! */
	&& (sscanf(str, "%s tells you: %s\n", who, phrase) != 2)) {
	say("Eliza looks brain damaged.\n");
	return;
    }
    if (who == "Eliza")
	return;
    /* phrase = lower_case(phrase); */
    client = present(lower_case(who), environment(eliza));
    if (!client) {
	say("Who said that? Eliza looks confused.\n");
	return;
    }

    if (sscanf(phrase, "%s %s", a, b) != 2) {
	say("Eliza says: You seem to be a bit short with me. Please tell me more!\n");
    }
    else if (sscanf(phrase, "%s?", a) == 1) {
	while (sscanf(phrase, "%s?", a) == 1)
	    phrase = a;
	say("Eliza says: Why do you ask if " + turn_phrase(phrase) + "?\n");
    }
    else if (   word_in_phrase("mother", phrase)
	     || word_in_phrase("father", phrase)
	     || word_in_phrase("sister", phrase)
	     || word_in_phrase("brother", phrase))
	say("Eliza says: Tell me more about your family!\n");
    else if (word_in_phrase("sex", phrase))
	say("Eliza says: Please tell me more. Don't forget any details.\n");
    else if (   word_in_phrase("computer", phrase)
	     || word_in_phrase("computers", phrase))
	say("Eliza says: You have your mind on computers, it seems.\n");
    else if (   word_in_phrase("monster", phrase)
	     || word_in_phrase("monsters", phrase))
	say("Eliza says: Why do you talk about monsters? There are no monsters.\n");
    else if (   word_in_phrase("kill", phrase)
	     || word_in_phrase("murder", phrase)
	     || word_in_phrase("weapon", phrase)
	     || word_in_phrase("destroy", phrase))
	say("Eliza says: This is not a healthy way of thinking.\n");
    else if (   word_in_phrase("Eliza", phrase)
	     || word_in_phrase("eliza", phrase))
	say("Eliza says: Don't talk about me, tell me about yourself instead.\n");
    else {
	while (sscanf(phrase, "%s!", a) == 1)
	    phrase = a;
	while (sscanf(phrase, "%s.", a) == 1)
	    phrase = a;
	n = random(6);
	if (n == 0) 
	    say("Eliza says: Maybe your life has something to do with this.\n");
	else if (n == 1) 
	    say("Eliza says: Go on, don't be afraid.\n");
	else if (n == 2) 
	    say("Eliza says: Perhaps this has something to do with your inhibitions?\n");
	else if (n == 3)
	    say("Eliza says: Do you say that because of some problems in your childhood?\n");
	else if (n == 4)
	    say("Eliza says: Why do you say that " + turn_phrase(phrase) + "?\n");
	else if (n == 5)
	    say("Eliza says: What makes you think that " + turn_phrase(phrase) + "?\n");
    }
    if (!random(20)) {
	tell_object(client, "Talking to Eliza is good for you. You feel mentally stronger.\n");
	client->restore_spell_points(4);
    }
} /* handle_say */


handle_arrival(str)
{
    string who, rest, n;

    if (sscanf(str, "%s arrives%s", who, rest) != 2) {
	say("Eliza looks brain damaged.\n");
	return;
    }
    if (who == "Eliza")
	return;
    client = present(lower_case(who), environment(eliza));
    if (!client) {
	say("Eliza looks confused.\n");
	return;
    }
    say("Eliza says: Hello, " + who + ". Tell me about your problems!\n");
} /* handle_arrival */


handle_leaving(str)
{
    string who, rest, n;

    if (sscanf(str, "%s leaves %s.\n", who, rest) != 2) {
	say("Eliza looks brain damaged.\n");
	return;
    }
    if (who == "Eliza")
	return;

    if (random(4)) {
	eliza->init_command(rest);
	if (present(lower_case(who), environment(eliza)))
	    say("Eliza says: Don't go yet, " + who + ". We must discuss your problems.\n");
    }

} /* handle_leaving */


turn_phrase(phrase)
{

	/* say("tf: phrase = '" + phrase + "'\n"); */

    phrase = replace_word(phrase, "yours", "PUT-MINE-HERE");
    phrase = replace_word(phrase, "your", "PUT-MY-HERE");
    phrase = replace_word(phrase, "you", "PUT-I-HERE");
    phrase = replace_word(phrase, "Your", "PUT-MY-HERE");
    phrase = replace_word(phrase, "You", "PUT-I-HERE");

	/* say("tf: phrase = '" + phrase + "'\n"); */

    phrase = replace_word(phrase, "I", "you");
    phrase = replace_word(phrase, "i", "you");
    phrase = replace_word(phrase, "me", "you");
    phrase = replace_word(phrase, "my", "your");
    phrase = replace_word(phrase, "My", "your");
    phrase = replace_word(phrase, "mine", "yours");

    phrase = replace_word(phrase, "PUT-I-HERE", "I");
    phrase = replace_word(phrase, "PUT-MY-HERE", "my");
    phrase = replace_word(phrase, "PUT-MINE-HERE", "mine");

    phrase = replace_word(phrase, "I are", "I am");
    phrase = replace_word(phrase, "are I", "am I");

    phrase = replace_word(phrase, "you am", "you are");
    phrase = replace_word(phrase, "am you", "are you");

	/* shout("tf: phrase = '" + phrase + "'\n"); */

    return phrase;
}

replace_word(phrase, replace_from, replace_to) {
    string a, b;

    phrase = "BEGIN-SENTINEL " + phrase + " END-SENTINEL";
    while (sscanf(phrase, "%s " + replace_from + " %s", a, b) == 2)	/* " from " */
	phrase = a + " " + replace_to + " " + b;
    while (sscanf(phrase, "%s " + replace_from + ",%s", a, b) == 2)	/* " from," */
	phrase = a + " " + replace_to + "," + b;
    while (sscanf(phrase, "%s " + replace_from + ".%s", a, b) == 2)	/* " from." */
	phrase = a + replace_to + "." + b;
    while (sscanf(phrase, "%s " + replace_from + "!%s", a, b) == 2)	/* " from!" */
	phrase = a + " " + replace_to + "!" + b;
    sscanf(phrase, "BEGIN-SENTINEL %s END-SENTINEL", phrase);
    return phrase;
} /* replace_word */


word_in_phrase(word, phrase)
{
    string a, b;

    return (sscanf("BEGIN-SENTINEL " + phrase + " END-SENTINEL", "%s " + word + "%s", a, b) == 2);
} /* word_in_phrase */


/* For the NEW, IMPROVED monster class: */
setup_arrays() {

    chat_str = ({
	"Eliza says: Tell me about your problems!\n",
	"Eliza says: Tell me about your mother!\n",
	"Eliza says: Lie down and tell me about your problems!\n",
	"Eliza says: How do you feel?\n",
	"Eliza looks at you understandingly.\n"
    });

    a_chat_str = ({
	"Eliza says: It is obvious that you have some serious problems.\n",
	"Eliza says: Haven't you taken your medicine today?\n",
	"Eliza says: Have you had these violent tendencies before?\n",
	"Eliza says: For your own good, you should be put in a hospital.\n",
	"Eliza says: Wait here for the nice young men in the clean white coats.\n",
	"Eliza says: This case is too hard for me. Consult Sir Obliterator instead.\n"
    });
    
    function = allocate(4);
    type = allocate(4);
    match = allocate(4);

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
} /* setup_arrays */
