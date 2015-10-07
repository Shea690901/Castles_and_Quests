inherit "room/room";

reset(arg) {

  object oracle;

  if (!arg){
    set_light(1);
    short_desc = "On a rock ledge";
    no_castle_flag = 0;
    long_desc = 
        "You step onto a small rock ledge on Misty Mountain.\n"
        + "Judging by the bits and pieces of a burned out fire here,\n"
        + "it seems that someone has been living on the ledge.\n";
    dest_dir = 
        ({
        "players/angmar/fairyland/mountain", "west",
        });
    items = 
        ({
"mountain", "The mountain has formed a natural ledge here",
"misty mountain", "The mountain has formed a natural ledge here",

        "pieces", "There are a few ashes around a chunk of charred wood",
        "bits", "There are a few ashes around a chunk of charred wood",
        "ashes", "You feel them, and they seem to be relatively recent",
        "wood", "Strangely enough, the wood seems hardly burned.  Magic, perhaps..",
        "ledge", "The ledge seems very dangerous.  Try not to fall off",
        "fire", "There are a few ashes around a chunk of charred wood",
        });
  }
  if (!present("oracle", this_object())){
    oracle = clone_object("players/angmar/o/oracle");
    oracle->set_name("oracle");
    move_object(oracle, this_object());
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
add_action("search", "search");
::init();
}

search(str){
if (!str) return 0;
if (str != "ashes") return 0;
write ("You dig through the ashes, but find nothing.\n");
say(this_player()->query_name() + " searches through the ashes, but finds nothing.\n");
return 1;
}
