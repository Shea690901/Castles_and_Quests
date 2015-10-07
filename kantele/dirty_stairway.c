inherit "room/room";

reset(arg)
{
   if(arg)
      return;
   short_desc = "You are in a stairway";
   long_desc = "You are at the bottom of a stairway.\n" +
               "You can go up or enter a small room to the south.\n";
   set_light(0);
   dest_dir =
   ({
       "players/kantele/dirty_anteroom", "south",
       "players/kantele/dirty_corridor", "up"
    });
}
