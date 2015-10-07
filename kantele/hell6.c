inherit "room/room";

object barbed_devil;

reset(arg)
{
   if(!barbed_devil || !living(barbed_devil))
   {
      int i;
      for(i = 2; i; i--)
      {
         barbed_devil = clone_object("obj/monster");
         call_other(barbed_devil, "set_name", "devil");
         call_other(barbed_devil, "set_alias", "barbed devil");
         call_other(barbed_devil, "set_level",14);
         call_other(barbed_devil, "set_short", "A barbed devil");
         call_other(barbed_devil, "set_wc",14);
         call_other(barbed_devil, "set_ac",5);
         call_other(barbed_devil, "set_aggressive", 1);
         call_other(barbed_devil, "set_move_at_reset");
         call_other(barbed_devil, "set_whimpy");
         call_other(barbed_devil, "set_chance",30);
         call_other(barbed_devil, "set_spell_mess1",
	            "The barbed devil lashes out with its tail.");
	 call_other(barbed_devil, "set_spell_mess2",
	            "You are hit by the barbed tail");
	 call_other(barbed_devil, "set_spell_dam",30);
         move_object(barbed_devil, this_object());
      }
   }
   if(arg)
      return;
   short_desc = "You are in hell";
   long_desc = "You are in hell, the smell of sulphur penetrates everything.\n";
   set_light(1);
   dest_dir =
   ({
       "players/kantele/hell2", "north",
       "players/kantele/hell7", "south",
       "players/kantele/hell5", "east",
       "players/kantele/hell6", "west"
    });
}
