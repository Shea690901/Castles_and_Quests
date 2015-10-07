inherit "room/room";

object harness, nightmare;

reset(arg)
{
   if(!harness || !present(harness))
   {
      harness = clone_object("obj/treasure");
      call_other(harness, "set_id", "harness");
      call_other(harness, "set_short", "The nightmare's harness");
      call_other(harness, "set_alias", "harness");
      call_other(harness, "set_value",600);
      move_object(harness, this_object());
   }
   if(!nightmare || !living(nightmare))
   {
      nightmare = clone_object("obj/monster");
      call_other(nightmare, "set_name", "nightmare");
      call_other(nightmare, "set_alias", "nightmare");
      call_other(nightmare, "set_level",19);
      call_other(nightmare, "set_al", -300);
      call_other(nightmare, "set_short", "A large nightmare is here");
      call_other(nightmare, "set_wc",15);
      call_other(nightmare, "set_ac",2);
      call_other(nightmare, "set_aggressive", 1);
      call_other(nightmare, "set_chance",30);
      call_other(nightmare, "set_spell_mess1",
                 "The demon stead breaths fire at you.");
      call_other(nightmare, "set_spell_mess2",
                 "You are hit by the firebreath");
      call_other(nightmare, "set_spell_dam",40);
      move_object(nightmare, this_object());
   }
   if(arg)
      return;
   short_desc = "In the Nightmare's stable";
   long_desc = "You are in the Nightmare's stable.\n" +
               "The smell of sulphur lies heavy in the air.\n" +
               "You can flee south onto the roof.\n";
   set_light(1);
   dest_dir = ({ "players/kantele/on_roof","south" });
}
