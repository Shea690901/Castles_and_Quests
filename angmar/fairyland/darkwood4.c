inherit "room/room";

reset(arg) {

  object witch;
  if (!arg){
    set_light(0);
    short_desc = "Walking in Darkwood";
    no_castle_flag = 0;
    long_desc = 
        "You are walking somewhere the Darkwood. It's almost pitch black.\n"
        + "Are there any nasty monsters lurking around here?\n";
    dest_dir = 
        ({
        "players/angmar/fairyland/dw_path4", "north",
        });
    items = 
        ({
        });
  }

  if(!present("witch", this_object())){
    object broom;
    witch=clone_object("obj/monster");
    call_other(witch,"set_name","witch");
    call_other(witch,"set_level",19);
    call_other(witch,"set_hp",300);
    call_other(witch,"set_wc",25);
    call_other(witch,"set_short","A nasty witch");
    call_other(witch,"set_long",
	       "The witches are not to be tampered with...\n");
    call_other(witch,"set_al",-200);
    
    broom=clone_object("obj/weapon");
    call_other(broom,"set_name","broom");
    call_other(broom,"set_short","A broom");
    call_other(broom,"set_long","This broom once belonged to a witch.\n");
    call_other(broom,"set_class",12);
    call_other(broom,"set_value",400);
    call_other(broom,"set_weight",1);
    move_object(broom,witch);
    
    move_object(witch,this_object());
  }
}

query_light() {
    return 0;
}

realm(str)
{
  return (str == "fairyland" || str == "darkwood");
}

query_inorout() { return 2; }

