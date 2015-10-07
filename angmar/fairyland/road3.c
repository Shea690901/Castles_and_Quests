inherit "room/room";

reset(arg) {
  if (!arg){
    set_light(1);
    short_desc = "A small road";
    no_castle_flag = 0;
    long_desc = 
        "You are standing on a small road which continues to the north.\n"
        + "There is a meadow to the west.\n";
    dest_dir = 
        ({
        "players/angmar/fairyland/road2", "south",
        "players/angmar/fairyland/crossing", "north",
        "players/angmar/fairyland/meadow", "west",
        });
    items = 
        ({
        "meadow", "The lush green grass and fresh air entice you to wander over there",
        "road", "The road seems to be narrowing down",
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

