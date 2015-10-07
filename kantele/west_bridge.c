inherit "room/room";

reset(arg)
{
   if(arg)
      return;
   short_desc = "You are in a hall";
   long_desc = "You are in a hall. Exits leads off in every direction.\n" +
               "To the east you can see a rotten wooden bridge.\n";
   set_light(0);
   dest_dir =
   ({
       "players/kantele/sphinx_room", "south",
       "players/kantele/hellgate_anteroom", "north",
       "players/kantele/guard_room", "west",
       "players/kantele/on_bridge", "east"
    });
}
