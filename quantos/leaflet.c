short() {
    return "A leaflet" ;
}

long() {
    cat("/open/LEAFLET");
}

init() {
    add_action("read"); add_verb("read");
}

id(str) {
    return str == "leaflet" || str == "pamphlet";
}

read(str) {
    if (!id(str))
	return 0;
    say(call_other(this_player(), "query_name") + " reads the leaflet.\n");
    long();
    return 1;
}

query_weight() { return 1; }

get() { return 1; }

query_value() { return 3; }
