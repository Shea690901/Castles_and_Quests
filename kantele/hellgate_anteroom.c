inherit "room/room";

reset(arg)
{
   if(arg)
      return;
   short_desc = "You are in an anteroom";
   long_desc = "You are in a anteroom, you can feel the power of magic\n" +
               "and you are sure there is a great power nearby.\n";
   set_light(0);
   dest_dir =
   ({
       "players/kantele/west_bridge", "south",
       "players/kantele/hellgate", "north"
    });
}
