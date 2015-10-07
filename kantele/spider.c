inherit "obj/monster";

reset(arg)
{
   ::reset(arg);
   if(arg)
      return;
   max_hp = 15;
   hit_point = 25;
   level = 10;
   experience = 70000;
   weapon_class = 55;
   set_name("spider");
   alignment = 100;
}

short() { return "A small poison spider"; }

long() { write("A little black spider.\n"); }
