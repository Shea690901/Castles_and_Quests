inherit "room/room";


reset(arg)
{
   if(arg)
      return;
   short_desc = "A beautiful garden";
   long_desc = "A beautiful garden filled with strange flowers of\n" +
               "many exotic species. Some strange trees line the fence.\n";
   set_light(1);
   dest_dir =
   ({
       "players/kantele/brick_road", "east",
       "players/kantele/courtyard", "south"
    });
}
