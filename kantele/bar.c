inherit "room/room";

reset(arg)
{
   if(arg)
      return;
   short_desc = "A small private barroom";
   long_desc = "You are in a small private bar.\n" +
               "You can leave west behind the bar,\n" +
               "enter the trophy room to the south and\n" +
               "to the north you can see into a livingroom.\n";
   set_light(1);
   dest_dir =
   ({
       "players/kantele/living_room", "north",
       "players/kantele/trophy_room", "south",
       "players/kantele/behind_bar", "west"
    });
   items =
   ({
        "bar", "The bar is quite empty actually..",
        "livingroom", "A very tasteful livingroom",
        "trophy room", ""
    });
}
