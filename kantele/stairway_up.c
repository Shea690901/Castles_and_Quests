inherit "room/room";

reset(arg)
{
   if(arg)
      return;
   short_desc = "You are on a landing in the stairway";
   long_desc = "You are on a landing in the stairway.\n" +
               "The stairway continues up and down and\n" +
               "you can also go north into the hall.\n" +
               "On the east wall you can see a large painting\n" +
               "of Kantele and her sister on a dragonhunt\n" +
               "they had on one of the outer planes.\n";
   dest_dir =
   ({
       "players/kantele/stairway", "down",
       "players/kantele/stairway_top", "up",
       "players/kantele/upper_hall", "north"
    });
   items =
   ({
        "painting", "The large painting covers the wall from ceiling to floor.\n" +
                    "It is fastened to the wall with some large nails and it looks\n" +
                    "almost impossible to get loose"
    });
}
