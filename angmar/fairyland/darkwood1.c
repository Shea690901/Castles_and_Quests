inherit "room/room";

reset(arg) {
  if (!arg){
    set_light(1);
    short_desc = "Somewhere in Darkwood";
    no_castle_flag = 0;
    long_desc = 
        "You are walking somewhere in Darkwood.  You jump at the sound\n"
        + "of a twig snapping.\n";
    dest_dir = 
        ({
        "players/angmar/fairyland/dw_path2", "west",
        });
    items = 
        ({
        "twig", "A small piece of wood.  If you were trying to be silent, you blew it",
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

