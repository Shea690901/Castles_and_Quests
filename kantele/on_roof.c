inherit "room/room";

reset(arg)
{
   if(arg)
      return;
   short_desc = "You are on the roof";
   long_desc = "You are on the roof. If you hadn't known better you could\n" +
               "swear the building to the north looks like a stable.\n" +
               "You think you can smell sulphur here.\n";
   set_light(1);
   dest_dir =
   ({
       "players/kantele/stable", "north",
       "players/kantele/upper_hall", "south"
    });
}

init()
{
   ::init();
   add_action("down", "jump");
}

down(arg)
{
   if(arg != "down" && arg != "out")
   {
      write("You throw yourself over the edge !\n");
      write("You hit the dirt hard......\n");
      call_other(this_player(), "hit_player",20);
      say(call_other(this_player(), "query_name") + " throws himself down from the rof.\n");
      call_other(this_player(), "move_player", "down#players/kantele/garden_west");
      return 1;
   }
}
