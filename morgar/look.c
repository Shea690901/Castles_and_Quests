id(str) { return str == "look"; }

short() { return "look macro"; }

query_value() { return 0; }

long() {
    write("This is the look macro.\n");
}

init() { add_action("func"); add_verb("look"); }

func(str) {
    string a;
    if (!str || sscanf(str, "at%s", a) == 1) return 0;
    write("invoked\n");
    command("look at "+str);
    return 1;
}

get() { return 1; }
