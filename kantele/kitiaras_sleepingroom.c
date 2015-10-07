inherit "room/room";

object ring;
int found;

reset(arg)
{
   found = found - 1;
   if(arg)
      return;
   short_desc = "A tidy sleepingroom";
   long_desc = "A tidy sleepingroom with a feminine look.\n" +
               "A large pink bed stands here.\n";
   dest_dir = ({ "players/kantele/kitiaras_innerhall", "east" });
   items = ({ "bed", "The bed is covered with clean silken sheets, it smells of roses" });
}

init()
{
   ::init();
   add_action("search_bed", "search");
}


search_bed(arg)
{
   if(arg == "bed" && found < 1)
   {
      found =3;
      ring = clone_object("players/kantele/ring");
      move_object(ring, this_object());
      write("You found a small ring.\n");
      return 1;
   }
   else if(arg == "bed")
   {
      write("You found nothing.\n");
      return 1;
   }
}
