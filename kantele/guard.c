inherit "room/room";

int gate_is_open;
object watchman,sturdy_sword,dog;

reset(arg)
{
   gate_is_open = 0;
   if(!watchman || !living(watchman))
   {
      watchman = clone_object("obj/monster");
      call_other(watchman, "set_name", "watchman");
      call_other(watchman, "set_level",14);
      call_other(watchman, "set_short", "The night watchman is here");
      call_other(watchman, "set_ac", 4);
      call_other(watchman, "set_wc",15);
      call_other(watchman, "set_aggressive", 1);
      move_object(watchman, this_object());
      sturdy_sword  = clone_object("obj/weapon");
      call_other(sturdy_sword, "set_name", "A sword");
      call_other(sturdy_sword, "set_short", "A sturdy sword");
      call_other(sturdy_sword, "set_class",15);
      call_other(sturdy_sword, "set_alt_name", "sword");
      call_other(sturdy_sword, "set_alias","sword");
      call_other(sturdy_sword, "set_value",700);
      call_other(sturdy_sword, "wield","sword");
      move_object(sturdy_sword, watchman);
      dog  = clone_object("obj/monster");
      call_other(dog, "set_name", "dog");
      call_other(dog, "set_short", "A guard dog is here");
      call_other(dog, "set_ac",1);
      call_other(dog, "set_level",8);
      call_other(dog, "set_wc",10);
      move_object(dog, this_object());
   }
   if(arg)
     return;
   short_desc = "A guard room";
   long_desc = "A guard room. You can leave to east into a hall,\n" +
             "west into a torture room and south into a dungeon corridor.\n" +
             "A large iron ring is fastende in the wall.\n";
   set_light(0);
   dest_dir =
   ({
       "players/kantele/torture_chamber","west",
       "players/kantele/west_temple","east",
       "players/kantele/dungeon_corridor.c","south"
    });
}

init()
{
   ::init();
   add_action("pull_ring", "pull");
}

pull_ring(str)
{
   if(str != "ring")
      return 0;
   write("You pull the ring.\n");
   say(call_other(this_player(), "query_name") + " pulls the ring.\n");
   if(gate_is_open == 1)
   {
      gate_is_open = 0;
      tell_room(this_object(), "You hear a grinding sound.\n");
   }
   else
   {
      gate_is_open = 1;
      tell_room(this_object(), "You hear a crunshing sound.\n");
   }
   return 1;
}



query_gate() {
   return !gate_is_open;
}
