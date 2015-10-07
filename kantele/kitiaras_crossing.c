inherit "room/room";

reset(arg)
{
   if(arg)
      return;
   short_desc = "You are on a crossing";
   long_desc = "You are in a crossing, a passage goes north/south and \n" +
               "an exit leads east.\n";
   set_light(0);
   dest_dir =
   ({
       "players/kantele/kitiaras_hall", "north",
       "players/kantele/snake_room", "east",
       "players/kantele/kitiaras_innerhall", "south"
    });
}
