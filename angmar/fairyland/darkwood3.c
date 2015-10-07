inherit "room/room";

reset(arg) {
  if (!arg){
    set_light(1);
    short_desc = "Somewhere deep inside Darkwood";
    no_castle_flag = 0;
    long_desc = 
        "You are walking somewhere deep inside the Darkwood. Are you\n"
        + "lost? Will you ever see your mummy again?\n";
    dest_dir = 
        ({
        "players/angmar/fairyland/darkwood5", "west",
        "players/angmar/fairyland/darkwood2", "east",
        "players/angmar/fairyland/dw_path4", "south",
        });
    items = 
        ({
        });
  }
}

query_light() {
    return 1;
}

realm()
{
  return ("darkwood");
}

query_inorout() { return 2; }

