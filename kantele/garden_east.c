inherit "room/room";


reset(arg) {
  if (!arg) {
    short_desc = "A beautiful garden";
    long_desc =
         "A beautiful garden, in the middle of the garden you can see a\n" +
         "small pool, you can see some goldfishes swimming around \n";
    set_light(1);
    dest_dir = ({"players/kantele/brick_road" , "west",
           "players/kantele/pool" , "enter",
        "players/kantele/courtyard" , "south"});
  }
}
