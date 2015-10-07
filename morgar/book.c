int i, level, nastiness;
string name;
object nasty,player,room;

setvars() {
    player = this_player();
    room = environment(player);
    name = call_other(player,"query_name",0);
    level = call_other(player,"query_level",0);
}

id(str) { return ((str == "book") || (str == "spellbook")); }

reset() {nastiness=15;}

long() {
    write("Morgar's spell book is a huge tome lying open on a pedistal.\n");
    write("He doesn't mind if people memorize spells from it, but taking\n");
    write("it is strictly forbidden.  It is, of course, not safe to\n");
    write("read, but you may use it at your own risk.\n");
}

short() { return "Morgar's spellbook"; }

query_value() { return 10000; }

init() {
    add_action("use"); add_verb("use");
    add_action("use"); add_verb("read");
    add_action("memorize"); add_verb("learn");
    add_action("memorize"); add_verb("memorize");
    add_action("stats"); add_verb("stat");
    add_action("set_nasty"); add_verb("setnasty");
}

use(arg) {
    setvars();
    if (!arg || !id(arg)) {
        return 0;
    } else {
        say(name + " reads the spell book\n");
        write("You read the book.\n");
        write("In the book you find these spells:\n");
        write("    Heal\n");
        nasty(8);
        return 1;
    }
}

get() { 
    setvars();
    if (level < 20) { return 0; }
    else { return 1; }
}

stats(arg) {
    if (call_other(this_player(),"query_level",0) < 20) { return 0; }
    if (call_other(this_player(),"query_level",0)<20) {return 0; }
    if (arg != "book") { return 0; }
    write("Nastiness is "+nastiness+"\n");
    return 1;
}

set_nasty(arg) {
    if (call_other(this_player(),"query_level",0) < 20) { return 0; }
    if (!arg || sscanf(arg,"%d",nastiness) != 1) {
        write("Need an integer\n");
    }
    return 1;
}


query_weight() { return 5; }

nasty(prob) {
    if (0 == random(prob)) {
        nastiness=nastiness+1;
        say(name + " accidentally summons a demon.\n");
        tell_room(room, "A demon appears in a blast of fire!\n");
        nasty = clone_object("obj/monster");
        call_other(nasty, "set_name", "demon");
        call_other(nasty, "set_alias", "demon");
        call_other(nasty, "set_level",14+random(6));
        call_other(nasty, "set_al", -600);
        call_other(nasty, "set_short", "A summoned demon is here");
        call_other(nasty, "set_wc",nastiness+random(nastiness));
        call_other(nasty, "set_ac",random(nastiness/2));
        call_other(nasty, "set_aggressive", 1);
        call_other(nasty, "set_chance",random(30));
        call_other(nasty, "set_spell_mess1", "The demon throws fire.");
        call_other(nasty, "set_spell_mess2", "The demon throws fire at you.");
        call_other(nasty, "set_spell_dam",10+random(nastiness));
        move_object(nasty, room);
        call_other(nasty, "attack_object", player);
        return 1;
    }
    return 0;
}

memorize(arg) {
    if (present("demon",environment(this_object()))) {
        write("You are busy.\n");
        return 1;
    }
    setvars();
    i = 20;
    if ((nasty(2)+nasty(3))>0) {
        return 1;
    }
    if (arg=="heal") i=8;
    if (level < i) {
        write("You are too low level to learn that spell.\n");
        return 1;
    } else {
        object spell;
        if (call_other(this_player(),"query_ghost")) {
            write("Ghosts can't learn spells.\n");
            return 1;
        }
        spell = clone_object("players/morgar/spells/"+arg);
        move_object(spell, player);
        write("You learn "+arg+".\n");
        return 1;
    }
}
