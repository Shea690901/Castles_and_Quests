inherit "room/room";

reset(arg)
{
   if(arg)
      return;
   short_desc = "A small courtyard";
   long_desc = "A small courtyard. A road leads north,\n" +
               "to the east you can see a small shack,\n" +
               "to the west a small open wagon stall can be seen while\n" +
               "to the south the entrance to the mansion can be seen.\n";
   set_light(1);
   dest_dir =
   ({
       "players/kantele/brick_road", "north",
       "players/kantele/shack", "east",
       "players/kantele/wagon_stall", "west",
       "players/kantele/inner_courtyard", "south"
    });
}
