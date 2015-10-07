inherit "room/room";

object matilda;

reset(arg)
{
   if(!matilda || !living(matilda))
   {
      object poker;
      matilda = clone_object("obj/monster");
      call_other(matilda, "set_name", "matilda");
      call_other(matilda, "set_level",9);
      call_other(matilda, "set_al",100);
      call_other(matilda, "set_short", "Matilda the fat old cook is here");
      call_other(matilda, "set_aggressive", 1);
      call_other(matilda, "set_wc",10);
      call_other(matilda, "add_money", random(250));
      move_object(matilda, this_object());
      poker = clone_object("obj/weapon");
      call_other(poker, "set_value",10);
      call_other(poker, "set_name", "poker");
      call_other(poker, "set_wc",14);
      move_object(poker, matilda);
   }
   if(arg)
      return;
   short_desc = "Kitchen";
   long_desc = "A hot very hot kitchen, which looks very clean.\n" +
               "You can see a store room to the south and\n" +
               "to the north you can see the dining room.\n";
   set_light(1);
   dest_dir =
   ({
       "players/kantele/dining_room","north",
       "players/kantele/store_room","south"
    });
}
