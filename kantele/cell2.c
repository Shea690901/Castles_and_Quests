inherit "room/room";

id(str)
{
   return ::id(str) || str == "celldoor" || str == "door";
}

long(str)
{
   if(str == "celldoor" || str == "door")
   {
      if(call_other("players/kantele/guard_room","query_gate2"))
         write("The celldoor is closed.\n");
      else
         write("The celldoor is open.\n");
      return 1;
   }
   if(str)
      return ::long(str);
   write("In a small dirty cell.\nA heavy steel celldoor leads west. It is ");
   if(call_other("players/kantele/guard_room","query_gate2"))
      write("closed.\n");
   else
      write("open.\n");
}

reset(arg)
{
   if(arg)
      return;
   short_desc = "A small dirty cell";
   dest_dir = ({ "players/kantele/dungeon_corridor", "west" });
}

init()
{
   ::init();
   add_action("nomove", "west");
}

nomove()
{
   if(call_other("players/kantele/guard_room","query_gate2"))
   {
      write("The celldoor is closed.\n");
      return 1;
   }
}
