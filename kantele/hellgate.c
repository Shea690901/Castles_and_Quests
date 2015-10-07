inherit "room/room";

int gate_is_open;
object gatekeeper,robe;

id(str) { return ::id(str) || str == "gate"; }

long(str)
{
   if(str == "gate")
   {
      if(gate_is_open == 1)
         write("The gate is shimmering black sinister.\n");
      else
         write("The gate looks compleatly dead.\n");
      return 1;
   }
   ::long(str);
}

init()
{
   ::init();
   add_action("enter", "enter");
   add_action("open_gate", "open");
   add_action("close_gate", "close");
}

reset(arg)
{
   if(!gatekeeper || !living(gatekeeper))
   {
      gatekeeper = clone_object("obj/monster");
      call_other(gatekeeper, "set_name", "gatekeeper");
      call_other(gatekeeper, "set_level",19);
      call_other(gatekeeper, "set_short", "The grayrobed Gatekeeper");
      call_other(gatekeeper, "set_long","He looks VERY tough");
      call_other(gatekeeper, "set_wc", 35);
      call_other(gatekeeper, "set_ac",2);
      call_other(gatekeeper, "set_hp",450);
      move_object(gatekeeper, this_object());
      robe  = clone_object("obj/armour");
      call_other(robe, "set_name", "robe");
      call_other(robe, "set_short","A grey robe");
      call_other(robe, "set_value",1000);
      call_other(robe, "set_weight",2);
      call_other(robe, "set_ac",1);
      call_other(robe, "set_type","cloak"); /* changed by Mats 901024 */
      move_object(robe,gatekeeper);
   }
   if(arg)
      return;
   short_desc = "Hellgate";
   long_desc = "You are at The Hellgate.\n" +
               "The gate stands black and sinister to the north.\n" +
               "This is the place where gods expel people they don't\n" +
               "want on earth.\n";
   dest_dir = ({ "players/kantele/hellgate_anteroom.c", "south" });
}

enter(str)
{
   if(str != "gate" && str != "hell" && str == "hellgate")
      return 0;
   if(!gate_is_open)
   {
      write("The gate is closed\n");
      return 1;
   }
   write("You get a tingeling feeling as you enter the gate.\n");
   call_other(this_player(), "move_player", "X#players/kantele/hell1");
   return 1;
}

open_gate(str)
{
   if(str && str =="gate")
   {
      if(call_other(this_player(), "query_str", 0) > 16)
 /*  Changed this to depend on str, not level.  /Gwendolyn  */
      {
         gate_is_open = 1;
         say(call_other(this_player(), "query_name") + " has opened the gate.\n");
         write("You have opened the gate.\n");
         return 1;
      }
      else
      {
         say(call_other(this_player(), "query_name") +
	     " tries to open the gate. but fails.\n");
         write("The power to open the gate don't belong to you.\n");
         return 1;
      }
   }
}

close_gate(str)
{
   if(str && str =="gate")
   {
      if(call_other(this_player(), "query_level", 0) > 20)
      {
         gate_is_open = 0;
         say(call_other(this_player(), "query_name") + " has closed the gate.\n");
         write("You have closed the gate.\n");
         return 1;
      }
      else
      {
         say(call_other(this_player(), "query_name") +
	     " tries to close the gate. but fails.\n");
         write("The power to open the gate don't belong to you.\n");
         return 1;
      }
   }
}
