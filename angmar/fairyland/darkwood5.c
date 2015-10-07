inherit "room/room";

reset(arg) {

  object oak;
  if (!arg){
    set_light(0);
    short_desc = "You are deep inside Darkwood";
    no_castle_flag = 0;
    long_desc = 
        "You are deep inside Darkwood.  You wish you had never come here.\n";
    dest_dir = 
        ({
        "players/angmar/fairyland/dw_path5", "south",
        "players/angmar/fairyland/darkwood3", "east",
        });
    items = 
        ({
        });
  }

  if(!present("oak", this_object())){
    oak=clone_object("obj/monster");
    call_other(oak,"set_name","oak");
    call_other(oak,"set_level",19);
    call_other(oak,"set_hp",400);
    call_other(oak,"set_wc",22);
    call_other(oak,"set_short","A giant oak");
    call_other(oak,"set_long",
	       "The oak is following your movements with its eyes.\n"+
	       "Maybe you should leave while you can.\n");
    call_other(oak,"set_al",-200);
    oak->add_money(500);
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

