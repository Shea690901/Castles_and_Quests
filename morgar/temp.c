string targetloc;
string str,dir,shortdesc;

id(arg) {return arg=="facade";}

reset(arg) {
    if(arg) return 0;
    shortdesc="Not a valid facade";
    str="facade";
    dir="facade";
}

short() { return shortdesc; }

long() {
    write("This is a facade.\n");
    write(arg+"\n"+str+"\n");
}

init() {
    add_action("move"); add_verb(dir);
    add_action("use"); add_verb("use");
    add_action("use"); add_verb("enter");
    add_action("set"); add_verb("set");
}

move(str) {
    call_other(this_player(), "move_player", str);
    return 1;
}

setshort(arg) { shortdesc=arg; }

setmove(arg) { str=arg; }

setdir(arg) { dir=arg; }

get() { return(call_other(this_player(),"query_level",0) >= 20); }

use(arg) {
    if (!arg || arg != "facade") return 0;
    write("You step through the mirror.\n");
    say(call_other(this_player(),"query_name") + " steps into a mirror.\n");
    move_object(this_player(), targetloc);
    say(call_other(this_player(),"query_name") + " steps out of a mirror.\n");
    call_other(this_player(),"command","look");
    return 1;
}

set(arg) {
    if (!arg || arg != "facade") return 0;
    if (environment(this_object()) != this_player()) return 0;
    write("You set the facade's destination.\n");
    targetloc = environment(this_player());
    return 1;
}

roomset(arg) { targetloc = arg; }
