status wielded;
string wielded_by;
string name_of_weapon;
string alt_name;
int class_of_weapon;
int value;
int local_weight;

query_name() { return name_of_weapon; }

long() {
    write(short() + ".\n");
}

reset(arg) {
    if (arg)
	return;
    wielded = 0; value = 0;
}

init() {
    add_action("wield"); add_verb("wield");
}

wield(str) {
    if (!id(str))
	return 0;
    if (environment() != this_player()) {
	write("You must get it first!\n");
	return 1;
    }
    if (wielded) {
	write("You already wield it!\n");
	return 1;
    }
    wielded_by = this_player();
    call_other(this_player(), "wield", this_object());
    wielded = 1;
    return 1;
}

short() {
    if (wielded)
	return name_of_weapon + " (wielded)";
    return name_of_weapon;
}

weapon_class() {
    return class_of_weapon;
}

id(str) {
    return str == name_of_weapon || str == alt_name;
}

drop(silently) {
    if (wielded) {
	call_other(wielded_by, "stop_wielding");
	wielded = 0;
	if (!silently)
	    write("You drop your wielded weapon.\n");
    }
    return 0;
}

un_wield() {
    if (wielded)
	wielded = 0;
}

set_class(c) {
    class_of_weapon = c;
}

set_name(n) {
    name_of_weapon = n;
}

query_value() {
    return value;
}

set_value(v) {
    value = v;
}

query_weight() { return local_weight; }

set_weight(w) { local_weight = w; }

get() { return 1; }

set_alt_name(n)
{
    alt_name = n;
}
