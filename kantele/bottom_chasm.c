inherit "room/room";

string rope;

reset(arg)
{
   if(!arg)
   {
      short_desc = "You are at the bottom of the chasm";
      set_light(1);
   }
   dest_dir =
   ({
       "/players/kantele/on_bridge", "up"
    });
}

long()
{
   write("You are at the bottom of the chasm. It seems impossible to get out !!\n");
   if(call_other("players/kantele/on_bridge", "query_rope"))
      write("There is a rope hanging down from the bridge.\n");
}

init()
{
   ::init();
   add_action("go_up", "up");
}

go_up() 
{
   if(!call_other("players/kantele/on_bridge", "query_rope"))
   {
      write("You can't go stright up with some kind of support.\n");
      return 1;
   }
}

tie(str)
{
   if(str != "pillar")
      return 0;
   rope = 1;
   return 1;
}

id(str)
{
   return str == "pillar";
}

untie(str)
{
   rope = 0;
   return 1;
}
