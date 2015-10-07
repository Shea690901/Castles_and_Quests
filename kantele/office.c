inherit "room/room";

reset(arg)
{
   if(arg)
      return;
   short_desc = "Dusty office";
   long_desc = "You are in a very dusty office.\n";
   set_light(1);
   dest_dir = ({ "players/kantele/trophy_room", "north" });
}
