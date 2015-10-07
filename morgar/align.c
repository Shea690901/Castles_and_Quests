int i;
string targetloc;

id(str) {
       return str == "alignglobe";
        }


reset() {
       i=1;
       }

long() {
    write("A small magical alignglobe is here.\n");
    }

short() {
     return "A small magical alignglobe";
}

query_value()
{
    return 200;
}

init() {
    add_action("use"); add_verb("use");
}

use(arg) {
    if (arg && arg != "alignglobe") {
       write("use what?\n");
    } else {
    write("You feel changed...\n");
    call_other(this_player(), "add_alignment", 1000);
    return 1;
}
}

get() {
    return 0;
}

query_weight() {
    return 1;
}
