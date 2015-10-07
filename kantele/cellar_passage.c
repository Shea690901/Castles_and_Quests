inherit "room/room";

int i;
object torch;

reset(arg)
{
   if(arg)
      return;
   short_desc = "In a dark passage";
   long_desc = "In a dark passage going north/south.\n" +
               "The passage is lighted with torches.\n";
   set_light(1);
   dest_dir =
   ({
       "players/kantele/cellar_east", "south",
       "players/kantele/cellar_passage1", "north"
    });
   items = ({ "torches", "You can see some torches" });
}

init()
{
   ::init();
   add_action("get_torch", "get");
}

get_torch(arg)
{
   if(arg != "torch")
      return 0;
   if(!present("torch", this_player()) && i < 3)
   {
      i = i + 1;
      torch = clone_object("obj/torch");
      call_other(torch, "set_name", "torch");
      call_other(torch, "set_fuel", 2000);
      call_other(torch, "set_weight", 1);
      move_object(torch, this_player());
      write("Ok.\n");
      return 1;
   }
}
