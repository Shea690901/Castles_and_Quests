inherit "room/room";

object rotweiler;

reset(arg)
{
   if(!rotweiler || !living(rotweiler))
   {
      object collar;
      int i;
      for(i = 2; i; --i)
      {
         rotweiler = clone_object("obj/monster");
	 call_other(rotweiler, "set_name", "rotweiler");
         call_other(rotweiler, "set_alias", "dog");
         call_other(rotweiler, "set_level",2);
	 call_other(rotweiler, "set_short", "A huge rotweiler");
	 call_other(rotweiler, "set_long", "A mean hungry rotweiler is " +
	            "snaring at you....\n");
         call_other(rotweiler, "set_wc",8);
         call_other(rotweiler, "set_aggressive", 1);
	 call_other(rotweiler, "set_move_at_reset");
	 call_other(rotweiler, "set_move_at_reset");
	 move_object(rotweiler, this_object());
         collar = clone_object("obj/treasure");
         call_other(collar, "set_id", "collar");
         call_other(collar, "set_alias", "dog collar");
         call_other(collar, "set_short", "A heavy studded dog collar");
         call_other(collar, "set_value", 25);
         move_object(collar, rotweiler);
      }
   }
   if(arg)
      return;
   short_desc = "A small brickroad leading south";
   long_desc = "A small brickroad leading south.\n" +
               "To the north you can exit through an iron gate.\n" +
               "To the east and west you can see a beautiful garden.\n";
   set_light(1);
   dest_dir =
   ({
       "players/kantele/garden_west", "west",
       "room/plane5", "north",
       "players/kantele/garden_east", "east",
       "players/kantele/courtyard", "south"
    });
   items =
   ({
        "road", "Just a small brickroad"
    });
}
