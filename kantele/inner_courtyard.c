inherit "room/room";

int door_is_open, door_is_locked;
object guard;

reset(arg)
{
   door_is_open = 0;
   door_is_locked = 1;
   if(arg)
      return;
   items = ({ "door", "Just a door" });
   short_desc = "The inner courtyard";
   long_desc = "You are in the inner courtyard, it opens up to the north \n" +
               "and a door leads south. There is a sign on the door.\n ";
   set_light(1);
   dest_dir = ({"players/kantele/courtyard", "north"});
   items = ({ "sign", "There is something written on it" });
}

init()
{
   ::init();
   add_action("open", "open");
   add_action("unlock", "unlock");
   add_action("south", "south");
   add_action("read_sign", "read");
}

read_sign(str)
{
   if(str != "sign")
      return 0;
   write("The sign says: Kantele lives here. Beware!\n");
   return 1;
}

open(str)
{
   if(str != "door")
      return 0;
   if(door_is_open)
   {
      write("The door is already open.\n");
      return 1;
   }
   if(door_is_locked)
   {
      write("The door is locked.\n");
      return 1;
   }
   door_is_open = 1;
   write("Ok.\n");
   say(call_other(this_player(), "query_name") + " opened the door.\n");
   return 1;
}

unlock(str)
{
   if(str != "door")
      return 0;
   if(door_is_open || !door_is_locked)
   {
      write("The door isn't locked.\n");
      if(door_is_open)
         write("It's even open.\n");
      return 1;
   }
   if(!present("mansion key", this_player()))
   {
      if(present("key", this_player()))
         write("The key doesn't fit.\n");
      else
         write("You need a key.\n");
      return 1;
   }
   door_is_locked = 0;
   write("Ok.\n");
   say(call_other(this_player(), "query_name") + " unlocked the door.\n");
   return 1;
}

south()
{
   if(!door_is_open)
   {
      write("The door is closed.\n");
      return 1;
   }
   call_other(this_player(), "move_player", "south#players/kantele/hall");
   return 1;
}

query_door() { return !door_is_open; }

open_door_inside()
{
   door_is_locked = 0;
   door_is_open = 1;
}
