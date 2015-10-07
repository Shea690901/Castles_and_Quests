int worn;
object next, worn_by;
string name;

id(str)
{
    return str == "ring" || str == "wedding ring";
}

short() {
    if(worn) {
	return "A diamond wedding ring (worn)";
    }
    return "A diamond wedding ring";
}

long() {
    write("A filigreed golden band, composed of three intricately intertwined\n");
    write("strands of fine gold. The crown setting is made of white gold, and\n");
    write("contains five small fine-cut diamonds in a tiny pentagonal pattern\n");
    write("with a sixth, larger diamond in the center of the pentagon. The\n");
    write("interior of the band is etched with a message:\n");
    write("\n");
    write("'To Portia, my love, on our wedding day.\n");
    write(" You will always be special to me.\n");
    write(" Love, Quantos'\n");
}

query_value() { return 1000000; }

get() {
    return 1;
}

query_weight() {
    return 1;
}

init() {
    add_action("read"); add_verb("read");
    add_action("wear"); add_verb("wear");
    add_action("drop"); add_verb("drop");
    add_action("remove"); add_verb("remove");
}

read(str) {
    if (str != "ring" &&  str != "wedding ring")
	return 0;
    write("To Portia, my love, on our wedding day.\n");
    write("Love, Quantos\n");
    return 1;
}

wear(str)
{
    object ob;

    if (!id(str))
	return 0;
    if (environment() != this_player()) {
	write("You must get it first!\n");
	return 1;
    }
    if (worn) {
	write("You're already wearing it!\n");
	return 1;
    }
    next = 0;
    ob = call_other(this_player(), "wear", this_object());
    if(!ob) {
	worn_by = this_player();
	worn = 1;
	return 1;
    }
}

drop() {
    if (worn) {
	call_other(worn_by, "stop_wearing",name);
	worn = 0;
	worn_by = 0;
    }
    return 0;
}

remove(str) {
    if (!id(str))
	return 0;
    if (!worn) {
	return 0;
    }
    call_other(worn_by, "stop_wearing",name);
    worn_by = 0;
    worn = 0;
    return 1;
}
