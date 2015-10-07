inherit "room/room";

reset(arg)
{
   if(arg)
      return;
   short_desc = "A dirty sleeping room";
   long_desc = "A dirty sleeping room. A single dirty bed\n" +
               "stands in one corner.\n";
   dest_dir = ({ "players/kantele/mechanic_room", "west" });
   items = ({ "bed", "The bed is dirty and smelling, and you should be " +
                      "ashamed to mess around in it" });
}
