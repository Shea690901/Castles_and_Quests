inherit "room/room";

int iron_maiden;

reset(arg)
{
   iron_maiden = 0;
   if(arg)
      return;
   short_desc = "In a torture chamber";
   long_desc = "In a torture chamber.\n" +
               "The only exit is east into the guardroom.\n" +
               "You can see a well used stretch bench and an ironmaiden.\n";
   set_light(0);
   dest_dir = ({ "players/kantele/guard_room", "east" });
   items =
   ({
        "ironmaiden", "A horrifying ironmaiden",
        "maiden", "A horrifying ironmaiden",
        "stretch bench", "A terrifying stretch bench",
        "bench", "A terrifying stretch bench"
    });
}

init()
{
   ::init();
   add_action("enter", "enter");
   add_action("open_maiden", "open");
}

open_maiden(str)
{
   if(str == "ironmaiden" || str == "maiden")
   {
      if(!iron_maiden)
      {
         write("You open the ironmaiden.\n");
         say(call_other(this_player(), "query_name") + " opens the iron maiden.\n");
         iron_maiden = 1;
      }
      else
         write("The ironmaiden is already open.\n");
      return 1;
   }
}

enter(str)
{
   if(str == "ironmaiden" || str == "maiden")
   {
      write("You can't do a stupid thing like that!!!\n");
      say(call_other(this_player(), "query_name") +
          " thinks he is playing ABERmud.\n");
      return 1;
   }
}
