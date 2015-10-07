inherit "room/room";

reset(arg)
{
   if(arg)
      return;
   set_light(1);
   short_desc = "A small dark hall";
   long_desc = "You are in a small dark hall. A passage leads south and a\n" +
               "door leads east. You can see some light to the south.\n";
   dest_dir =
   ({
       "players/kantele/kitiaras_crossing", "south",
       "players/kantele/kitiaras_anteroom", "east"
    });
   items = ({ "door", "It's a sturdy steel door"});
}

long(str)
{
   if(str == "door")
   {
      if(call_other("players/kantele/kitiaras_anteroom", "query_door"))
         write("The door is closed.\n");
      else
         write("The door is open.\n");
      return;
   }
   ::long(str);
}

init()
{
   ::init();
   add_action("east", "east");
   add_action("open", "open");
}

east()
{
   if(call_other("players/kantele/kitiaras_anteroom", "query_door"))
   {
      write("The door is closed.\n");
      return 1;
   }
}

open(str)
{
   if(str == "door")
   {
      if(!call_other("players/kantele/kitiaras_anteroom", "query_door"))
      {
	 write("It is already open!\n");
	 return 1;
      }
      call_other("players/kantele/kitiaras_anteroom","open_door_inside");
      write("Ok.\n");
      say(call_other(this_player(), "query_name") + " Opened the door.\n");
      return 1;
   }
   return 0;
}
