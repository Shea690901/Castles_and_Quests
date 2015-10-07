inherit "room/room";

init(){
  add_action("get","get");
  add_action("get","take");
  add_action("pick", "pick");
  ::init();
}

reset(arg) {
  object scarecrow;

  if (!arg){
    set_light(1);
    short_desc = "In a cornfield";
    no_castle_flag = 0;
    long_desc = 
        "You are in a large cornfield.  It is full of corn.\n";
    dest_dir = 
        ({
        "players/angmar/fairyland/corn1", "south",
        });
    items = 
        ({
        "corn", "Ears and ears of it...waiting to be picked",
        "ears", "The corn is not yet ripe, so do not try to pick it",
        "cornfield", "Acres of corn, as far as you can see",
        });
  }

  if(!present("scarecrow")){
    object boots;
    scarecrow=clone_object("obj/monster");
    call_other(scarecrow,"set_name","scarecrow");
    call_other(scarecrow,"set_level",5);
    call_other(scarecrow,"set_hp",80);
    call_other(scarecrow,"set_wc",10);
    call_other(scarecrow,"set_short","A scarecrow");
    call_other(scarecrow,"set_long",
	       "He is seeing to that nobody steals the corn...\n");
    call_other(scarecrow,"set_al",-10);
    
    boots=clone_object("obj/armour");
    call_other(boots,"set_name","boots");
    call_other(boots,"set_short","A pair of rubber boots");
    call_other(boots,"set_alias","rubber boots");
    call_other(boots,"set_value",40);
    call_other(boots,"set_weight",1);
    call_other(boots,"set_ac",1);
    call_other(boots,"set_type","boot");
    move_object(boots,scarecrow);
    move_object(scarecrow,this_object());
  }
   
  if(!present("corncob"))
    move_object(clone_object("players/angmar/o/corncob"),this_object());
}
	      
get(str) {
  string who;
  if(!present("corncob") || (str!="corncob" && str!="cob" && str!="all") ||
     !present("scarecrow")) return 0;
  
  who=call_other(this_player(),"query_name",0);
  if(!who) who=" ";
  write("The scarecrow notices your attempt to\n"+
        "steal the corn and grabs your hand!\n");
  say("The scarecrow notices "+who+"'s attempt to\n"+
      "steal the corn and grabs his hand!\n");
  call_other(present("scarecrow"),"attacked_by",this_player());
  return 1;
}  


query_light() {
    return 1;
}

realm()
{
  return ("fairyland");
}

query_inorout() { return 2; }

pick(str){
  if (!str) return 0;
  if (str != "corn" && str != "ears") return 0;
  write("They are not yet ripe.\n");
  say(this_player()->query_name() + 
      " starts to pick corn, but realizes that it is not ripe yet.\n");
  return 1;
}
