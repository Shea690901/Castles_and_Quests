inherit "room/room";

reset(arg) {
  if (!arg){
    set_light(0);
    short_desc = "On a path in Darkwood";
    no_castle_flag = 0;
    long_desc = 
        "You are on a twisty path in the legendary Darkwood. You can see\n"
        + "gleaming eyes stare at you from the shadows.\n";
    dest_dir = 
        ({
        "players/angmar/fairyland/darkwood2", "north",
        "players/angmar/fairyland/dw_path2", "south",
        "players/angmar/fairyland/dw_path4", "west",
        });
    items = 
        ({
        "eyes", "They appear red, but then disappear.  They reappear momentarily",
        });
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

