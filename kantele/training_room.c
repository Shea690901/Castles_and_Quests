inherit "room/room";

reset(arg)
{
   if(arg)
      return;
   short_desc = "Training room";
   long_desc = "You are in a training room.\n";
   set_light(1);
   dest_dir =
   ({
       "players/kantele/small_room", "north",
       "players/kantele/knights_room", "west"
    });
}
