inherit "room/room";

reset(arg) {
  if (!arg){
    set_light(1);
    short_desc = "Crossing";
    no_castle_flag = 0;
    long_desc = 
        "The road crossing.  An old wooden sign-post points the ways to\n" +
	  "different areas.  The road to the north leads to Misty Mountain.\n" +
	    "The village is to the south.\n";
    dest_dir = 
        ({
        "players/angmar/fairyland/path1", "north",
        "players/angmar/fairyland/by_lake", "east",
        "players/angmar/fairyland/road3", "south",
        });
    items = 
        ({
        "road", "The road seems worn, as if many adventurers have travelled upon it",
        "sign-post", "The sign points east to Great Lake",
        "post", "It's old and weatherbeaten.  It looks like it will fall apart",
        "sign", "The sign points east to Great Lake",
        "lake", "Great Lake, off to the east.  You need to go closer to see it",
        "village", "The village lies off to the south",
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
  ::init();
}
