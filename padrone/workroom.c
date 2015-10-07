/* Padrone's workroom */

#include "config.h"

object remembered_pad;          /* A pointer to Padrone */

reset(arg) {
    tell_room(this_object(), "The room says: I got a reset with argument " + arg + ".\n");
    if (!arg) {
	set_light(1);
    }
} /* reset */

init() {
    add_action("check_get", "get");
    add_action("check_get", "take");
    add_action("down", "down");
    add_action("up", "up");
    add_action("in", "in");
    add_action("hall", "hall");
    add_action("church", "church");
    add_action("shop", "shop");
    add_action("pub", "pub");
    add_action("post", "post");
    add_action("bboard", "bboard");
    add_action("wizboard", "wizboard");
    add_action("read", "read");
    add_action("press", "press");
    add_action("press", "push");
    add_action("money", "money");
    if (this_player()->query_level() < 20) {
	add_action("do_people", "people");
	add_action("do_echo", "echo");
	add_action("do_emote", "emote");
	add_action("do_wizlist", "wizlist");
    }
    
    if (!is_padrone()) {
	string the_name;

	the_name = this_player()->query_name();
	if (!remembered_pad)
	    remembered_pad = find_living("padrone");
	if (remembered_pad) {
	    tell_object(remembered_pad, "\n");
	    tell_object(remembered_pad, "*** Message from your workroom: " +
			the_name + " entered.\n");
	}
	log_file("padrone", ctime(time()) + ": " + the_name + " entered my workroom.\n");
    }
} /* init */

check_get(str) {
    if (!str)
	return 0;
    else if (!is_padrone()) {
	write("The Wizard has cast a permanent spell, making all\n" +
	      "loose objects in this room being magically glued\n" +
	      "to the floor. Only he can pick them up. Sorry.\n");
	return 1;
    }
    else
	return 0;
} /* check_get */

down() {
    this_player()->move_player("down#players/padrone/tower/hall");
    return 1;
}

up() {
    if (!is_padrone())
	write("That ladder is enchanted, and can only be used by the one who built it.\n" +
	      "It leads up to a special storeroom that only the Wizard may enter.\n");
    else
	this_player()->move_player("up#players/padrone/store");
    return 1;
}

in(str) {
    if (str)
	return 0;
    if (!is_padrone())
	write("You try to enter Padrone's private room, but the door is\n" +
	      "enchanted and can only be used by the Wizard himself. Sorry.\n");
    else
	this_player()->move_player("in#players/padrone/tower/home");
    return 1;
}

hall() {
    this_player()->move_player("through a magic door#players/padrone/inside/main_hall");
    return 1;
}

church() {
    this_player()->move_player("through a magic door#room/church");
    return 1;
}

shop() {
    this_player()->move_player("through a magic door#room/shop");
    return 1;
}

pub() {
    this_player()->move_player("through a magic door#room/pub2");
    return 1;
}

post() {
    this_player()->move_player("through a magic door#room/post");
    return 1;
}

bboard() {
    this_player()->move_player("through a magic door#room/adv_guild");
    return 1;
}

wizboard() {
    if (this_player()->query_level() < 20)
	write("You notice that there is a sign on that door saying 'WIZARDS ONLY'. Sorry.\n");
    else
	this_player()->move_player("through a magic door#room/adv_inner");
    return 1;
}

read(str) {
    if (book_id(str)) {
	say(this_player()->query_name() +
	    " reads the instruction manual.\n");
	write("This is an instruction manual for magic, covering\n" +
	      "every aspect of magic known to mankind.\n" +
	      "You open the book and start to read it.\n" +
	      "It is written in a mixture of Bulgarian and FORTRAN-IV on\n" +
	      "2000 pages of very small print filled with references\n" +
	      "to Appendix A, B and C (which are missing).\n" +
	      "Numerous coffee stains and small acid holes, left by the\n" +
	      "careless Wizard, makes it even harder to read.\n" +
	      "You understand nothing, except one short passage about\n" +
	      "how you can make money by doing it.\n");
	return 1;
    }
    else if (note_id(str)) {
	say(this_player()->query_name() +
	    " reads the note.\n");
	write("You read the note:\n");
	cat("/players/padrone/MESSAGE");
	return 1;
    }
    else
	return 0;
} /* read */

press(str) {
    int antal;
    
    if (str == "button") {
	write("You press the DESTRUCT button!\n");
	write("An alarm signal begins to wail (oo-i-ooo-iii!), indicating that\n");
	write("everything in this room will be recursively destroyed,\n" +
	      "except for players and what they are carrying.\n");
	say(this_player()->query_name() + " pressed the DESTRUCT button!\n");
	say("An alarm signal begins to wail (oo-i-ooo-iii!), indicating that\n");
	say("everything in this room will be recursively destroyed,\n" +
	    "except for players and what they are carrying.\n");
	antal = destruct_contents(this_object());
	write("\n");
	say("\n");
	write(antal + " objects were destructed.\n");
	say(antal + " objects were destructed.\n");
	return 1;
    }
    else
	return 0;
} /* read */

money(str) {
    int amount;
    object money;
    
#ifdef EXPORT
    /* Export version: No cheating by pseudo-padrones! */
    amount = 1 - random(3);
#else
    if (!is_padrone())
	amount = 1 - random(3);
    else if (!str)
	amount = 100000;
    else
	sscanf(str, "%d", amount);
#endif

    write("POP! Created " + amount + " gold coins...\n");
    say(this_player()->query_name() + " magically created some money.\n");
    this_player()->add_money(amount);
    return 1;
} /* money */


do_people() {
    write("These people are playing (with locations in the real world and in mud):\n");
    list_peoples();	/* Used to be: people(); */
    return 1;
} /* do_people */

/* list_peoples -- copied from players.c */
static list_peoples() {
    object list;
    int i;
    
    list = users();
    while(i<sizeof(list)) {
	string name;
	name = list[i]->query_real_name();
	if (!name)
	    name = list[i]->query_name();
	if (!name)
	    name = "logon";
	name = capitalize(name);
	if (list[i]->short() == 0)
	    name = "(" + name + ")";
	if (strlen(name) < 8)
	    name = name + "\t";
	write(query_ip_number(list[i]) + "\t" + name + "\t" +
	      list[i]->query_level() + "\t");
	if (environment(list[i]))
	    write(file_name(environment(list[i])));
	write("\n");
	i += 1;
    }
    return 1;
} /* list_peoples */

do_echo(str) {
    if (!str) {
	write ("Echo what?\n");
	return 1;
    }
    say (str + "\n");
    write ("You echo: " + str + "\n");
    return 1;
} /* do_echo */


do_emote(str) {
    string pn;
    
    if (!str) {
	write("Emote what ?\n");
	return 1;
    }
    pn = this_player()->query_name();
    say(pn + " " + str + "\n");
    write ("You emote: " + pn + " " + str + "\n");
    return 1;
} /* do_emote */

do_wizlist(arg) {
    if (arg)
        wizlist(arg);
    else
        wizlist();
    return 1;
} /* do_wizlist */


short() {
    return "Padrone's workroom";
}

long(str) {
    if (set_light(0) == 0) {
	write("It is dark, but the magic in this room enables you to see anyway.\n");
    }
    
    if (book_id(str)) {
	write("This is a book with the title MUD MAGIC INSTRUCTION MANUAL.\n" +
	      "It is thick and seems very solid in its black leather cover.\n" +
	      "It has been heavily used and looks a bit worn.\n");
	return;
    }

    if (note_id(str)) {
	write("This is a small note on the wall.\n" +
	      "It must have been put there by Padrone for visitors to read.\n" +
	      "Why not read it?\n");
	return;
    }
    
    if (cmd_id(str)) {
	write("Some commands that must have been left here by the carless Wizard:\n" +
	      "    people - an extended 'who'\n" +
	      "    echo - echo a string to everyone in the room\n" +
	      "    emote - like echo but with your name prepended\n" +
	      "    wizlist - print the wizards' high-score list, including mysterious numbers\n" +
	      "Feel free to use them while you are here!\n");
	return;
    }
    
    if (str == "button") {
	write("A big red button on the wall.\n" +
	      "Above it is a sign saying: WARNING! DESTRUCT!\n");
	return;
    }
    
    if (is_padrone())
	write("You are in your private workroom.\n");
    else
	write("You have managed to reach the private workroom of Padrone,\n" +
	      "the powerful and famous Wizard.\n" +
	      "It is a rather small and sparsely furnished room high up in the\n" +
	      "Wizard's tower, where the walls themselves positively reek with magic.\n" +
	      "You feel that maybe even you can do some magic in this place of power,\n" +
	      "but, as always, magic is a dangerous thing to tamper with for those\n" +
	      "who are not adept at it...\n" +
	      "A wooden ladder leads up through an opening in the ceiling,\n" +
	      "a stone stairway leads down to the tower hall, and a small door\n" +
	      "leads into Padrone's private room, were noone else can enter.\n" +
	      "On the walls you can see several strange-looking doors,\n" +
	      "seemingly painted on the stone, and labeled 'HALL', 'SHOP' and so on...\n");
    write("There are many exits to choose from:\n" +
	  "    up, down, in, hall, church, shop, pub, post, bboard and wizboard.\n" +
	  "There is a 2000-page instruction manual lying on a table.\n" +
	  "There is a big red button on the wall.\n" +
	  "There is a note on the wall too.\n"+ 
	  "There are some wizard commands lying in a corner.\n");
} /* long */


is_padrone() {
    if (remembered_pad)
	return this_player() == remembered_pad;
    else
	return this_player()->query_name() == "Padrone";
}

book_id(str) {
    return (   str == "instruction manual"
	    || str == "2000-page instruction manual"
	    || str == "manual"
	    || str == "book"
	    || str == "instructions");
}

note_id(str) {
    return (   str == "note"
	    || str == "small note"
	    || str == "note on wall"
	    || str == "note on the wall");
}

cmd_id(str) {
    return (   str == "commands"
	    || str == "wizard command"
	    || str == "command"
	    || str == "wizard commands");
}

id(str) {
    return !str  || book_id(str) || note_id(str) || str == "button" || cmd_id(str);
}

destruct_contents(mama_obj) {
    object an_obj, this_obj;
    int nr_destroyed;
    
    nr_destroyed = 0;
    an_obj  = first_inventory(mama_obj);
    
    while (an_obj) {
	this_obj = an_obj;
	an_obj = next_inventory(an_obj);
	if (!living(this_obj) || this_obj->query_npc()) {
	    nr_destroyed += destruct_contents(this_obj);
	    destruct(this_obj);
	    say("Zap! ");
	    write("Zap! ");
	    nr_destroyed += 1;
	}
    }
    
    return nr_destroyed;
} /* destruct_contents */
