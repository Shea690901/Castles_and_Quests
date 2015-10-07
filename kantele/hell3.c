inherit "room/room";

reset(arg)
{
   if(arg)
      return;
   short_desc = "You are in hell";
   long_desc = "You are in hell, the smell of sulphur penetrates everything.\n";
   set_light(1);
   dest_dir =
   ({
       "players/kantele/hell2", "north",
       "players/kantele/hell4", "south",
       "players/kantele/hell2", "east",
       "players/kantele/hell2", "west"
    });
}
