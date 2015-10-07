inherit "room/room";

reset(arg)
{
   if(arg)
      return;
   short_desc = "In a strange room";
   long_desc = "You are in a strange room.It is small and totaly without\n" +
               "furniture of any kind. It looks like some kind of meditation \n" +
               "room. A large blackboard stands against the north wall.\n";
   dest_dir = ({ "players/kantele/kitiaras_livingroom", "east" });
   items =
   ({
        "blackboard", "There is a message on the blackboard. It says:\n" +
                      "Dear Kit !\n\nCan you visit me tomorrow?\n" +
                      "And bring my gift unless you want to visit my pets!!!\n\n" +
                      "          /K\n"
    });
}
