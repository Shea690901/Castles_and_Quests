inherit "room/room";

int rope;

init()
{
   ::init();
   add_action("down","down");
   add_action("down","climb");
   add_action("jump_down","jump");
}

reset(arg)
{
   if(arg)
      return;
   short_desc = "In a room with a pit";
   long_desc = "You are in a room with a pit. The only exit seems to be west.\n" +
               "You can see a large pillar standing beside the pit.\n";
   dest_dir =
   ({
       "players/kantele/kitiaras_crossing", "west",
       "players/kantele/snake_pit", "down"
    });
   items =
   ({
        "pit", "You look down into the pit.\nIt seems slipery " +
               "and impossible to climb down",
        "pillar", "A large stone pillar standing by the pit"
    });
}
   
down(str)
{
   if(query_verb() == "climb" && str == "up")
      return 0;
   if(!rope)
   {
      write("You would fall down the pit and possible hurt yourself.\n");
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
      if(!rope)             /* added by Angmar */
      {
         write("You wouldn't be able to get up again.\n");
         return 1;
      }
      write("You throw yourself into the pit !\n");
      write("You hit the dirt hard......\n");
      call_other(this_player(), "hit_player", 20);
      call_other(this_player(), "move_player", "jump_down#players/kantele/snake_pit");
      return 1;
   }
   write("You jump up and down, but get tired after a while.\n");
   return 1;
}
