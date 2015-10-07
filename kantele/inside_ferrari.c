inherit "room/room";


reset(arg) {
  if (!arg) {
    short_desc = "Inside the ferrari";
    long_desc =
	 "This is the residence of Lars.\n";
    set_light(1);
    dest_dir = ({"players/kantele/wagon_stall.c","exit"});
  }
}
