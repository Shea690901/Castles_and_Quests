inherit "room/room";

reset(arg)
{
   if(arg)
      return;
   short_desc = "You are in the west hall";
   long_desc = "You are in the west hall in the cellar.\n" +
               "You can go east to the stairway or follow\n" +
               "passages north or west.\n";
   set_light(0);
   dest_dir =
   ({
       "players/kantele/stairway_down", "east",
       "players/kantele/kitiaras_anteroom", "west",
       "players/kantele/dirty_passage", "north"
    });
}
