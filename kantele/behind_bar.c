inherit "room/room";

reset(arg)
{
   if(arg)
      return;
   short_desc = "Behind the bar";
   long_desc = "You are behind the bar. You can enter the barroom\n" +
               "proper to the west. There is a very large barrel of\n" +
               "beer here. It should be possible to drink from the tap...\n";
   set_light(1);
   dest_dir = ({ "players/kantele/bar", "east" });
}

init()
{
   ::init();
   add_action("drink_beer", "drink");
}

drink_beer(arg)
{
   if(arg != "from tap" && arg != "from the tap")
      return 0;
   if(call_other(this_player(), "drink_alcohol", 2))
      write("It tasted a bit stale\n");
   return 1;
}
