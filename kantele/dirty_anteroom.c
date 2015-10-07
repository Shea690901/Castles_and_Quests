inherit "room/room";

reset(arg)
{
   if(arg)
      return;
   short_desc = "you are in a small room";
   long_desc = "You are in a small room.\n" +
               "There is a stairway to the north and some sort\n" +
               "of temple to the south.\n";
   set_light(0);
   dest_dir =
   ({
       "players/kantele/dirty_stairway", "north",
       "players/kantele/dirty_temple", "south"
    });
}
