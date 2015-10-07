inherit "room/room";


reset(arg) {
  if (!arg) {
    short_desc = "Lars's residence";
    long_desc =
	 "This is the residence of Lars.\n";
    set_light(1);
    dest_dir = ({"room/church", "church"});
  }
}
