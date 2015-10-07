inherit "room/room";

object kitiara;

reset(arg)
{
   if(!kitiara || !living(kitiara))
   {
      kitiara = clone_object("obj/monster");
      call_other(kitiara, "set_name", "kitiara");
      call_other(kitiara, "set_level",20);
      call_other(kitiara, "set_al",-1000);
      call_other(kitiara, "set_short", "Kitiara the Witch is here");
      call_other(kitiara, "set_chance",30);
      call_other(kitiara, "set_aggressive", 1);
      call_other(kitiara, "set_spell_mess1",
                "Kitiara casts a flashing glance at you !");
      call_other(kitiara, "set_spell_mess2",
                "You are hit by the flashing glance !");
      call_other(kitiara, "set_spell_dam",20);
      call_other(kitiara, "set_wc",20);
      move_object(kitiara, this_object());
   }
   if(arg)
      return;
   short_desc = "In a livingroom";
   long_desc = "You are in Kitiaras livingroom, a comfortable room where it\n" +
               "should be possible to relax. The room is dimly lit from a\n" +
               "hole in the ceiling.\n";
   dest_dir =
   ({
       "players/kantele/kitiaras_innerhall", "north",
       "players/kantele/kitiaras_smallroom", "east",
       "players/kantele/kitiaras_strangeroom", "west",
    });
   items = ({ "hole", "As you look up in the whole, you see only light" });
}
