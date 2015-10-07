inherit "room/room";

int moved;

reset(arg)
{
   moved = 1;
   if(arg)
      return;
   short_desc = "You are in a large dark hall";
   long_desc = "You are in a large dark hall.\n" +
               "You can reach the stairway to the west.\n" +
               "There are some barrels here.\n";
   set_light(0);
   dest_dir = ({ "players/kantele/stairway_down", "west" });
   items =
   ({
        "barrel", "An old wine barrel",
        "barrels", "Some old wine barrels"
    });
}

init()
{
   ::init();
   add_action("movex", "move");
   add_action("north", "north");
   add_action("north", "enter");
}

north(str)
{
   if(query_verb() == "enter" && str != "passage")
   {
      write("You cannot enter that.\n");
      return 1;
   }
   if(moved == 2)
   {
      write("You enter the narrow passage.\n");
      call_other(this_player(), "move_player", "north#players/kantele/cellar_passage");
      return 1;
   }
}

movex(arg)
{
   if(arg != "barrel" && arg != "barrels")
   {
      write("move what ?\n");
      return 1;
   }
   if(moved == 2)
   {
      write("They cannot be moved more.\n");
      return 1;
   }
   if(this_player()->query_str() < 14)  /* Level -> Str  /Gwendolyn  */
   {
      write("You are not strong enough to move the barrels.\n");
      say(call_other(this_player(), "query_name", 0) +
	  " tries to move the barrels, but fails.\n");
      return 1;
   }
   write("You move the barrels to reveal a\nsecret passage leading north.\n");
   moved = 2;
   say(call_other(this_player(), "query_name", 0) +
       " moves some of the barrels.\n");
   return 1;
}
