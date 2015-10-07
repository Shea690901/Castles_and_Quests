inherit "room/room";

reset(arg) {
  if (!arg){
    set_light(1);
    short_desc = "Somewhere deep inside Darkwood";
    no_castle_flag = 0;
    long_desc = 
        "You are walking somewhere deep inside Darkwood.  You feel cold\n"
        + "and frightened.  Maybe you should turn back?\n";
    dest_dir = 
        ({
        "players/angmar/fairyland/darkwood3", "west",
        "players/angmar/fairyland/dw_path3", "south",
        });
    items = 
        ({
        "darkwood", "You see something creep behind you out of the corner of your eye",
        "something", "It's gone now.  Too fast for your untrained vision",
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

