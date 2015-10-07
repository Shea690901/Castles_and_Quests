inherit "room/room";

reset(arg)
{
   if(arg)
      return;
   set_light(1);
   short_desc = "Entrance hall";
   long_desc = "You are in the entrance hall to the mansion.\n" +
               "A door leads north and a passage leads south.\n";
   dest_dir =
   ({
       "players/kantele/inner_courtyard", "north",
       "players/kantele/inner_hall", "south"
    });
}

id(str) { return ::id(str) || str ==  "door"; }

long(str)
{
   if(str == "door")
   {
      if(call_other("players/kantele/inner_courtyard", "query_door"))
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
    add_action("north"); add_verb("north");
    add_action("open"); add_verb("open");
}

north()
{
   if(call_other("players/kantele/inner_courtyard", "query_door"))
   {
      write("The door is closed.\n");
      return 1;
   }
}

open(str)
{
   if(str == "door")
   {
      if(!call_other("players/kantele/inner_courtyard", "query_door"))
      {
         write("It is already open!\n");
         return 1;
      }
      call_other("players/kantele/inner_courtyard","open_door_inside");
      write("Ok.\n");
      say(call_other(this_player(), "query_name") + " opened the door.\n");
      return 1;
   }
   return 0;
}
