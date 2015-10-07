inherit "room/room";

reset(arg) {

  object oak;
  if (!arg){
    set_light(0);
    short_desc = "On a path in Darkwood";
    no_castle_flag = 0;
    long_desc = 
        "You are walking on a twisty path in the legendary Darkwood.  You feel\n"
        + "very uncomfortable.\n";
    dest_dir = 
        ({
        "players/angmar/fairyland/dw_path3", "north",
        "players/angmar/fairyland/dw_path1", "south",
        "players/angmar/fairyland/darkwood1", "east",
        });
    items = 
        ({
        "path", "The path twists and turns through Darkwood",
        "darkwood", "The forest gets more evil now, and light is frequently blocked by the trees",
        });
  }

  if(!present("oak", this_object())){
    object branch;
    oak=clone_object("obj/monster");
    call_other(oak,"set_name","oak");
    call_other(oak,"set_level",18);
    call_other(oak,"set_hp",200);
    call_other(oak,"set_wc",20);
    call_other(oak,"set_short","A big oak");
    call_other(oak,"set_long",
	       "The oak is watching you with small gleaming eyes\n"+
	       "and waves it's branches menacingly.\n");
    call_other(oak,"set_al",-200);
    
    branch=clone_object("obj/weapon");
    call_other(branch,"set_name","branch");
    call_other(branch,"set_short","A branch");
    call_other(branch,"set_long","Seems to be a branch from an oak.\n");
    call_other(branch,"set_class",13);
    call_other(branch,"set_value",500);
    call_other(branch,"set_weight",2);
    move_object(branch,oak);
    
    move_object(oak,this_object());
  }
}

query_light() {
    return 0;
}

realm()
{
  return ("fairyland");
}

query_inorout() { return 2; }

