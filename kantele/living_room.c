inherit "room/room";

object demon;

reset(arg)
{
   if(!demon || !living(demon))
   {
      demon = clone_object("obj/monster");
      call_other(demon, "set_level", 15);
      call_other(demon, "set_name", "demon");
      call_other(demon,"set_level",12);
      call_other(demon, "set_short", "A household demon");
      call_other(demon, "set_wc", 20);
      call_other(demon, "set_move_at_reset");
      call_other(demon, "set_ac", 2);
      call_other(demon, "set_aggressive", 1);
      move_object(demon, this_object());
   }
   if(arg)
      return;
   short_desc = "A tasteful living room";
   long_desc = "A tasteful living room. An exit leads west into the hall,\n" +
               "you can also leave south into the bar.\n";
   set_light(1);
   dest_dir =
   ({
       "players/kantele/inner_hall", "west",
       "players/kantele/bar", "south"
    });
}
