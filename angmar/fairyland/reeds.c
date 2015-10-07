inherit "room/room";

int boxhere;
int fishhere;

init(){
  add_action("Give", "give");
  ::init();
}

reset(arg) {
  if (!arg){
    set_light(1);
    short_desc = "In a clump of reeds";
    no_castle_flag = 0;
    long_desc = 
        "You trudge through the reeds, and find yourself in a small\n"
        + "fishing area.  Reeds and other water plants have been cleared\n"
        + "away to form a small spot to sit and fish, if you don't mind\n"
        + "getting your pants wet.\n";
    dest_dir = 
        ({
        "players/angmar/fairyland/by_lake", "west",
        });
    items = 
        ({
	  "plants", "All sorts of water plants, algae, and tubes grow here",
	  "reeds", "Small green tubes, growing from the bottom of the lake",
	  "bottom", "You search the bottom, but only find reed roots",
	  "lake", "The lake is tranquil and calm; the perfect place to fish",
        });
  }

  boxhere=1; fishhere=1;
  if(!present("elfboy", this_object())){
    object elfboy,rod;
    string chat_str;
    string a_chat_str;
    elfboy=clone_object("obj/monster");
    call_other(elfboy,"set_name","elfboy");
    call_other(elfboy,"set_level",1);
    call_other(elfboy,"set_hp",40);
    call_other(elfboy,"set_wc",3);
    call_other(elfboy,"set_ac",0);
    elfboy->set_male(); /* ### MUTARA: Made the elfBOY male */
    call_other(elfboy,"set_short","A fishing elfboy");
    call_other(elfboy,"set_alias","boy");
    call_other(elfboy,"set_al",300);
    call_other(elfboy,"set_long",
	       "The elfboy doesn't seem to notice you. He is concentrating\n"+
	       "hard on his fishing.\n");
    
    if(!a_chat_str) {
      a_chat_str=allocate(4);
      a_chat_str[0]=
	"Elfboy cries: Noo! Please, don't kill me!\n";
      a_chat_str[1]=
	"Elfboy says: Mummy! mummy! Help! Help!\n";
      a_chat_str[2]=
        "The boy is beating you furiously with his hands.\n";
      a_chat_str[3]=
        "Elfboy says: Waaaaahhh!\n";
      elfboy->load_a_chat(70,a_chat_str);
    }
    
    rod=clone_object("players/angmar/o/fishing_rod");
    move_object(rod,elfboy);
    
    move_object(elfboy,this_object());
  }
}

fish() {
  object box;
  if(boxhere) {
    box=clone_object("players/angmar/o/box");
    move_object(box,this_object());
    write("You got something!\n");
    boxhere=0;
    return 1;
  }
  
  if(fishhere) {
    move_object(clone_object("players/angmar/o/dead_fish"),this_object());
    write("You got something!\n");
    fishhere=0;
    return 1;
  }
  
  write("No luck today.\n");
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
     
Give(str){
  object boy,candy,rod;
  
  if (!str) return 0;
  if (str != "candy to elfboy" && str != "taffy to elfboy" &&
      str != "candy to boy" && str != "taffy to boy")
    return 0;
  else{
    candy = present("candy", this_player());
    if (!candy){
      write("You do not have any candy.\n");
      return 1;
    }
    boy = present("elfboy", this_object());
    if (!boy){
      write ("Give candy to whom?\n");
      return 1;
    }

    transfer(candy,environment(this_player()));
    destruct(candy);
    rod = present("rod", boy);
    transfer(rod,this_object());
    destruct(boy);
    say("The elfboy grins as " + this_player()->query_name() + 
	" gives him some candy.\n");
    write ("Candy: Ok.\n");
    write("The elfboy grins as you give him some candy.\n");
    say("Throwing caution to the wind and his fishing rod to the ground, he leaves.\n");
    return 1;
  }
}
