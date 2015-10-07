inherit "room/room";


reset(arg) {
  if (!arg) {
    short_desc = "In a dark passage";
    long_desc =
        "In a narrow twisting passage going south and north.\n";
    set_light(0);
    dest_dir = ({"players/kantele/cellar_passage2","south",
         "players/mats/cave.c","north"});
  }
}
