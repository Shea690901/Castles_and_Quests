#include "std.h"
int i, charges, price;
object targetloc;
string pointo;

id(str) { return str == "greystone"; }

reset(arg) {
    if (!arg) charges=random(6);
    price = charges * 20;
}

long() {
    write("A round pebble with no distinct features.\n");
}

short() {
     return "A small greystone";
}

query_value()
{
    return price;
}

init() {
    add_action("use"); add_verb("invoke");
    add_action("set"); add_verb("point");
    add_action("stat"); add_verb("stat");
}

use(arg) {
    string realm, destrealm;
    object otherplayer;

    if (!arg || arg != "greystone") {
        return 0;
    } else {
        if (i != 1) {
            return 1;
        } else {
            realm=call_other(environment(this_player()),"realm",0);
            otherplayer = find_living(pointo);
            if(otherplayer == 0) return 0;
            targetloc = environment(otherplayer);
            destrealm=call_other(targetloc,"realm",0);
            if ((realm == destrealm) && (realm != "NT")) {
                write("As you use the greystone everything shimmers away...\n");
                say(call_other(this_player(),"query_name") + " shimmers and fades.\n");
                move_object(this_player(), targetloc);
                say(call_other(this_player(),"query_name") + " shimmers into solidity.\n");
                call_other(this_player(),"look");
                if (charges == 0) {
                    move_object(this_object(), "players/morgar/store");
                    write("The greystone breaks and turns into dust.\n");
                    call_other(this_player(),"add_weight", -1);
                }
                charges=charges-1;
            } else {
                write("The greystone struggles to take you with it, but fails.\n");
                move_object(this_object(), targetloc);
                write("The greystone shatters from the strain!\n");
                call_other(this_player(),"add_weight", -1);
            }
            return 1;
        }
    }
}

set(arg) {

    if (!arg) {
        return 0;
    }
    else {

         pointo = lower_case(arg);
        write("The stone glows in your hand\n");
        i = 1;
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
    if (!arg || arg != "greystone" ||
        call_other(this_player(),"query_level",0)<20) return 0;
    write("Stone stats:\ncharges: "+charges+"\nsetting: "+pointo+"\n");
    return 1;
}
