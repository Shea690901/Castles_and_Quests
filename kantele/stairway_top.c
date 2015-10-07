inherit "room/room";

reset(arg)
{
   if(arg)
      return;
   set_light(1);
   short_desc = "You are on the upper landing";
   long_desc = "You are on a landing in the stairway. This place gives you \n" +
               "a bad feeling, you feel truly depressed at the thought of\n" +
               "going further up the stairway.\n";
   dest_dir = ({ "players/kantele/stairway_up", "down" });
}

init()
{
   ::init();
   add_action("up"); add_verb("up");
}

up()
{

/* Changed by Angmar */
/* This is a deadly trap. I don't like deadly traps. */

   if(!"players/kantele/snake_room"->query_rope())
   {
      write("You would fall down the snake-pit and not be able\n");
      write("to get up again.\n");
      return 1;
   }
   write("As you start to walk up the stairs a pit opens under your feet.\n");
   write("You fall, down into the pit.........\n\n");
   call_other(this_player(), "move_player", "up#players/kantele/snake_pit");
   return 1;
}

