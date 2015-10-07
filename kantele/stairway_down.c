inherit "room/room";

object haunt;

reset(arg)
{
   if(!haunt || !living(haunt))
   {
      haunt = clone_object("obj/monster");
      call_other(haunt, "set_name", "haunt");
      call_other(haunt, "set_short", "A ghostly haunt");
      call_other(haunt, "set_aggressive", 1);
      call_other(haunt, "set_level",12);
      call_other(haunt, "set_wc", 15);
      call_other(haunt, "set_ac", 2);
      call_other(haunt, "set_chance",20);
      call_other(haunt, "set_spell_mess1",
                "The haunt utters a wailing scream.");
      call_other(haunt, "set_spell_mess2",
                "The scream hurts you bad.");
      call_other(haunt, "set_spell_dam",40);
      move_object(haunt, this_object());
   }
   if(arg)
      return;
   short_desc = "Bottom of stairway";
   long_desc = "You are at the bottom of the stairway.\n" +
               "The stairway goes up and you can go further\n" +
               "into the cellar to the west.\n";
   set_light(0);
   dest_dir =
   ({
       "players/kantele/stairway", "up",
       "players/kantele/cellar_west", "west",
       "players/kantele/cellar_east", "east"
    });
}

init()
{
   ::init();
   add_action("west","west");
   add_action("east","east");
}

west()
{
   if(call_other(this_player(), "query_level", 0) < 20)
   {
      if(haunt && present(haunt))
      {
         write("The haunt is in the way  !\n");
         return 1;
      }
   }
}

east()
{
   if(call_other(this_player(), "query_level", 0) < 20)
   {
      if(haunt && present(haunt))
      {
         write("The haunt is in the way!\n");
         return 1;
      }
   }
}
