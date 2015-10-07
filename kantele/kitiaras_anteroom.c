inherit "room/room";

int door_is_open, door_is_locked;

reset(arg)
{
   door_is_open = 0;
   door_is_locked = 1;
   if(arg)
      return;
   short_desc = "You are in Kitiaras anteroom";
   long_desc = "You are in Kitiaras anteroom. A sturdy steel door leads west\n" +
               "and a passage east. There is a sign on the door.\n";
   set_light(0);
   dest_dir =
   ({
       "players/kantele/cellar_west", "east",
       "players/kantele/kitiaras_hall", "west"
    });
   items =
   ({
        "door", "A sturdy steel door",
        "sign", "There is something written on it"
    });
}

init()
{
   ::init();
   add_action("open", "open");
   add_action("unlock", "unlock");
   add_action("west", "west");
   add_action("read_sign", "read");
}

read_sign(str)
{
   if(str != "sign")
      return 0;
   write("The sign says: MORTALS SHOULD NOT ENTER! (on pain of death.)\n");
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
   if(!present("cellar key", this_player()))
   {
      if(present("key", this_player()))
      {
         write("The key doesn't fit.\n");
	 return 1;
      }
      write("You need a key.\n");
      return 1;
   }
   door_is_locked = 0;
   write("Ok.\n");
   say(call_other(this_player(), "query_name") + " unlocked the door.\n");
   return 1;
}

west()
{
   if(!door_is_open)
   {
      write("The door is closed.\n");
      return 1;
   }
}

query_door() { return !door_is_open; }

open_door_inside()
{
   door_is_locked = 0;
   door_is_open = 1;
}
