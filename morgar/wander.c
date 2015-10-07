object knight,chainmail,blade;

reset(arg) {
    if (arg) return;
    knight = clone_object("obj/monster");
    call_other(knight, "set_name", "knight");
    call_other(knight, "set_short", "A black knight is here");
    call_other(knight, "set_level",17);
    call_other(knight, "set_whimpy");
    call_other(knight, "set_al",-200);
    call_other(knight, "set_hp",250);
    call_other(knight, "set_wc",25);
    call_other(knight, "set_ac", 4);
    call_other(knight, "set_aggressive", 1);
    call_other(knight, "set_move_at_reset");
    move_object(knight, this_object());
    chainmail = clone_object("obj/armour");
    call_other(chainmail, "set_ac",4);
    call_other(chainmail, "set_alias","armour");
    call_other(chainmail, "set_type","armour");
    call_other(chainmail, "set_alias","mail");
    call_other(chainmail, "set_name", "chainmail");
    call_other(chainmail, "set_value", 500);
    call_other(chainmail, "set_short", "A death black chainmail");
    call_other(chainmail, "set_weight",5);
    move_object(chainmail, knight);
    blade = clone_object("obj/weapon");
    call_other(blade, "set_name", "A black demon blade");
    call_other(blade, "set_short", "A black demon blade");
    call_other(blade, "set_class",20);
    call_other(blade, "set_alt_name", "blade");
    call_other(blade, "set_value",5000);
    call_other(blade, "wield","blade");
    call_other(blade,"set_alias","sword");
    move_object(blade, knight);
    }
}
