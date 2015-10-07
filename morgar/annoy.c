int i, level;
string name;
object nasty,player,room;

setvars() {
    player = this_player();
    room = environment(player);
    name = call_other(player,"query_name",0);
}

id(str) { return ((str == "annoy") || (str == "annoyance")); }

reset() {
    setvars();
    if (environment(this_object())==environment(this_player()) {
        nasty(1);
    }
    destruct(this_object());
}

long() {
    write("You should never see this description.\n");
}

short() { return "Morgar's annoyance"; }

query_value() { return 0; }

get() { return 0; }

query_weight() { return 5; }

nasty() {
        tell_room(room, "A demon appears in a blast of fire!\n");
        nasty = clone_object("obj/monster");
        call_other(nasty, "set_name", "demon");
        call_other(nasty, "set_alias", "demon");
        call_other(nasty, "set_level",14+random(6));
        call_other(nasty, "set_al", -600);
        call_other(nasty, "set_short", "A summoned demon is here");
        call_other(nasty, "set_wc",15+random(15));
        call_other(nasty, "set_ac",random(8));
        call_other(nasty, "set_aggressive", 1);
        call_other(nasty, "set_chance",random(30));
        call_other(nasty, "set_spell_mess1", "The demon throws fire.");
        call_other(nasty, "set_spell_mess2", "The demon throws fire at you.");
        call_other(nasty, "set_spell_dam",10+random(10));
        move_object(nasty, room);
        call_other(nasty, "attack_object", player);
        return 1;
}
