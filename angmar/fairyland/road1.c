inherit "room/room";

reset(arg) {
  if (!arg){
    set_light(1);
    short_desc = "On a road in Fairyland";
    no_castle_flag = 0;
    long_desc = 
        "You are standing on a road in Fairyland.  The road\n"
        + "continues to the north.  Above you floats a wardrobe,\n"
        + "hovering in the same position.\n";
    dest_dir = 
        ({
        "players/angmar/fairyland/road2", "north",
        "players/angmar/fairyland/edge1", "south",
        });
    items = 
        ({
        "road", "The road has a magical quality to it.  This realm is different, somehow",
        "fairyland", "You can't possibly see all of it from here",
        });
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

init() {
  add_action("open","open");
  add_action("close","close");
  add_action("enter","enter");
  add_action("Check_out", "look");
  add_action("Check_out", "examine");
   add_action("Check_out", "exa");
  ::init();
}


Check_out(str) {
  if (query_verb() == "look"){
    if (str=="at door" || str=="at wardrobe" ||
	str == "at magical wardrobe") {
      if(!call_other("players/angmar/castle/wardrobe2","query_door",0))
        write("It is open.\n");
      else
        write("It is closed.\n");
      return 1;
    }
    return 0;
  }
   if (query_verb() == "examine" || query_verb() == "exa"){
    if(str=="door" || str=="wardrobe") {
      if(!call_other("players/angmar/castle/wardrobe2","query_door",0))
        write("It is open.\n");
      else
        write("It is closed.\n");
      return 1;
    }
    return 0;
  }
  return 0;
}

open(str) {
  if(str!="door"&&str!="wardrobe") return 0;
  call_other("players/angmar/castle/wardrobe2","open_door","door");
  return 1;
}
close(str) {
  if(str!="door"&&str!="wardrobe") return 0;
  call_other("players/angmar/castle/wardrobe2","close_door","door");
  return 1;
}
enter(str) {
  if(str!="door"&&str!="wardrobe") return 0;
  if(call_other("players/angmar/castle/wardrobe2","query_door",0)) {
    write("The door is closed.\n");
    return 1;
  }
  call_other(this_player(),"move_player",
        "into the wardrobe#players/angmar/castle/wardrobe2");
  return 1;
}

