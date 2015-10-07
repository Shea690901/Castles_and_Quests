inherit "room/room";

object priest, mace, key;

reset(arg)
{
   if(!priest || !living(priest))
   {
      priest = clone_object("obj/monster.talk");
      call_other(priest, "set_name", "priest");
      call_other(priest, "set_level",14);
      call_other(priest, "set_al", -200);
      call_other(priest, "set_short", "A blackrobed Priest");
      call_other(priest, "set_ac",2);
      call_other(priest, "set_wc",15);
      call_other(priest, "set_aggressive", 1);
      call_other(priest, "set_move_at_reset");
      call_other(priest, "set_chance",30);
      call_other(priest, "set_spell_mess1",
                 "The priest throws a curse.");
      call_other(priest, "set_spell_mess2",
                 "The priest throws a curse at you, the curse weakens you");
      call_other(priest, "set_spell_dam",40);
      key = clone_object("obj/treasure");
      call_other(key, "set_id", "key");
      call_other(key, "set_alias", "cellar key");
      call_other(key, "set_short", "A cellar key");
      call_other(key, "set_value", 10);
      call_other(key, "set_weight", 1);
      move_object(key, priest);
      mace = clone_object("obj/weapon");
      call_other(mace, "set_name", "mace");
      call_other(mace, "set_value",250);
      call_other(mace, "set_class",17);
      move_object(mace, priest);
      move_object(priest, this_object());
   }
   if(arg)
      return;
   short_desc = "A small dirty room";
   long_desc = "A small dirty room. It looks like this room was made\n" +
               "for some reason, which is lost to you.\n";
   set_light(0);
   dest_dir = ({ "players/kantele/dirty_corridor", "south" });
}
