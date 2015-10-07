inherit "room/room";

reset(arg)
{
   if(arg)
      return;
   short_desc = "The second floor hall";
   long_desc = "You are in the hall on the second floor.\n" +
               "To the north you can exit on to the roof.\n" +
               "To the south you can see the stairway.\n";
   set_light(1);
   dest_dir =
   ({
       "players/kantele/on_roof", "north",
       "players/kantele/lab", "west",
       "players/kantele/small_room", "east",
       "players/kantele/stairway_up", "south"
    });
}
