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
       "players/kantele/hell6", "north",
       "players/kantele/hell8", "south",
       "players/kantele/hell8", "east",
       "players/kantele/hell6", "west"
    });
}
