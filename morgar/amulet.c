int i, charges;
object targetloc;

id(str) { return str == "amulet"; }

reset(arg) {
    if (!arg) charges=random(6);
}

long() {
    write("A small magical amulet is here.\n");
    if (i == 1) {
        write("Looking into the amulet you see:\n");
        call_other(targetloc,"long");
    }
}

short() {
     return "A small magical amulet";
}

query_value()
{
    return 100;
}

init() {
    add_action("use"); add_verb("use");
    add_action("set"); add_verb("set");
    add_action("stat"); add_verb("stat");
}

use(arg) {
    string realm, destrealm;
    object ob;
    if (!id(arg)) {
        return 0;
    } else {
        if (i != 1) {
            write("The amulet has not had a destination set.\n");
            return 1;
        } else {
	  ob = first_inventory(this_player());
	  while(ob) {
	    if (call_other(ob, "id", "drk2")) {
	      tell_object(this_player(),
			"You are not allowed to leave with drinks!\n");
	      return 1;
	    }
	    ob = next_inventory(ob);
	  }
            realm=call_other(environment(this_player()),"realm",0);
            destrealm=call_other(targetloc,"realm",0);
            if ((realm == destrealm) && (realm != "NT")) {
                write("As you use the amulet everything shimmers away...\n");
                say(call_other(this_player(),"query_name") + " shimmers and fades.\n");
                move_object(this_player(), targetloc);
                say(call_other(this_player(),"query_name") + " shimmers into solidity.\n");
		call_other(this_player(),"look",0);
                if (charges == 1) {
                    move_object(this_object(), "players/morgar/store");
                    write("The amulet did not make it through the transport.\n");
                    call_other(this_player(),"add_weight", -1);
                }
                charges=charges-1;
            } else {
                write("The amulet struggles to take you with it, but fails.\n");
                move_object(this_object(), targetloc);
                write("The amulet shimmers and fades!\n");
                call_other(this_player(),"add_weight", -1);
	    }
            return 1;
        }
    }
}

set(arg) {
    if (!arg || arg != "amulet") {
        return 0;
    } else {
        write("You set the amulet's destination.\n");
        targetloc = environment(this_player());
        i=1;
    }
    return 1;
}

get() {
    return 1;
}

query_weight() {
    return 1;
}

stat(arg) {
    if (!arg || arg!="amulet" ||
        call_other(this_player(),"query_level",0)<20) return 0;
    write("Amulet stats:\ncharges:");
    write(charges);
    write("\ndestination:");
    write(targetloc);
    write("\n");
}
