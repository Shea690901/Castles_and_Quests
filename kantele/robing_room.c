inherit "room/room";

reset(arg)
{
   if(arg)
      return;
   short_desc = "In the robing room";
   long_desc = "In a small robing room. To the east you can see an altar.\n";
   set_light(0);
   dest_dir = ({ "players/kantele/behind_altar", "east" });
}
