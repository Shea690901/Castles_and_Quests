inherit "room/room";

object mage, weap;

reset(arg)
{
   if(!mage || !living(mage))
   {
      mage = clone_object("obj/monster.talk");
      call_other(mage, "set_name", "necromancer");
      call_other(mage, "set_alias", "mage");
      call_other(mage, "set_level",19);
      call_other(mage, "set_al", -300);
      call_other(mage, "set_short", "A black robed necromancer");
      call_other(mage, "set_wc",15);
      call_other(mage, "set_ac",2);
      call_other(mage, "set_aggressive", 1);
      call_other(mage, "set_move_at_reset");
      call_other(mage, "set_ep",250000);
      call_other(mage, "set_chance",25);
      call_other(mage, "set_spell_mess2",
                 "You are hit by a fire ball.");
      call_other(mage, "set_spell_dam",30);
      weap  = clone_object("obj/weapon");
      call_other(weap, "set_name", "sword");
      call_other(weap, "set_short", "A sword");
      call_other(weap, "set_class",20);
      call_other(weap, "set_weight",2);
      call_other(weap, "set_value",10000);
      move_object(weap, mage);
      move_object(mage, this_object());
   }
   if(arg)
      return;
   short_desc = "In the mages room";
   long_desc = "In the mages room.\nThis little room only contains a small bed.\n";
   set_light(1);
   dest_dir = ({ "players/kantele/kitiaras_lab", "south" });
}
