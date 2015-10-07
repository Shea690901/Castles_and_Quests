inherit "room/room";

object beast;

reset(arg)
{
   if(!beast || !living(beast))
   {
      beast = clone_object("obj/monster");
      call_other(beast, "set_name", "displacer beast");
      call_other(beast, "set_wc",20);
      call_other(beast, "set_ac",5);
      call_other(beast, "set_short", "Kitiaras pet displacer beast is here");
      call_other(beast, "set_aggressive", 1);
      call_other(beast, "set_level",10);
      call_other(beast, "set_alias","beast");
      move_object(beast, this_object());
   }
   if(arg)
      return;
   short_desc = "You are in a small hall";
   long_desc = "You are in a small hall. You can smell\n" +
               "some sulphur to the east.\n";
   set_light(0);
   dest_dir =
   ({
       "players/kantele/kitiaras_crossing", "north",
       "players/kantele/kitiaras_lab", "east",
       "players/kantele/kitiaras_sleepingroom", "west",
       "players/kantele/kitiaras_livingroom", "south"
    });
}

init()
{
   ::init();
   add_action("north","north");
   add_action("east","east");
   add_action("west","west");
}

north()
{
   if(beast && present(beast) && this_player()->query_level() < 21)
   {
      write("The Displacer beast shimmers and blurs !\n");
      write("Suddenly it appears in front of you, barring your way !\n");
      return 1;
   }
}

east()
{
   if(beast && present(beast) && this_player()->query_level() < 21)
   {
      write("The Displacer beast shimmers and blurs !\n");
      write("Suddenly it appears in front of you, barring your way !\n");
      return 1;
   }
}

west()
{
   if(beast && present(beast) && this_player()->query_level() < 21)
   {
      write("The Displacer beast shimmers and blurs !\n");
      write("Suddenly it appears in front of you, barring your way !\n");
      return 1;
   }
}
