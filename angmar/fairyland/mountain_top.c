inherit "room/room";

reset(arg) {
  if (!arg){
    set_light(1);
    short_desc = "Eagle's nest";
    no_castle_flag = 0;
    long_desc = 
        "You are on the top of Misty Mountain.  It's very cold up here, although\n"
        + "the view of the fairyland below is terrific.  There is a nest here.\n";
    dest_dir = 
        ({
        "players/angmar/fairyland/mountain", "down",
        });
    items = 
        ({
"nest", "The home of a few eaglets, which are mysteriously missing",
        "fairyland", "The expanse of land beneath you stretches out to the horizon",
        "mountain", "The mountain stretches below you.  You can see a ledge and a door",
        "door", "You cannot tell if the door is open or closed",
        "ledge", "There is an indistinguishable figure on the ledge",
        "figure", "You can't make out the details.  The figure is too far away",
        });
  }
  if(!present("eagle", this_object())){
    object ruby,eagle;
    eagle=clone_object("obj/monster");
    call_other(eagle,"set_name","eagle");
    call_other(eagle,"set_level",9);
    call_other(eagle,"set_hp",100);
    call_other(eagle,"set_wc",10);
    call_other(eagle,"set_short","An eagle");
    call_other(eagle,"set_long",
	       "The eagle glares at you. He doesn't want to be disturbed.\n");
    call_other(eagle,"set_al",50);
    
    ruby=clone_object("obj/treasure");
    call_other(ruby,"set_id","ruby");
    call_other(ruby,"set_short","A small ruby");
    call_other(ruby,"set_value",100);
    move_object(ruby,eagle);
    move_object(eagle,this_object());
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

