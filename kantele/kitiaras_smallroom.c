inherit "room/room";

int value, cost, strength, heal,found;
string name, short_desc, mess;
object potion, drink;

reset(arg)
{
   found = 0;
   if(arg)
      return;
   short_desc = "A small dirty room";
   long_desc = "This is a small dirty room with lots of strange rubble.\n";
   set_light(0);
   dest_dir = ({ "players/kantele/kitiaras_livingroom","west" });
}

init()
{
   ::init();
   add_action("search_rubble", "search");
}

search_rubble(arg)
{
   if(arg == "rubble" && found < 1)
   {
      found = 1;
      drink = clone_object("obj/drink");
      if(!call_other(drink, "set_value", "potion" + "#" +
	 "A bottle with strange contents" + "#" + "You are totally healed" +
         "#" + 1000 + "#" + 500 + "#" +0))
      {
         write("Error in creating drink.\n");
         destruct(drink);
      }
      move_object(drink, this_object());
      write("You found a strange bottle.\n");
      return 1;
   }
   else if(arg == "rubble")
   {
      write("You found nothing.\n");
      return 1;
   }
}
