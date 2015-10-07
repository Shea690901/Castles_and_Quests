inherit "room/room";

reset(arg) {
  object mushroom;

  if (!arg){
    set_light(1);
    short_desc = "The beech woods";
    no_castle_flag = 0;
    long_desc = 
      "You are in the beech woods. The air feels warm, and the birds are\n"+
	"singing. You feel very happy.\n";
    dest_dir = 
        ({
        "players/angmar/fairyland/beech1","east",
	"players/angmar/fairyland/edge2","north",
        });
    items = 
        ({
        "woods", "The woods consist of a huge number of beech trees",
        "trees", "Beech trees, which have been here for years",
        "beech trees", "Beech trees, which have been here for years",
        "birds", "All types and varieties, singing and flying around",
	"air", "The sun has warmed up the area",
        });
  }

if (!present("slimy mushroom")){
    mushroom=clone_object("obj/treasure");
    call_other(mushroom,"set_name","mushroom");
    call_other(mushroom,"set_short","A slimy mushroom");
    call_other(mushroom,"set_long","Yuck! Disgusting!\n");
    call_other(mushroom,"set_value",5);
    call_other(mushroom,"set_alias","slimy mushroom");
    move_object(mushroom,this_object());
  }
if (!present("elf")){
    object elf,we;
    elf=clone_object("players/angmar/castle/elf");
    we=clone_object("obj/weapon");
elf->set_male();
    call_other(we,"set_name","knife");
we->set_short("Big knife");
    call_other(we,"set_class",9);
    call_other(we,"set_value",25);
    call_other(we,"set_weight",1);
    move_object(we,elf);
    move_object(elf,this_object());

elf = clone_object("players/angmar/castle/elf");
elf = clone_object("players/angmar/castle/elf");
    move_object(elf,this_object());
    we=clone_object("obj/weapon");
    call_other(we,"set_name","sword");
we->set_short("Small sword");
    call_other(we,"set_class",11);
elf->set_male();
    call_other(we,"set_value",40);
    call_other(we,"set_weight",2);
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
add_action("listen", "listen");
::init();
}

climb(str){
if (!str)
return 0;
if (str == "tree" || str == "trees"){
write ("You try, but cannot reach the branches of the beech tree.\n");
say (this_player()->query_name() + " tries, but cannot reach the branches.\n");
return 1;
}
return 0;
}

listen(str){
if (!str) 
return 0;
if (str == "birds" || str == "to birds" || str == "birdsong"){
write ("The birds sound happy to be here.\n");
say(this_player()->query_name() + " listens to the birds.\n");
return 1;
}
return 0;
}
