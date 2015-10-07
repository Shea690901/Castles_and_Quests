inherit "room/room";

reset(arg) {

  object creature;
  object gutripper,master,creat,workroom;

  if (!arg){
    set_light(1);
    short_desc = "Angmar's castle";
    no_castle_flag = 0;
long_desc =
"You are inside the gates of Angmar the Necromancer's castle.\n" +
"The castle was abandoned a long time ago when Angmar was driven\n" +
"from this world by the Istari, and is now quite ruined.  Angmar's\n" +
"workroom is to the east.  You can see a forge to the west.\n";
dest_dir =
        ({
        "room/plane11", "north",
        "players/angmar/castle/stairs", "south",
        "players/angmar/castle/forge", "west",
        });
    items = 
        ({
        "gates", "The gates are covered with rust, since they have not been used in ages",
        "rust", "The rust on the gates is thinck.  The metal has oxidized over the years",
        "castle", "The castle looms over you.  You shiver as you think of the death inside",
        "workroom", "The portal is shadowy.  You see a few blurs inside",
        "portal", "The portal consists of a dark oval.  You cannot see within",
        "oval", "The oval is a two-dimensional object.  You are always facing it",
        "blurs", "You cannot distinguish anything about the blurs",
        "forge", "In the forge, you see a smith, sitting quietly",
        "smith", "You can't make out any details about him",
        "sign", "The sign points south, and says, 'This way to Fairyland'",
        "south", "The way south is in darkness.  You cannot see",
        });
  }

  workroom=find_object("players/angmar/workroom");
  if(workroom) master=present("master-palantir",workroom);
  if(!master || !workroom) {
    master=clone_object("players/angmar/o/master");
    move_object(master,"players/angmar/workroom");
  }
  if(!present("creator",this_object())){
    creat=clone_object("players/angmar/o/creator");
    creat->set_master(master);
    move_object(creat,this_object());
  }

  if (!present("creature", this_object())){

    creature = clone_object("obj/monster");
    gutripper = clone_object("obj/weapon");
    
    call_other(gutripper, "set_name", "gutripper");
    call_other(gutripper, "set_alias", "ripper");
    call_other(gutripper, "set_short", "Gutripper");
    call_other(gutripper, "set_long", "You can only guess what devishly " +
	       "deeds this nasty tool was used for.\nIt should serve very well " +
	       "as a weapon though.\n");
    call_other(gutripper, "set_class", 15);
    call_other(gutripper, "set_weight", 2);
    call_other(gutripper, "set_value", 1000);
    
    call_other(creature, "set_name", "creature");
    call_other(creature, "set_level", 15);
    call_other(creature, "set_hp", 200);
    call_other(creature, "set_wc", 10);
    call_other(creature, "set_ac", 5);
    call_other(creature, "set_al", -150);
    call_other(creature, "set_short", "A loathesome creature");
    call_other(creature, "set_long" ,"A disgusting malformed thing," +
	       " who perhaps was a human once.\n" +
	       "Angmar was probably in a " +
	       "bad mood when he created \nthis indescribable being. " +
	       "Take care!\n");
    
    call_other(creature, "set_aggressive", 0);
    call_other(creature, "set_spell_mess1"
	       , "The creature casts a spell");
    call_other(creature, "set_spell_mess2",
	       "The creature casts a spell at you");
    call_other(creature, "set_chance", 30);
    call_other(creature, "set_spell_dam",20);
    move_object(creature, this_object());
    move_object(gutripper,creature);
    call_other(creature,"init_command","wield gutripper");
  }
}

query_light() {
    return 1;
}

query_inorout() { return 2; }

init(){
  ::init();
    add_action("east","east");
    if(this_player()->query_name()=="Cow") {
      move_object(this_player(),"room/void");
    }
  }




east(){
  if (call_other (this_player(), "query_real_name",0)!="angmar" &&
      this_player()->query_real_name() != "mutara") { 
    /* ### MUTARA: Gotta have SOME priviledges. */
    write("You start to shiver. You dare not enter.\n");
    say(call_other(this_player(), "query_name",0) +
	" tried to enter the workroom.\n");
    return 1; }
  
  write("You enter Angmar's monsterlab\n");
  call_other(this_player(), "move_player", "east#players/angmar/workroom");
  return 1;
}
