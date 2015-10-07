inherit "room/room";

reset(arg)
{
   if(arg)
      return;
   short_desc = "You are in a dirty passage";
   long_desc = "You are in a dirty passage.\n" +
               "A stairway leads down and the corridor continues\n" +
               "to the north.\n";
   set_light(0);
   dest_dir =
   ({
       "players/kantele/dirty_passage", "south",
       "players/kantele/dirty_stairway", "down",
       "players/kantele/dirty_room", "north"
    });
}
