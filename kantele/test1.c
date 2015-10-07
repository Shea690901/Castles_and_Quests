inherit "room/room";

int moved;

south()
{
   if(moved == 2)
   {
      write("You enter the small hole.\n");
      this_player()->move_player("south#players/kantele/cellar_passage");
      return 1;
   }
   else
      return 0;
}

move(arg)
{
   if(arg != "barrel" && arg != "barrels" || moved == 2)
   {
      write("move what ?\n");
      return 1;
   }
   else
   {
      if(call_other(this_player(), "query_str", 0) < 14)
 /* Changed to depend on strength, not level.  /Gwendolyn  */
      {
         write("You are not strong enough to move the barrels.\n");
         say(call_other(this_player(), "query_name", 0) +
             " tries to move the barrels, but fails.\n");
         return 1;
      }
      write("You move the barrels and reveal a secret passage leading south.\n");
      moved = 2;
      say(call_other(this_player(), "query_name", 0) +
          " moves some of the barrels.\n");
      return 1;
   }
}

reset(arg)
{
   moved = 1;
   if(arg)
      return;
   short_desc = "You are in a large dark hall";
   long_desc = "You are in a large dark hall.\n" +
               "You can enter the stairway to the west.\n";
   set_light(0);
   dest_dir = ({ "players/kantele/stairway_down.c","west" });
}

init()
{
   ::init();
   add_action("move", "move");
   add_action("south", "south");
}
