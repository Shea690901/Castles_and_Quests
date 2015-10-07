inherit "room/room";

int shieldi;
object james, shield;

reset(arg)
{
   if(!james || !living(james))
   {
      shield = 0;
      james  = clone_object("obj/monster");
      call_other(james, "set_name", "james");
      call_other(james, "set_level", 12);
      call_other(james, "set_al", 12);
      call_other(james, "set_short", "James the butler is here");
      call_other(james, "set_wc", 10);
      call_other(james, "set_alias","butler");
      call_other(james, "add_money", random(1000));
      move_object(james, this_object());
   }
   if(arg)
      return;
   short_desc = "The inner hall";
   long_desc = "You are in the inner hall.\n" +
               "The walls are lined with shields which\n" +
               "looks like they are loot from some sort of campaign.\n";
   set_light(1);
   dest_dir =
   ({
       "players/kantele/stairway","south",
       "players/kantele/hall", "north",
       "players/kantele/dining_room","west",
       "players/kantele/living_room","east"
    });
}

init()
{
   ::init();
   add_action("south","south");
   add_action("west","west");
   add_action("east","east");
   add_action("get_shield", "pry");
}

south()
{
   if(call_other(this_player(), "query_level", 0) < 20)
   {
      if(james && present(james, this_object()))
      {
         write("James bars your way !\n");
         write("James says: Can you please leave, Sir !\n");
         return 1;
      }
   }
}

west()
{
   if(call_other(this_player(), "query_level", 0) < 20)
   {
      if(james && present(james, this_object()))
      {
         write("James bars your way !\n");
         write("James says: Can you please leave, Sir !\n");
         return 1;
      }
   }
}

east()
{
   if(call_other(this_player(), "query_level", 0) < 20)
   {
      if(james && present(james, this_object()))
      {
         write("James bars your way !\n");
         write("James says: Can you please leave, Sir !\n");
         return 1;
      }
   }
}

get_shield(arg) {
if (arg != "off shield") {
write("pry off what ?\n");
} else {
   if (!present("shield", this_player()) &&  shieldi < 5) {
        shieldi = shieldi +1;
        write("you pry off a shield.\n");
        shield = clone_object("obj/armour");
        call_other(shield, "set_ac",1);
        call_other(shield, "set_name", "shield");
        call_other(shield, "set_alias", "small shield");
        call_other(shield, "set_value", 70);
        call_other(shield, "set_short", "A small metal shield");
        call_other(shield, "set_weight",4);
        call_other(shield, "set_type", "shield");
        move_object(shield, this_player());
        return 1;
                                            }
   else {
        write("the shields are fastened to hard.\n");
        return 1;
        }
}
}
