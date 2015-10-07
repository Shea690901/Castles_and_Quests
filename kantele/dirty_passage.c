inherit "room/room";


reset(arg) {
  if (!arg) {
    short_desc = "You are in a narrow corridor";
    long_desc =
         "You are in a narrow corridor, it is damp and dark.\n";
    set_light(0);
    dest_dir = ({"players/kantele/cellar_west","south",
         "players/kantele/dirty_corridor","north"});
  }
}
