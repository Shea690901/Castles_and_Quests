inherit "room/room";

reset(arg) {
  if (!arg){
    set_light(1);
    short_desc = "On a path in Darkwood";
    no_castle_flag = 0;
    long_desc = 
        "You are on a twisty path in the legendary Darkwood.  Many adventurers\n"
        + "have been killed here.\n";
    dest_dir = 
        ({
        "players/angmar/fairyland/dw_path2", "north",
        "players/angmar/fairyland/darkw_entrance", "west",
        });
    items = 
        ({
        "path", "The path twists and turns as it weaves its way into Darkwood",
        "darkwood", "The mystical forest makes you shudder as it emanates evil",
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

