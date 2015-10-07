inherit "room/room";

reset(arg)
{
   if(arg)
      return;
   short_desc = "A dusty room, with a pentagram";
   long_desc = "A dusty room. You can see a small pentagram chalked up\n" +
               "in the dirt. You can exit west into the hall or\n" +
               "south into the training room\n";
   set_light(1);
   dest_dir =
   ({
       "players/kantele/training_room", "south",
       "players/kantele/upper_hall", "west"
    });
}
