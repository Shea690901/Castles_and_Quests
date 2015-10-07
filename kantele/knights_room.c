inherit "room/room";

object knight, chainmail, blade;

reset(arg)
{
   if(!knight || !living(knight))
   {
      knight = clone_object("obj/monster");
      call_other(knight, "set_name", "knight");
      call_other(knight, "set_short", "A black knight");
      call_other(knight, "set_level",19);
      call_other(knight, "set_whimpy");
      call_other(knight, "set_al", -200);
      call_other(knight, "set_hp",250);
      call_other(knight, "set_wc",25);
      call_other(knight, "set_ac", 4);
      call_other(knight, "set_aggressive", 1);
      call_other(knight, "set_move_at_reset");
      move_object(knight, this_object());
      chainmail = clone_object("obj/armour");
      call_other(chainmail, "set_ac",4);
      call_other(chainmail, "set_alias","armour");
      call_other(chainmail, "set_type","armour");
      call_other(chainmail, "set_alias","mail");
      call_other(chainmail, "set_name", "chainmail");
      call_other(chainmail, "set_value", 500);
      call_other(chainmail, "set_short", "A death black chainmail");
      call_other(chainmail, "set_weight",5);
      move_object(chainmail, knight);
      blade = clone_object("obj/weapon");
      call_other(blade, "set_name", "blade");
      call_other(blade, "set_alt_name", "demon blade");
      call_other(blade, "set_alias", "black blade");
      call_other(blade, "set_short", "A black demon blade");
      call_other(blade, "set_hit_func", this_object());
      call_other(blade, "set_value",5000);
      call_other(blade, "set_wield_func", this_object());
      move_object(blade, knight);
   }
   if(arg)
      return;
   short_desc = "Knights room";
   long_desc = "You are in 'the knights room'. The rooms simple furnishing\n" +
               "and black dekor shows what type of man he is.\n" +
               "You can enter the training room to the east.\n";
   set_light(1);
   dest_dir =
   ({
       "players/kantele/office2", "west",
       "players/kantele/training_room", "east"
    });
}

wield(weap)
{
   int alig, evil;
   alig = call_other(this_player(),"query_alignment");
   if(alig > 0)
   {
      write("The blade gives you an electric jolt.\n");
      write("The blade don't like you, you're too stinking good.\n");
      call_other(this_player(), "hit_player", 20);
      return 0;
   }
   if(!evil)
   {
      evil = 1;
      call_other(this_player(),"add_alignment",-4);
      write("You feel more evil.\n");
   }
   return 1;
}

weapon_hit(attacker)
{
   int alig, dam;
   alig = call_other(attacker,"query_alignment");
   if(alig > 0)
   {
      dam = random(25);
      if(dam < 10)
	 return 0;
      if(dam < 15)
	 write("The blade flashes.\n");
      else if(dam < 20)
	 write("The blade flashes happily.\n");
      else if(dam < 24)
	 write("The blade flashes happily, and gives out a happy cry.\n");
      else if(dam == 24)
      {
         write("The blade flashes happily, and you can feel its evil might.\n");
         call_other(this_player(), "heal_self", random(10));
         write("You feel stronger.\n");
	 dam = dam + random(20);
	 if(dam == 63)
         {
	    call_other(this_player(),"heal_self",random(10));
	    tell_room(this_object(), "The black demon blade flashes, and gives out a happy cry.\n");
         }
         else
            tell_room(this_object(), "The black demon blade flashes!\n");
      }
      return dam;
   }
   dam = random(15);
   return dam;
}
