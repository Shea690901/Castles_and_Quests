#define NAME "kantele"
#define DEST "room/plane5"
int manservant_dead, gate_open;
object manservant;

/*
 * This is just the facade to a castle. If you want to enable the
 * "enter" command, move the player to a hall or something (which
 * you have to design yourself).
 * The predefined string DEST is where a player should come when he
 * leaves the castle.
 *
 * This file is loaded automatically from "init_file". We have to move
 * ourself to where we are supposed to be.
 */

id(str) { return str == "mansion" || str == "sign" || str == "gate" ||
	         str == "gates"; }

short() { return "The Mansion of Kantele is to the south"; }

long(str)
{
   if(str == "sign")
   {
      write("\nBEWARE OF THE DOGS\n\n" +
            "SQUATTERS WILL BE EATEN !\n\n");
      return;
   }
   write("A large fence topped by barbed wire surrounds the house, the only\n");
   write("entrance is a huge iron gate leading into the garden. There is a\n");
   write("sign on the gate. You can also see a bell rope.\n");
}

init()
{
   add_action("enter", "south");
   add_action("pull_rope", "pull");
   add_action("try_open", "open");
}

pull_rope(str)
{
   if(str != "rope")
      return 0;
   else
   {
      if(gate_open == 1)
         write("Nothing happens...\n");
      else
      {
         gate_open = 1;
	 say(call_other(this_player(), "query_name") +
             " pulls the rope...\n");
         say("The gate opens !\n");
         say("Kanteles manservant arrives.\n");
         say("Kanteles manservant says: get lost punk !\n");
         write("The gate opens !\n");
         write("Kanteles manservant arrives.\n");
         write("Kanteles manservant says: get lost punk !\n");
	 if(!manservant || !living(manservant))
	    manservant = clone_object("players/kantele/manservant");
         move_object(manservant, environment(this_object()));
      }
      return 1;
   }
}

enter(str)
{
   if(manservant && environment(manservant) == environment(this_object()) &&
      this_player()->query_level() < 21)
   {
      write("Kanteles servant bars your way !\n");
   }
   else if(!gate_open)
      write("The gates are closed.\n");
   else
      this_player()->move_player("south#players/kantele/brick_road");
   return 1;
}

try_open(str)
{
   if(str != "gate" && str != "gates")
      return 0;
   write("Civilized people use the bell...\n");
   return 1;
}

reset(arg)
{
   object ob;			/* Pell */
   /* Move away the manservant, and close the gates. */
   if(manservant && living(manservant))
      call_other(manservant, "move_player", "X#players/kantele/castle");
   gate_open = 0;
   if(arg)
      return;
   move_object(this_object(), DEST);
   ob = clone_object("obj/quest_obj");
   call_other(ob, "set_name", "kantele");
   call_other(ob, "set_hint", "Loot Kantele's snake pit.\n");
   call_other(ob, "set_short", "Loot Kantele's snake pit");
   call_other(ob, "set_points", 50);
   move_object(ob, "room/quest_room");
}
