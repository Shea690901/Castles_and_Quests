inherit "room/room";

reset(arg) {
  if (!arg){
    set_light(1);
    short_desc = "In a cornfield";
    no_castle_flag = 0;
    long_desc = 
        "You are in a large cornfield.  Corn grows everywhere.\n";
    dest_dir = 
        ({
        "players/angmar/fairyland/corn2", "north",
        "players/angmar/fairyland/ditch", "east",
        });
    items = 
        ({
        "cornfield", "The field stretches on for acres",
        "corn", "It must be a bumper crop this year.  There are ears everywhere",
        "ears", "Ears of corn.  But they are not ripe yet, so don't try to pick them",
        "corn", "It must be a bumper crop this year.  There are ears everywhere",
        "crop", "This huge expanse of corn should make the farmer very happy",
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

