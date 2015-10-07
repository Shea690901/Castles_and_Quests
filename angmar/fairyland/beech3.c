inherit "room/room";

reset(arg) {
object elfking, we;

  if (!arg){
    set_light(1);
    short_desc = "The beech woods";
    no_castle_flag = 0;
    long_desc = 
      "You are in the beech woods. The birds are singing.\n";
    
    dest_dir = 
        ({
        "players/angmar/fairyland/beech1", "north",
        });
    items = 
        ({
        "woods", "The woods consist of a huge number of beech trees",
        "trees", "Beech trees, which have been here for years",
        "beech trees", "Beech trees, which have been here for years",
	"birds", "They flit away before you can glimpse them",
        });
  }
if (!present("elfking")){
    elfking=clone_object("obj/monster");
    call_other(elfking,"set_name","elfking");
    call_other(elfking,"set_level",17);
    call_other(elfking,"set_hp",200);
    call_other(elfking,"set_wc",20);
    call_other(elfking,"set_ac",10); /* Guru: He surely need protection! */
    call_other(elfking,"set_short","The elfking");
    call_other(elfking,"set_alias","king");
    call_other(elfking,"set_al",200);
    call_other(elfking,"set_male",1); /* Guru: Kings usually are male */
    call_other(elfking,"set_long",
"This is the King of the Elves.  Though small in stature, he\n" +
"exudes a charisma and sense of capability that places you in awe.\n" +
"He is mature, by elf standards, yet you get the feeling that he is\n" +
"hundreds of years older than you are.  He has a determined look on his face.\n");
    we=clone_object("obj/weapon");
    call_other(we,"set_name","elfsword");
    call_other(we,"set_short","An elfsword");
    call_other(we,"set_long","It looks very sharp.\n");
    call_other(we,"set_alias","sword");	/* Guru: Nice with an alias */
    call_other(we,"set_class",17);
    call_other(we,"set_value",1500);
    call_other(we,"set_weight",4);
    move_object(we,elfking);
    move_object(elfking,this_object());
    command("wield sword", elfking); /* Guru: Wield sword! */
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
if (str == "trees" || str == "tree"){
write("The branches are too high for you to reach.\n");
say(this_player()->query_name() + " reaches for a few branches, but misses.\n");
return 1;
}
return 0;
}
listen(){
write("You hear the sounds of content birds.\n");
say(this_player()->query_name() + " listens to the birds.\n");
return 1;
}
