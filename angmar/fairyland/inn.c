#include <door.h>

#define MUST_STAY_WITH_DRINKS

object drunkard,key_obj,amulet;

realm() { return ("NT"); }
external_reset() {
  drunkard=present("drunkard");
  if(!drunkard) {
    string chat_str;
    string a_chat_str;
    drunkard=clone_object("obj/monster");
    call_other(drunkard,"set_name","drunkard");
    call_other(drunkard,"set_level",14);
    call_other(drunkard,"set_hp",150);
    call_other(drunkard,"set_wc",12);
    call_other(drunkard,"set_ac",5);
    call_other(drunkard,"set_short","The drunkard");
    call_other(drunkard,"set_al",20);

    if(!chat_str) {
      a_chat_str=allocate(3);
      chat_str=allocate(3);
      a_chat_str[0]=
	"The drunkard says: Schtop that!\n";
      a_chat_str[1]=
	"The drunkard says: What do you think you're doing?\n";
      a_chat_str[2]=
	"The drunkard holds the beer in one hand while he tries to\n"+
	"hit you with his other hand.\n";
      chat_str[0]=
	"The drunkard says: I've schlayed many dragonsch in my life!\n";
      chat_str[1]=
	"The drunkard says: I'm a great dragonschlayer!\n";
      chat_str[2]=
	"The drunkard says: I know of a big dragon in the mountainsch nearby.\n"+
	  "I'm gonna kill him today, but I muscht have another beer first.\n";
      drunkard->load_chat(13,chat_str);
      drunkard->load_a_chat(40,a_chat_str);
    }

    amulet=clone_object("obj/armour");
    call_other(amulet,"set_name","amulet");
    call_other(amulet,"set_short","A small amulet");
    call_other(amulet,"set_long","It is a beautiful stone in a necklace.\n");
    call_other(amulet,"set_value",100);
    call_other(amulet,"set_type","amulet");
    move_object(amulet,drunkard);
    move_object(drunkard,"players/angmar/fairyland/inn");
  }

  if(!present("key",drunkard)) {
    MAKE_KEY(key_obj,"big","auxd")
    move_object(key_obj,drunkard);
  }

}

reset(arg) {
  if (!arg) {
    set_light(1);
  }
  external_reset();
}

short() {
    return "The inn Laughing Horse";
}

init() {
    add_action("move"); add_verb( "west");
    add_action("order"); add_verb("order");
    add_action("order"); add_verb("buy");
}

#if 0
move() {
    object ob;

    ob = first_inventory(this_player());
    while(ob) {
	if (call_other(ob, "id", "drk2")) {
	    tell_object(this_player(),
			"You are not allowed to leave with drinks!\n");
	    return 1;
	}
	ob = next_inventory(ob);
    }
    call_other(this_player(), "move_player",  "west" + "#"+
                      "players/angmar/fairyland/road2");
    return 1;
}
#else
move() {
#ifdef MUST_STAY_WITH_DRINKS
     if (has_drink(this_player())) {
        tell_object(this_player(),
                    "You are not allowed to leave with drinks!\n");
        return 1;
     }
#endif
     call_other(this_player(), "move_player",  "west" + "#" +
		"players/angmar/fairyland/road2");
     return 1;
}

#ifdef MUST_STAY_WITH_DRINKS
has_drink(obj) {
     status drink;
     object ob;
     ob = first_inventory(obj);
     while(ob) {
        if (call_other(ob, "id", "drk2"))
             drink = 1;
        if (call_other(ob,"can_put_and_get")) {
             if (has_drink(ob))
                  drink = 1;
        }
        ob = next_inventory(ob);
     }
     return drink;
}
#endif
#endif

long() {
    write("You are in the inn Laughing Horse.\n");
    write("You can order drinks here.\n\n");
    write("     A large beer                    : 12 coins\n");
    write("     Whiskey on the rocks            : 50 coins\n");
    write("     The doctor's special mixture    : 150 coins\n\n");
    write("The only obvious exit is to " +  "west" + ".\n\n");
}

order(str)
{
    object drink;
    string name, short_desc, mess;
    int value, cost, strength, heal;

    if (!str) {
       write("Order what ?\n");
       return 1;
    }

    if (str == "beer") {
	name = str;
	short_desc = "A large beer";
	mess = "Wow, best beer you've ever tasted";
	heal = 0;
	value = 12;
	strength = 2;
    }

    else if (str == "whisky" || str == "whiskey") {
	name = "whiskey";
	short_desc = "A whiskey on the rocks";
	mess = "Steam comes out of your ears";
	heal = 10;
	value = 50;
	strength = 8;
    } else if (str == "mixture" || str == "special") {
	name = "mixture";
	short_desc = "Doctor's special mixture";
	mess = "Your guts catch fire";
	heal = 25;
	value = 150;
	strength = 12;
    } else {
       write("What ?\n");
       return 1;
    }
    if (call_other(this_player(), "query_money", 0) < value) {
        write("That costs " + value + " gold coins, which you don't have.\n");
	return 1;
    }
    drink = clone_object("obj/drink");
    if (!call_other(this_player(), "add_weight",
	call_other(drink, "query_weight"))) {
	write("You can't carry more.\n");
	destruct(drink);
	return 1;
    }
    if (!call_other(drink, "set_value", name + "#" + short_desc + "#" + mess +
	"#" + heal + "#" + value + "#" + strength)) {
	write("Error in creating drink.\n");
	destruct(drink);
	return 1;
    }
    call_other(drink, "set_pub");
    move_object(drink, this_player());
    call_other(this_player(), "add_money", - value);
    write("You pay " + value + " for a " + name + ".\n");
    say(call_other(this_player(), "query_name", 0) + " orders a " +
	name + ".\n");
    return 1;
}

