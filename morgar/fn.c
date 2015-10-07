id(arg) {return arg=="fnord";}

init() {
    add_action("null"); add_verb("fnord");
    add_action("null"); add_verb("f");
}

null(arg) {return 1;}
