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
       "players/kantele/hell3", "north",
       "players/kantele/hell5", "south",
       "players/kantele/hell3", "east",
       "players/kantele/hell6", "west"
    });
}
