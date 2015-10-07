inherit "room/room";


reset(arg) {
  if (!arg) {
    short_desc = "Dining room";
    long_desc =
         "A beautiful dining room, this room is decorated with dark cedar\n" +
         "panels, you can smell coking to the south.\n";
    set_light(1);
    dest_dir = ({"players/kantele/inner_hall","east",
         "players/kantele/kitchen","south"});
  }
}
