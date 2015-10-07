inherit "room/room";

reset(arg) {
  object troll;


  if (!arg){
    set_light(1);
    short_desc = "Behind the Misty Mountain";
    no_castle_flag = 0;
    long_desc = 
        "The path ends here behind Misty Mountain.  There seems to be no\n"
        + "way around it.\n";
    dest_dir = 
        ({
        "players/angmar/fairyland/dw_path5", "east",
        });
    items = 
        ({
        "path", "It stops all of a sudden.  You cannot follow it anymore",
        "mountain", "It dwarfs you, looming in the sky",
        "misty mountain", "It dwarfs you, looming in the sky",
        });
  }

  if(!present("troll", this_object())){
    object cloak;
    troll=clone_object("obj/monster");
    call_other(troll,"set_name","troll");
    call_other(troll,"set_level",19);
    call_other(troll,"set_hp",400);
    call_other(troll,"set_wc",25);
    call_other(troll,"set_short","The forestking");
    call_other(troll,"set_alias","king");
    call_other(troll,"set_race","forestking");
    call_other(troll,"set_long",
	       "It's an old troll which must be at least 1000 years old.\n"+
	       "I don't think he likes you...\n");
    call_other(troll,"set_al",-300);

    cloak=clone_object("obj/armour");
    call_other(cloak,"set_name","cloak");
    call_other(cloak,"set_short","A cloak made of twigs and leaves");
    call_other(cloak,"set_long",
	       "It once belonged to the troll-king of Darkwood.\n");
    call_other(cloak,"set_value",200);
    call_other(cloak,"set_weight",1);
    call_other(cloak,"set_ac",1);
    call_other(cloak,"set_type","cloak");
    move_object(cloak,troll);
    
    move_object(troll,this_object());
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

