inherit "room/room";

object spider;

reset(arg)
{
   if(!spider || !living(spider))
   {
      spider = clone_object("players/kantele/spider.c");
      move_object(spider, this_object());
   }
   if(arg)
      return;
   short_desc = "A dusty store room";
   long_desc = "This is a small dusty store room.\n" +
          "It looks like it has been a very long time since anyone used it.\n";
   set_light(1);
   dest_dir = ({ "players/kantele/kitchen","north" });
}
