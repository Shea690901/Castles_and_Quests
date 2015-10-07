string str,dir,shortdesc;

id(arg) {return arg=="facade";}

reset(arg) {
    if(arg) return 0;
    shortdesc="Not a valid facade";
    str="facade";
    dir="facade";
}

short() {
    return shortdesc;
}

long() {
    write("This is a facade.\n");
    write(arg+"\n"+str+"\n");
}

init() {
    add_action("move"); add_verb(dir);
}

move(str) {
    call_other(this_player(), "move_player", str);
    return 1;
}

setshort(arg) {
    shortdesc=arg;
}

setmove(arg) {
    str=arg;
}

setdir(arg) {
    dir=arg;
}

get() {
    return(call_other(this_player(),"query_level",0) >= 20);
}
