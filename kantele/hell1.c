inherit "room/room";

object manes;

reset(arg)
{
   int i;
   if(!manes || !living(manes))
   {
      for(i = 4; i; --i)
      {
         manes = clone_object("obj/monster");
         call_other(manes, "set_name", "mane");
         call_other(manes, "set_alias", "devil");
         call_other(manes, "set_level",8);
         call_other(manes, "set_short", "A huge mane");
         call_other(manes, "set_long", "A mean hungry mane\n");
         call_other(manes, "set_wc",12);
         call_other(manes, "set_aggressive", 1);
         call_other(manes, "set_move_at_reset");
         call_other(manes, "set_move_at_reset");
         move_object(manes, this_object());
      }
   }
   if(arg)
      return;
   short_desc = "You are in hell";
   long_desc = "You are in hell. The smell of sulphur penetrates everything.\n";
   set_light(1);
   dest_dir =
   ({
       "players/kantele/hell2", "north",
       "players/kantele/hell6", "south",
       "players/kantele/hell2", "east",
       "players/kantele/hell2", "west"
    });
}
