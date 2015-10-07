inherit "room/room";

reset(arg)
{
   if(arg)
      return;
   short_desc = "A small lab";
   long_desc = "You are in a small well lit laboratory.\nLots of strange things " +
               "can be seen in this room.\nYou feel lost in the affairs of the " +
               "immortals.\n";
   set_light(1);
   dest_dir =
   ({
       "players/kantele/kitiaras_innerhall", "west",
       "players/kantele/kitiaras_magesroom", "north"
    });
}
