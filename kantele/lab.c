inherit "room/room";

reset(arg)
{
   if(!present("scroll"))
      move_object(clone_object("players/kantele/scroll"), this_object());
   if(arg)
      return;
   short_desc = "Kanteles laboratory";
   long_desc = "You are in Kanteles laboratory. You can go south into\n" +
               "her workroom or you can enter the hall to the east.\n" +
               "The room is covered with strange devices.\n" +
               "An odd smell penetrates the air.\n";
   set_light(1);
   dest_dir =
   ({
       "players/kantele/upper_hall", "east",
       "players/kantele/office2", "south"
    });
}
