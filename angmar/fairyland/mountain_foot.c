inherit "room/room";

reset(arg) {
  if (!arg){
    set_light(1);
    short_desc = "The foot of Misty Mountain";
    no_castle_flag = 0;
    long_desc = 
        "Misty Mountain towers high before you.  You feel very small.\n";
    dest_dir = 
        ({
        "players/angmar/fairyland/path2", "south",
        "players/angmar/fairyland/mountain", "up",
        });
    items = 
        ({
"misty mountain", "The mountain is huge, but you think you can climb up",
        "mountain", "The mountain is huge, but you think you can climb up",
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

