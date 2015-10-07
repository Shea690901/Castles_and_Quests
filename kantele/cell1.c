inherit "room/room";

int helped;
object solar, shackles, bag, money;

id(str)
{
   return ::id(str) || str == "celldoor" || str == "door";
}

long(str)
{
   if(str == "celldoor" || str == "door")
   {
      if(call_other("players/kantele/guard_room","query_gate1"))
      {
         write("The celldoor is closed.\n");
         return 1;
      }
      else
         write("The celldoor is open.\n");
      return 1;
   }
   if(str)
      return ::long(str);
   write("In a small dirty cell.\nA heavy steel celldoor leads north. It is ");
   if(call_other("players/kantele/guard_room","query_gate1"))
      write("closed.\n");
   else
      write("open.\n");
   return 1;
}

init()
{
   ::init();
   add_action("nomove", "north");
   add_action("open_shackles", "open");
}

nomove()
{
   if(call_other("players/kantele/guard_room","query_gate1"))
   {
      write("The celldoor is closed.\n");
      return 1;
   }
}

open_shackles(str)
{
   if(str == "door" || str == "celldoor")
   {
      write("You cannot do that.\n");
      return 1;
   }
   if(!str || str != "shackles" || helped == 0 || !(solar))
      return 0;
   write("Ok.\n");
   helped = 0;
   write("The Solar thanks you.\n");
   write("The Solar gives you a bag.\n");
   destruct(solar);
   write("The Solar disappears in a puff of smoke !\n");
   bag = clone_object("obj/bag");
   money = clone_object("obj/money");
   call_other(money, "set_money", random(2500));
   move_object(money, bag);
   move_object(bag,this_player());
   return 1;
}

reset(arg)
{
    helped = 1;
    if(!solar || !living(solar))
    {
       solar  = clone_object("obj/monster");
       call_other(solar, "set_name", "solar");
       call_other(solar, "set_level",19);
       call_other(solar, "set_short","A beautiful Solar is here");
       call_other(solar, "set_al", 300);
       call_other(solar, "set_wc",30);
       call_other(solar, "set_ac",3);
       call_other(solar, "set_chance",30);
       call_other(solar, "set_spell_mess1",
                  "The Solar throws a fireball");
       call_other(solar, "set_spell_mess2",
                  "You are hit by a fireball");
       call_other(solar, "set_spell_dam",40);
       move_object(solar,  this_object());
       shackles = clone_object("players/kantele/shackles");
       move_object(shackles, solar);
   }
   if(arg)
      return;
   short_desc = "A small dirty cell";
   dest_dir =
   ({
       "/players/kantele/dungeon_corridor", "north"
    });
}
