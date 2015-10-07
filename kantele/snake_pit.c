inherit "room/room";

int rope;
object snake, orb, bar;

reset(arg)
{
   if(!snake || !living(snake))
   {
      int i;
      for(i = random(10); i > 0; --i)
      {
         snake  = clone_object("obj/monster");
	 call_other(snake, "set_name", "snake");
	 call_other(snake, "set_level", random(4) + 1);	/* Pell */
	 call_other(snake, "set_short", "A small poison snake");
	 call_other(snake, "set_wc", random(29) + 1); /* Pell */
	 call_other(snake, "set_aggressive", 1);
	 move_object(snake, this_object());
      }
      orb = clone_object("obj/treasure");
      call_other(orb, "set_name", "orb");
      call_other(orb, "set_value",750);
      call_other(orb, "set_short", "A small gold orb");
      call_other(orb, "set_alias", "gold orb");
      move_object(orb, this_object());
      bar = clone_object("obj/treasure");
      call_other(bar, "set_name", "bar");
      call_other(bar, "set_value",750);
      call_other(bar, "set_short", "A gold bar");
      call_other(bar,"set_alias", "gold bar");
      move_object(bar, this_object()); 
   }
   if(arg)
      return;
   set_light(1);
   short_desc = "You are in the snake pit";
   dest_dir = ({ "players/kantele/snake_room", "up" });
}

long()
{
   write("You are in the snake pit. It seems impossible to get out!!!\n");
   if(call_other("players/kantele/snake_room", "query_rope"))
      write("There is a rope hanging down from above.\n");
}

init()
{
   ::init();
   add_action("go_up", "up");
}

go_up() 
{
   if(!call_other("players/kantele/snake_room","query_rope"))
   {
      write("You can't go stright up without some kind of support.\n");
      return 1;
   }
}

tie(str)
{
   if(str != "pillar")
      return 0;
   rope = 1;
   return 1;
}

id(str) { return str == "pillar"; }

untie(str)
{
   rope = 0;
   return 1;
}

exit(ob)
{
   if(present("gold orb", ob))
   {
      if(ob->set_quest("kantele"))
         write("You have fulfilled Kanteles quest.\n");
   }
}
