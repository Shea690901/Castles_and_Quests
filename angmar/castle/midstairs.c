inherit "room/room";

reset(arg) {
  if (!arg){
    set_light(1);
    short_desc = "Between the staircases";
    no_castle_flag = 0;
    long_desc = 
"You are between two long staircases going up and down.  Torches on the\n" +
"walls light up the passage.  You wonder who keeps the torches lit.  The\n" +
"atmosphere somehow seems to become more threatening further down.\n";

    dest_dir = 
        ({
        "players/angmar/castle/stairs", "up",
        "players/angmar/castle/downstairs", "down",
        "players/angmar/castle/magroom", "west",
        "players/angmar/castle/treasury_entrance", "north",
        });
    items = 
        ({
"staircases", "They wind their way into the castle, above and below you",
"staircase", "It winds its way into the castle, above and below you",
        "torches", "They glow with a magical light.  They seem not to need fuel",
        "sign", "The sign points west, and says, 'Fairyland'",
        "*", "**",
        });
  }
}

query_light() {
    return 1;
}

query_inorout() { return 1; }

