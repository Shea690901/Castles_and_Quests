int i, charges;
object targetloc;

id(str) { return str == "mirror"; }

reset() {
    charges=random(6);
}

long() {
    write("A magical mirror is here.\n");
    if (i == 1) {
        write("Looking into the mirror you see:\n");
        call_other(targetloc,"long");
    }
}

short() {
     return "A magical mirror";
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
    if (!arg || arg != "mirror") {
        return 0;
    } else {
        if (i != 1) {
            write("The mirror has not had a destination set.\n");
            return 1;
        } else {
            realm=call_other(environment(this_player()),"realm",0);
            destrealm=call_other(targetloc,"realm",0);
            if ((realm == destrealm) && (realm != "NT")) {
                write("As you use the mirror everything shimmers away...\n");
                say(call_other(this_player(),"query_name") + " shimmers and fades.\n");
                move_object(this_player(), targetloc);
                say(call_other(this_player(),"query_name") + " shimmers into solidity.\n");
                call_other(this_player(),"look");
                if (charges == 1) {
                    move_object(this_object(), "players/morgar/store");
                    write("The mirror did not make it through the transport.\n");
                call_other(this_player(),"add_weight", -1);
                }
                charges=charges-1;
            } else {
                write("The mirror struggles to take you with it, but fails.\n");
                move_object(this_object(), targetloc);
                write("The mirror shimmers and fades!\n");
                call_other(this_player(),"add_weight", -1);
	    }
            return 1;
        }
    }
}

set(arg) {
    if (!arg || arg != "mirror") {
        return 0;
    } else {
        write("You set the mirror's destination.\n");
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
