inherit "obj/monster";

/* The heart beat is started in living.h when we are attacked. */

reset(arg)
{
   object weapon;
   object key;
   ::reset(arg);
   if(arg)
      return;
   set_level(10);
   set_hp(200);
   set_wc(16);
   set_name("manservant");
   set_alias("servant");
   alignment = 100;
   weapon = clone_object("obj/weapon");
   call_other(weapon, "set_name", "battleaxe");
   call_other(weapon, "set_class", 12);
   call_other(weapon, "set_alias", "battleaxe");
   call_other(weapon, "set_value",250);
   call_other(weapon, "set_weight", 3);
   move_object(weapon, this_object());
   key = clone_object("obj/treasure");
   call_other(key, "set_id", "key");
   call_other(key, "set_alias", "mansion key");
   call_other(key, "set_short", "A mansion key");
   call_other(key, "set_value", 10);
   call_other(key, "set_weight", 1);
   move_object(key, this_object());
}

short() { return "Kanteles manservant"; }

long()
{
   write("Kanteles manservant is here, he looks mean !\n");
   if(hit_point > max_hp - 40)
      write("He seems to be in a good shape.\n");
}

can_put_and_get(str)
{
   if(!str)
   {
      write(name + " says: Over my dead body.\n");
      return 0;
   }
   return 1;
}
