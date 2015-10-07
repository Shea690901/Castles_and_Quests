inherit "room/room";

reset(arg) {
  if (!arg){
    set_light(1);
    short_desc = "On a small road outside an inn";
    no_castle_flag = 0;
    long_desc = 
        "You are on a small road outside the Laughing Horse Inn.\n"
        + "Laughter and clinking from glasses can be heard from the east.\n"
        + "The road continues north and south.\n";
    dest_dir = 
        ({
        "players/angmar/fairyland/inn", "east",
        "players/angmar/fairyland/road1", "south",
        "players/angmar/fairyland/road3", "north",
        });
    items = 
        ({
        "road", "The road seems wellworn.  As it should, seeing as how it is the main road",
        "inn", "You can see people laughing and drinking inside",
        "east", "To the east, you see the Laughing Horse Inn",
        "laughter", "It sounds like someone is BLASTED in there",
        "clinking", "Cheers!  Stop listening, and join them",
        });
  }
}

query_light() {
    return 1;
}

realm()
{
  return ("fairyland");
}

query_inorout() { return 2; }

init(){
add_action("listen", "listen");
::init();
}

listen(){
   write ("You hear the sounds of a bar in full swing coming from the east.\n");
say(this_player()->query_name() + " listens to the sounds issuing from the inn.\n");
return 1;
}
