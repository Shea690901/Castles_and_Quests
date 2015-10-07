inherit "room/room";

reset(arg) {
  if (!arg){
    set_light(1);
    short_desc = "By Great Lake";
    no_castle_flag = 0;
    long_desc = 
        "You are standing by Great Lake.  You can hear the gulls crying.\n";
    dest_dir = 
        ({
        "players/angmar/fairyland/crossing", "west",
        "players/angmar/fairyland/reeds", "east",
        });
    items = 
        ({
        "lake", "The lake stretches out for a few miles",
        "gulls", "The gulls must have come from the sea nearby",
        "sea", "You cannot see it.  It must be behind the mountain",
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

