inherit "room/room";

object sphinx;

reset(arg)
{
   if(!sphinx  || !present(sphinx))
   {
      sphinx  = clone_object("obj/treasure");
      call_other(sphinx, "set_id", "sphinx");
      call_other(sphinx, "set_short", "A huge stone Sphinx stands here");
      call_other(sphinx, "set_weight", 1000);
      move_object(sphinx, this_object());
   }
   if(arg)
      return;
   short_desc = "The Sphinx room";
   long_desc = "This is the Sphinx room.\n";
   set_light(1);
   dest_dir = ({ "players/kantele/west_bridge.c","north" });
}
