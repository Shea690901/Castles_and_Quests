inherit "room/room";

reset(arg) {
  object notebook,statue;
  if (!arg){
    set_light(1);
    short_desc = "The library";
    no_castle_flag = 0;
    long_desc = 
        "This is Angmar's library.  Along the walls are shelves full of books,\n"
        + "papers, and magic scrolls.  The entire room seems to emanate a dark,\n"
        + "chilling feeling, as if Angmar were still here in spirit.\n" 
	  + "There is a magic wardrobe in the corner.\n";
    dest_dir = 
        ({
        "players/angmar/castle/magroom", "east",
        });
    items = 
        ({
        "shelves", "They hold what look like the collected works of Angmar's magic",
        "books", "The book you examine deals with the pitfalls of magical human mutation",
        "papers", "The paper seems to be thinner than normal parchment.  Surely, magical",
        });
  }
  notebook=present("notebook");
  if(notebook) destruct(notebook);
  notebook=clone_object("players/angmar/o/notebook");
  move_object(notebook,this_object());

  if(!present("stone statue")&&!present("elfwarrior")) {
    statue=clone_object("players/angmar/o/statue");
    move_object(statue,this_object());
  }
}

query_light() {
    return 1;
}

query_inorout() { return 1; }


init() {
  add_action("open","open");
  add_action("close","close");
  add_action("enter","enter");
  add_action("Check_out","exa",1);
  add_action("Check_out", "look");
  ::init();
}

Check_out(str) {
  if (!str)
    return 0;
  if (query_verb() == "look"){
    if (str == "at door" || str == "at wardrobe" ||
	str == "at magic wardrobe"){
      if(!call_other("players/angmar/castle/wardrobe1","query_door",0)) {
        write("It can take you to fairyland.\n");
        write("The door is open.\n");
      }
      else {
        write("It can take you to fairyland.\n");
        write("The door is closed.\n");
      }
      return 1;
    }
    return 0;
  }
if (query_verb() == "examine" || query_verb() == "exa"){
    if (str == "door" || str == "wardrobe" || 
	str == "magic wardrobe"){
      if(!call_other("players/angmar/castle/wardrobe1","query_door",0)) {
        write("It can take you to fairyland.\n");
        write("The door is open.\n");
      }
      else {
        write("It can take you to fairyland.\n");
        write("The door is closed.\n");
      }
      return 1;
    }
    return 0;
  }
  return 0;
}

open(str) {
  if(str!="door"&&str!="wardrobe") return 0;
  call_other("players/angmar/castle/wardrobe1","open_door","door");
  return 1;
}
close(str) {
  if(str!="door"&&str!="wardrobe") return 0;
  call_other("players/angmar/castle/wardrobe1","close_door","door");
  return 1;
}
enter(str) {
  if(str!="door"&&str!="wardrobe") return 0;
  if(call_other("players/angmar/castle/wardrobe1","query_door",0)) {
    write("The door is closed.\n");
    return 1;
  }
  call_other(this_player(),"move_player",
        "into the wardrobe#players/angmar/castle/wardrobe1");
  return 1;
}
