inherit "room/room";

reset(arg)
{
   short_desc = "A dungeon corridor";
   long_desc = "A dungeon corridor. You can enter the watch room to\n" +
               "the north and in the other directions there are celldoors\n";
   dest_dir =
   ({
       "players/kantele/guard_room", "north",
       "players/kantele/cell1", "south",
       "players/kantele/cell2", "east",
       "players/kantele/cell3", "west"
    });
   items =
   ({
        "celldoor", "The celldoors is made of steel and looks very tough",
        "door", "The celldoors is made of steel and looks very tough",
        "doors", "The celldoors is made of steel and looks very tough"
    });
}

init()
{
   ::init();
   add_action("nomove2", "south");
   add_action("nomove3", "east");
   add_action("nomove4", "west");
   add_action("open_door", "open");
   add_action("open_door", "unlock");
}

open_door(str)
{
   if(str == "door" || str == "celldoor")
   {
      write("There is no way for you to do that.\n");
      return 1;
   }
}

nomove2()
{
   if(call_other("players/kantele/guard_room","query_gate1"))
   {
      write("The celldoor is closed.\n");
      return 1;
   }
}

nomove3()
{
   if(call_other("players/kantele/guard_room","query_gate2"))
   {
      write("The celldoor is closed.\n");
      return 1;
   }
}

nomove4()
{
   if(call_other("players/kantele/guard_room","query_gate3"))
   {
      write("The celldoor is closed.\n");
      return 1;
   }
}
