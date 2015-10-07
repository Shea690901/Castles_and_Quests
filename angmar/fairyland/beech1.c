inherit "room/room";

reset(arg) {
object elves;
int i;
  object elf,we;

  if (!arg){
    set_light(1);
    short_desc = "The beech woods";
    no_castle_flag = 0;
    long_desc = 
        "You are in the beech woods.  The sun is shining through the foliage.\n";
    dest_dir = 
        ({
        "players/angmar/fairyland/beech2", "west",
        "players/angmar/fairyland/beech3", "south",
        "players/angmar/fairyland/edge1", "north",
        });
    items = 
        ({
        "woods", "The woods consist of a huge number of beech trees",
        "trees", "Beech trees, which have been here for years",
        "beech trees", "Beech trees, which have been here for years",
        "sun", "The sun, rising over Mizar, peeks through the foliage",
        "foliage", "The branches of the beech trees mesh together",
        "branches", "They look too high to climb",
        });
  }
if (!present("elf")){
elf = clone_object("players/angmar/castle/elf");
    we=clone_object("obj/weapon");
    we->set_name("Big knife");
    we->set_short("Big knife");	/* Added by Tanzi */
    we->set_class(9);
elf->set_male();
    we->set_value(25);
    we->set_weight(1);
    we->set_alias(({"knife", "big knife"}));
    move_object(we,elf);
    move_object(elf,this_object());

elf = clone_object("players/angmar/castle/elf");
    move_object(elf,this_object());
    we=clone_object("obj/weapon");
elf->set_male();
    we->set_name("Small sword");
    we->set_class(11);
    we->set_value(40);
    we->set_weight(2);
    we->set_alias(({"sword", "small sword"}));    
    we->set_short("Small sword");
    move_object(we,elf);
    move_object(elf,this_object());
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
if (!str)
return 0;
if (str == "tree" || str == "trees"){
write ("The branches are all too high for you to reach.\n");
say(this_player()->query_name() + " tries to reach for a few branches.\n");
return 1;
}
return 0;
}
