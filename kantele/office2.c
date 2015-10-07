inherit "room/room";

reset(arg)
{
   if(arg)
      return;
   short_desc = "Kantele's workroom";
   long_desc = "You are in Kanteles workroom.\n" +
               "A large oak desk covers most of the room.\n" +
               "You can go north into the lab or east into a small room.\n" + 
               "You can see a massive oak desk against the wall.\n";
   set_light(1);
   dest_dir =
   ({
       "players/kantele/lab", "north",
       "players/kantele/knights_room", "east"
    });
}
