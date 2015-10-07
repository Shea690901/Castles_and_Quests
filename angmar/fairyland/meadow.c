inherit "room/room";

reset(arg) {
  if (!arg){
    set_light(1);
    short_desc = "The meadow";
    no_castle_flag = 0;
    long_desc = 
        "You are standing in the middle of a meadow.  Many different\n"
        + "kinds of flowers are growing here.\n";
    dest_dir = 
        ({
        "players/angmar/fairyland/road3", "east",
        "players/angmar/fairyland/ditch", "west",
        });
    items = 
        ({
        "meadow", "The grass blows in the wind",
        "wind", "You lick a finger, and stick it into the wind: North",
        "flowers", "They smell fresh, as if they had grown here forever",
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

