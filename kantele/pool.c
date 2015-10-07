inherit "room/room";


reset(arg) {
  if (!arg) {
    short_desc = "standing in the pool";
    long_desc =
        "You are standing in the pool, probably scaring the fishes to\n" +
        "death, besides your feet are getting wet......\n";
    set_light(1);
    dest_dir = ({"players/kantele/garden_east" , "exit"});
  }
}
