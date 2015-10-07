inherit "room/room";

object ogre;
int payed, rope, bridge_is_down;

init()
{
   ::init();
   add_action("pay_troll", "pay");
   add_action("down", "down");
   add_action("down", "climb");
   add_action("west", "west");
   add_action("tie", "tie");
   add_action("untie", "untie");
   add_action("jump_down", "jump");
}

pay_troll(str)
{
   if(str == "troll" && ogre)
   {
      write("The troll doesn't want your stinking money!\n");
      return 1;
   }
}

west()
{
   if(call_other(this_player(), "query_level", 0) < 20)
   {
      if(bridge_is_down == 1)
      {
         write("The bridge is down.\n");
         return 1;
      }
      else
      {
         if(ogre  && present(ogre, this_object()) && payed == 1)
         {
            write("The Troll bars your way !\n");
            return 1;
         }
      }
   }
}

reset(arg)
{
   payed = 1;
   bridge_is_down = 0;
   if(!ogre  || !living(ogre))
   {
      ogre  = clone_object("obj/monster");
      call_other(ogre, "set_name", "troll");
      call_other(ogre, "set_level",19);
      call_other(ogre, "set_al", -300);
      call_other(ogre, "set_short", "A large Troll is here");
      call_other(ogre, "set_wc",25);
      call_other(ogre, "set_ac",2);
      call_other(ogre, "add_money", random(1000) + 100);
      move_object(ogre, this_object());
   }
   if(arg)
      return;
   short_desc = "Beside a rickety wooden bridge";
   long_desc =  "A rickety wooden bridge extends across the chasm\n" +
                "to the west, vanishing into the darkness.\n" +
                "A sign posted on the bridge reads:\n" +
                "'STOP! Pay the troll!'\n";
   dest_dir =
   ({
       "players/kantele/dirty_temple", "east",
       "players/kantele/bottom_chasm", "down",
       "players/kantele/west_bridge", "west"
    });
}

down()
{
   if(!rope)
   {
      write("You would fall down the chasm and possible hurt yourself.\n");
      return 1;
   }
}

tie(str)
{
   if(str != "bridge")
      return 0;
   rope = 1;
   return 1;
}

untie(str)
{
   rope = 0;
   return 1;
}

query_rope() { return rope; }

jump_down(arg)
{
   if(arg == "down")
   {
      write("You throw yourself into the chasm !\n");
      write("You hit the dirt hard......\n");
      call_other(this_player(), "hit_player", 20);
      call_other(this_player(), "move_player", "jump_down#players/kantele/bottom_chasm");
       return 1;
   }
}
