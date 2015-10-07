inherit "room/room";

reset(arg) {
  object sign;

  if (!arg){
    set_light(1);
    short_desc = "The entrance to Darkwood";
    no_castle_flag = 0;
    long_desc = 
        "You are standing in front of the entrance to Darkwood.\n"
        + "You cannot see further than a few metres of the path\n"
        + "that is trailing into the forest.\n";
    dest_dir = 
        ({
        "players/angmar/fairyland/path1", "west",
        });
    items = 
        ({
        "darkwood", "A dark and menacing forest.  You don't want to enter it",
        "forest", "The trees themselves seem dark.  Evil emanates from the heart of the forest",
        "trees", "No longer are they healthy trees.  The dark has claimed them",
        "dark", "You cannot examine such an evil presence",
        "entrance", "The road blends into the wood, and disappears from view",
        "road", "It leads to the forest, but you cannot see further",
        "path", "It leads to the forest, but you cannot see further",
        });
  }
  if (!present("sign", this_object())){
    sign = clone_object("obj/treasure");
    sign->set_id("sign");
sign->set_short("A small sign");
    sign->set_long("It seems to have been here for quite a while.\n");
    sign->set_weight(50);
    sign->set_read("The road is closed due to the many accidents\n" +
		   "caused by the creatures in the forest.\n");
    sign->set_value(1);
    move_object(sign, this_object());
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
::init();
}

climb(str){
if (!str) return 0;
if (str != "trees" && str != "tree"){
return 0;
}
write ("You shiver involuntarily as you approach the tree.  You dare not try to climb.\n");
say (this_player()->query_name() + " approaches a tree, but backs off.\n");
return 1;
}
