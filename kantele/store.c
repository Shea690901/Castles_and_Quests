inherit "room/room";

reset(arg)
{
   if(!present("money"))
   {
      object money;
      money = clone_object("obj/money");
      call_other(money, "set_money",1);
      move_object(money,this_object());
   }
   if(arg)
      return;
   short_desc = "store room";
   long_desc = "Kitiaras store room.. \n";
   set_light(1);
   dest_dir = ({ "players/kantele/workroom" , "north" });
}
