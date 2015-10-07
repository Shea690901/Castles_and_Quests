inherit "room/room";

reset(arg) {
  if (!arg){
    set_light(1);
    short_desc = "Corridor";
    no_castle_flag = 0;
    long_desc = 
        "You are in a corridor deep under the ancient castle.  The air\n"
        + "in here hasn't been breathed for hundreds of years.  You\n"
        + "cough and sneeze from the dust in the air.\n";
    dest_dir = 
        ({
        "players/angmar/castle/downstairs", "west",
        "players/angmar/castle/empty", "east",
        "players/angmar/castle/dungeons", "south",
        });
    items = 
        ({
        "corridor", "The corridor is lined with black flagstones",
        "flagstones", "The stones are just there as part of the wall supports",
        "supports", "They are behind the walls.  You cannot see them",
        "walls", "They seem sturdy and sound",
        "dust", "There is a thick layer of dust on the ground",
        "ground", "You see few footprints in the dust",
        "footprints", "You see your own, and a strange wave pattern",
        "pattern", "It looks like someone dragged a cloth lightly over the dust",
        });
  }
}

query_light() {
    return 1;
}

query_inorout() { return 1; }

init(){
add_action("smell", "smell");
::init();
}

smell(){
write("You sniff the air, but choke on the dust swirling around you.\n");
return 1;
}
