inherit "room/room";

object gardener;

reset(arg)
{
   if(!gardener || !living(gardener))
   {
      object bag;
      object money;
      gardener = clone_object("obj/monster");
      call_other(gardener, "set_name", "gardener");
      call_other(gardener, "set_level", 6);
      call_other(gardener, "set_al", 100);
      call_other(gardener, "set_short", "The old bent gardener is here");
      call_other(gardener, "set_wc", 6);
      move_object(gardener, this_object());
      bag = clone_object("obj/bag");
      move_object(bag, gardener);
      money = clone_object("obj/money");
      call_other(money, "set_money", random(650));
      move_object(money, bag);
   }
   if(arg)
      return;
   short_desc = "The gardeners shack";
   long_desc = "This is the gardeners shack. It is small, dark and dirty.\n";
   set_light(1);
   dest_dir = ({ "players/kantele/courtyard", "west" });
}
