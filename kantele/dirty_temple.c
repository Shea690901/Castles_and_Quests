inherit "room/room";

object fiend;

reset(arg)
{
   if(!fiend || !living(fiend))
   {
      fiend = clone_object("obj/monster");
      call_other(fiend, "set_name", "pit fiend");
      call_other(fiend, "set_alias", "fiend");
      call_other(fiend, "set_alt_name", "demon");
      call_other(fiend, "set_level",16);
      call_other(fiend, "set_al", -300);
      call_other(fiend, "set_short", "A huge Pit Fiend is here");
      call_other(fiend, "set_aggressive", 1);
      call_other(fiend, "set_wc",20);
      call_other(fiend, "set_ac",2);
      call_other(fiend, "set_chance",30);
      call_other(fiend, "set_spell_mess1",
                 "The Pit Fiend casts a firebolt at you.");
      call_other(fiend, "set_spell_mess2",
                 "You are hit by a firebolt");
      call_other(fiend, "set_spell_dam",15);
      move_object(fiend,this_object());
   }
   if(arg)
      return;
   short_desc = "In the Evil Temple";
   long_desc = "You are in a Evil Temple.\n" +
               "Behind the altar to the south you can\n" +
               "see a huge statue of Kali. To the west a\n" +
               "rickety bridge leads into the darkness.\n";
   set_light(1);
   dest_dir =
   ({
       "players/kantele/dirty_anteroom", "north",
       "players/kantele/behind_altar", "south",
       "players/kantele/on_bridge.c", "west"
    });
   items = ({ "bridge", "The bridge looks very frail" });
}
