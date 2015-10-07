inherit "room/room";

reset(arg)
{
   if(!arg)
   {
      short_desc = "silent workroom";
      long_desc = "Kitiara's silent workroom.\n";
      set_light(1);
      dest_dir =
      ({
          "room/pub2", "pub",
          "players/kantele/store.c", "south"
       });
   }
   if(!present("torch"))
   {
      object torch;
      torch = clone_object("obj/torch");
      torch->set_name("torch");
      torch->set_fuel(9999);
      torch->set_weight(1);
      move_object(torch, this_object());
   }
   if(!present("money"))
   {
      object money;
      money = clone_object("obj/money");
      money->set_money(100000);
      move_object(money, this_object());
   }
}
