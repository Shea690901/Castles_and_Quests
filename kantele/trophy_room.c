inherit "room/room";

reset(arg)
{
   if(arg)
      return;
   short_desc = "Kantele's trophy room";
   long_desc = "This is the room where Kantele places some of her trophies.\n" +
               "On a table in the center of the room, you can see a human head!\n" +
               "On the north wall you can see the head of the 'Great Wyrm' the\n" +
               "famous Gold Dragon Kantele slayed on her 18'th birtday.\n" +
               "To the north you can see the bar and to the south there is some\n" +
               "sort of workroom.\n";
   dest_dir =
   ({
       "players/kantele/bar", "north",
       "players/kantele/office", "south"
    });
   items =
   ({
        "head", "This is the head of 'Alf the black knight'.\n" +
                "It is in premium condition and exactly as when Kantele slayed\n" +
                "him. Heads is items Kantele likes, so it is not possible to\n" +
                "steal, even if you would like to.."
    });
}
