int charges, i;

id(str) { return str == "scroll"; }
short() { return "a small magical scroll"; }
long() { write("A small magical scroll. Somehow it feels a bit evil...\n"); }
get() { return 1; }
query_weight() { return 1; }
query_value() { return 100; }
reset() { i = random(6); }
init() { add_action("read"); add_verb("read"); }

read(arg)
{
   if(arg != "scroll")
   {
      notify_fail("Read what?\n");
      return 0;
   }
   if(environment(this_player())->realm() == "NT")
   {
      write("Nothing happens.\n");
      return 1;
   }
   write("As you read the scroll everything shimmers away...\n");
   switch(i)
   {
      case 1:
      {
         call_other(this_player(), "move_player", "X#players/kantele/snake_pit");
         i = random(6);
         return 1;
      }
      case 2:
      {
	 call_other(this_player(), "move_player", "X#room/church");
         break;
      }
      case 3:
      {
         call_other(this_player(), "move_player", "X#room/pub2");
         break;
      }
      case 4:
      {
	 call_other(this_player(), "move_player", "X#room/giant_lair");
         break;
      }
      case 5:
      {
         call_other(this_player(), "move_player", "X#players/kantele/bar");
         break;
      }
      default:
      {
         call_other(this_player(), "move_player", "X#players/kantele/on_roof");
         break;
      }
   }
   move_object(this_object(), "players/kantele/store");
   write("The scroll suddenly disappears !\n");
   return 1;
}
