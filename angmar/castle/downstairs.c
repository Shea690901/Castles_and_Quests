inherit "room/room";

reset(arg) {

  object bat;

  if (!arg){
    set_light(1);
    short_desc = "Bottom of staircase";
    no_castle_flag = 0;
    long_desc = 
        "You are at the bottom of the staircase.  Nobody has been here for\n"
        + "a long time.  Still, the place is lit up by torches.  The atmosphere\n"
        + "does not feel very good.  You can easily imagine evil creatures\n"
        + "lurking in every corner.\n";
    dest_dir = 
        ({
        "players/angmar/castle/midstairs", "up",
        "players/angmar/castle/corridor", "east",
        "players/angmar/castle/torture", "south",
        });
    items = 
        ({
        "torches", "The torches are fastened to the wall.  They seem to be magical",
        "creatures", "See?  Your imagination is flourishing",
        "corners", "You search them, but find nothing",
        "staircase", "The staircase winds its way back up into the castle",
        });
  }

  if (!present("bat", this_object())){
    bat=clone_object("obj/monster");
    call_other(bat, "set_name","bat");
    call_other(bat,"set_level",1);
    call_other(bat,"set_hp",30);
    call_other(bat,"set_al",-10);
    call_other(bat,"set_short","A bat");
bat->set_long("A small bat, with sharp fangs.  It seems to be all alone here.\n");
    call_other(bat,"set_wc",2);
    call_other(bat,"set_ac",0);
    call_other(bat,"set_aggressive",1);
    call_other(bat,"set_dead_ob",this_object());
    
    move_object(bat,this_object());
  }
}

monster_died(dum){
  write("The bat gives off a high pitched shriek as you\n"+
	"give it a killing blow.\n");
  say("The bat gives off a shriek as "+
      call_other(this_player(),"query_name",0)+" kills it.\n");
  return(0);
}

query_light() {
    return 1;
}

query_inorout() { return 1; }

