inherit "room/room";

reset(arg) {
  if (!arg){
    set_light(1);
    short_desc = "The path to Misty Mountain";
    no_castle_flag = 0;
    long_desc = 
        "You are on the path to Misty Mountain. Many people have walked\n"
        + "this path. Not many have returned...\n"
        + "The entrance to Darkwood is to the east.\n";
    dest_dir = 
        ({
        "players/angmar/fairyland/path2", "west",
        "players/angmar/fairyland/darkw_entrance", "east",
        "players/angmar/fairyland/crossing", "south",
        });
    items = 
        ({
        "entrance", "The entrance to Darkwood seems evil and forboding",
        "darkwood", "The evil forest reeks of malignant airs...beware",
"forest", "Darkwood, the mystical forest of pure evil",
        "path", "The path leads to Misty Mountain",
"misty mountain", "The mountain seems huge, even though you are far away from it",
        "mountain", "The mountain seems huge, even though you are far away from it",
        });
  }
  if(!present("tramper", this_object())){
    object tramper,we;
    tramper=clone_object("obj/monster");
    call_other(tramper,"set_name","tramper");
    call_other(tramper,"set_level",10);
    call_other(tramper,"set_hp",150);
    call_other(tramper,"set_wc",12);
    call_other(tramper,"set_ac",10);
    tramper->set_male(); /* ### MUTARA: Made tramper male. */
    call_other(tramper,"set_short","A wandering tramper");
    call_other(tramper,"set_alias","tramper");
    call_other(tramper,"set_al",30);
    call_other(tramper,"set_long",
	       "The wandering tramper is whistling happily.\n");
    we=clone_object("obj/weapon");
    call_other(we,"set_name","stick");
    call_other(we,"set_short","A long stick");
    call_other(we,"set_class",7);
    call_other(we,"set_value",15);
    call_other(we,"set_weight",1);
    move_object(we,tramper);
    we=clone_object("obj/armour");
    call_other(we,"set_name","shoes");
    call_other(we,"set_short","Worn shoes");
    call_other(we,"set_long","A pair of very worn shoes.\n");
    call_other(we,"set_value",20);
    call_other(we,"set_weight",1);
    call_other(we,"set_ac",1);
    call_other(we,"set_type","boot");
    move_object(we,tramper);

    move_object(tramper,this_object());
  }
}

query_light() {
    return 1;
}

realm()
{
  return ("fairyland");
}

query_inorout() { return 2; }

