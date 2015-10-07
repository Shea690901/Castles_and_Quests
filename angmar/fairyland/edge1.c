inherit "room/room";

reset(arg) {
  if (!arg){
    set_light(1);
    short_desc = "Edge of the woods";
    no_castle_flag = 0;
    long_desc = 
        "You are at the edge of the beech woods. The birds are singing cheerfully.\n";
    dest_dir = 
        ({
        "players/angmar/fairyland/road1", "north",
        "players/angmar/fairyland/edge2", "west",
        "players/angmar/fairyland/beech1", "south",
        });
    items = 
        ({
"tree", "You see a prime candidate for climbing",
        "edge", "The road blends into the woods here",
        "woods", "Dozens of beech trees, flourishing in their environment",
        "beech trees", "Standing tall, their branches sway in the wind",
        "trees", "Standing tall, their branches sway in the wind",
        "branches", "None of them look stable enough to hold you",
        "birds", "The birdsong pierces the air, and adds to the atmosphere",
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
add_action("climb", "climb");
add_action("listen", "listen");
::init();
}

climb(str){
if (!str)
return 0;
if (str == "tree"){
write("You try your best, but you cannot climb the tree.\n");
say(this_player()->query_name() + " tries to climb a tree, but fails.\n");
return 1;
}
return 0;
}
listen(str){
if (!str)
return 0;
if (str == "song" || str == "bird song" ||
str == "birdsong" || str == "bird"){
write("You hear the song of a bird in its natural environment.\n");
say(this_player()->query_name() + " listens to the bird.\n");
return 1;
}
return 0;
}
