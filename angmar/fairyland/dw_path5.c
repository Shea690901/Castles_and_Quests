inherit "room/room";

reset(arg) {
  if (!arg){
    set_light(1);
    short_desc = "On a path in Darkwood";
    no_castle_flag = 0;
    long_desc = 
        "You are on a twisty path in the legendary Darkwood. The\n"
        + "forest ends to the west.\n";
    dest_dir = 
        ({
        "players/angmar/fairyland/behind_mountain", "west",
        "players/angmar/fairyland/dw_path4", "east",
        "players/angmar/fairyland/darkwood5", "north",
        });
    items = 
        ({
        "west", "The forest ends, finally",
        "forest", "The forest has thinned out slightly.  Could you be out of it?  Perhaps..",
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

