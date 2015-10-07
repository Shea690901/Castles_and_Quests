inherit "room/room";



reset(arg) {
  if (!arg) {
    items = ({ "painting", "The large painting covers the wall from ceiling to the floor"});
    short_desc = "You are at a landing in the stairway";
    long_desc =
           "You are on a landing in the stairway, the stairway continues up\n" +
           "and down, you can go north into the hall. on the east wall you\n" +
           "can se a large painting of Kantele and her sister on a dragon-\n" +
           "hunt they had on one of the outher planes.\n";
    set_light(1);
    dest_dir = ({"players/kantele/stairway","down",
           "players/kantele/stairway_top","up",
          "players/kantele/upper_hall",});
  }
}
