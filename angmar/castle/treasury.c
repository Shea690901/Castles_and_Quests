status door_is_open;
int rescount;
string password;

realm(){ return "NT";}

reset(arg) {
  object chainmail,obj,mon;
  if(!arg) set_light(1);
  throw_out(); /* We don't want it robbed twice, do we? */
  door_is_open=0;
  call_other("players/angmar/castle/treasury_entrance","doors_open",0);
  if(rescount==0) new_password();
  set_heart_beat(1);  /* just to be sure */

  mon=present("money");

  if(!present("chainmail")) {
    chainmail=clone_object("obj/armour");
    call_other(chainmail,"set_name","chainmail");
    call_other(chainmail,"set_short","heavy chainmail");
    call_other(chainmail,"set_long",
	       "This chainmail looks rusty, and must be very old.\n"+
	       "There are a few darkened splotches of blood here and there,\n" +
	       "but it looks like a formidable piece of armour.\n");
    call_other(chainmail,"set_alias","heavy chainmail");
    call_other(chainmail,"set_value",1000);
    call_other(chainmail,"set_weight",7);
    call_other(chainmail,"set_ac",3);/* 4 Guru: Too much good armour already */
    call_other(chainmail,"set_type","armour");
    move_object(chainmail,this_object());
  }

  if(!present("sapphire")) {
    obj=clone_object("obj/treasure");
    call_other(obj,"set_id","sapphire");
    call_other(obj,"set_short","A sapphire");
    obj->set_long("The facets of the sapphire shimmer and glint in the light.\n"+
		  "You examine it closely, and notice the workmanship inherent in the gem.\n"+
		  "This is a fine stone, indeed.\n");
    call_other(obj,"set_value",200); /* 400 Guru: Just a bit less value.. */
    move_object(obj,this_object());
  }

  if(!mon) {
    obj=clone_object("obj/money");
    call_other(obj,"set_money",12);
    move_object(obj,this_object());
}

  if(!mon) {
    obj=clone_object("obj/money");
    call_other(obj,"set_money",312);
    move_object(obj,this_object());
  }
  
  if(!present("crown")) {
    obj=clone_object("obj/treasure");
    call_other(obj,"set_id","crown");
    call_other(obj,"set_short","A golden crown");
    obj->set_long("At first glance, this crown seems to be a crude adornment for a long-dead\n" +
		  "monarch.  On closer inspection, however, you notice a small gem pattern\n" +
		  "that renders this crown to be of high value.\n");
    call_other(obj,"set_value",400); /* 800 Guru: Less.. */
    move_object(obj,this_object());
}

if(!present("diamond")) {
  obj=clone_object("obj/treasure");
  call_other(obj,"set_id","diamond");
  call_other(obj,"set_short","A diamond");
  obj->set_long("This diamond is much larger than others you have seen in the world.\n" +
		"You cannot estimate the number of carats on this rock, but what you\n" +
		"do know about gems hints that this diamond may be worth a lot.\n");
  call_other(obj,"set_value",300); /* 600 Guru: Less... */
  move_object(obj,this_object());
}


  if(!present("spear")) {
    obj = clone_object("obj/weapon");
    call_other(obj,"set_name", "spear");
    call_other(obj,"set_short","A heavy spear");
    obj->set_long("It's about six feet long, with a metal head inserted into the tip.\n" +
		  "Some type of coarse cord is wrapped around the tip to hold the point in\n" +
		  "the spear.  You notice that the middle section of the spear seems worn,\n" +
		  "as if it were used in many battles.\n");
    
    call_other(obj,"set_class",14);
    call_other(obj,"set_weight",4);
    call_other(obj,"set_value",400); /* 800 Guru: Less.. */
    move_object(obj,this_object());
  }
  
  if(!present("sword")) {
    obj = clone_object("obj/weapon");
    call_other(obj,"set_name", "sword");
    call_other(obj,"set_short","An ancient sword");
    call_other(obj,"set_long",
	       "This sword has the nicks and scrapes of a well-used blade.  Although the\n"+
	       "hilt has been replaced several times, the blade is as keen and sharp\n" +
	       "as they day it was first ready for battle.\n");
    call_other(obj,"set_class",17); /* 20 Guru: Too many good weapons.. */
    call_other(obj,"set_weight",5);
    call_other(obj,"set_value",2100);
    move_object(obj,this_object());
  }
  
  /*  no, that was too generous...   :)
      if(!present("doomsgiver")) {
      obj=clone_object("players/angmar/o/doomsgiver");
      move_object(obj,this_object());
      }
      */

  if(!mon) {
    obj=clone_object("obj/money");
    call_other(obj,"set_money",125);
    move_object(obj,this_object());
  }
}

throw_out() {
  object ob, next_ob;
  ob=first_inventory(this_object());
  while(ob) {
    next_ob=next_inventory(ob);
    if(living(ob)) {
      move_object(ob,"players/angmar/castle/treasury_entrance");
      tell_object(ob,"You feel dizzy for a moment. Where are you?\n");
    }
    ob=next_ob;
  }
}

catch_it(str) {
  string a,b;
  if((sscanf(str,"%s"+password+"%s",a,b) == 2) && got_rings()) {
    call_other("players/angmar/castle/treasury_entrance","password_ok",0);
    write("The giant doors slowly and soundlessly swing open!\n");
    write("Angmar's treasury lies open in front of you!\n");
    say("The giant doors slowly and soundlessly swing open!\n");
    say("Angmar's treasury lies open in front of you!\n");
    door_is_open=1;
/*    call_other(this_player(),"set_quest","angmar"); */
/*    write("Your quest is completed!\n"); */
  }
}

got_rings() {
  object tplr;
  tplr=this_player();
   return (present("trlock1",tplr) && present("trlock2",tplr) &&
           present("trlock3",tplr));
}

new_password() {
  int x;
  x=random(6);
  if(x==0) password="tarantor";
  if(x==1) password="hashnuk";
  if(x==2) password="gothnir";
  if(x==3) password="hurfurin";
  if(x==4) password="alannen";
  if(x==5) password="rhastul";
  x=random(6);
  if(x==0) password=password+" osibilum";
  if(x==1) password=password+" shiryllis";
  if(x==2) password=password+" fornor";
  if(x==3) password=password+" es";
  if(x==4) password=password+" eth";
  if(x==5) password=password+" sureth";
  x=random(6);
  if(x==0) password=password+" brupp";
  if(x==1) password=password+" hades";
  if(x==2) password=password+" grukk";
  if(x==3) password=password+" elte";
  if(x==4) password=password+" connon";
  if(x==5) password=password+" benambra";
}

query_password() { /* called from oracle */
  return password;
}

prevent_reset() {  /* called from oracle */
  rescount=200;
  set_heart_beat(1);
}

heart_beat() {
  if(rescount>0) rescount-=1;
}

query_rescount() {  /* for debugging only */
  return rescount;
}

query_door() { return !door_is_open; }
init() {
  add_action("open_door"); add_verb("open");
  add_action("close_door"); add_verb("close");
  add_action("south"); add_verb("south");
}

short() {
  return "The treasury";
}

long(str) {
  if(str=="door" || str=="doors") {
    if(door_is_open)
        write("The doors are open.\n");
    else
        write("The doors are closed.\n");
    return 1;
  }
  write("You are inside Angmar's treasury.\n");
  write("The only obvious exit is to the south.\n");
}
id(str) { return str=="door" || str=="doors"; }

south() {
  if(!door_is_open) {
    write("The doors are closed.\n");
    return 1;
  }
  call_other(this_player(),"move_player",
        "south#players/angmar/castle/treasury_entrance");
  return 1;
}

open_door(str) {
  if(str!="door" && str!="doors") return 0;
  if(door_is_open) { 
    write("The doors are already open!\n");
    return 1;
  }
  door_is_open=1;
  write("You barely need to touch the doors. They seem to swing\n");
  write("wide open by some unvisible force.\n");
  say(call_other(this_player(),"query_name",0)+" opened the doors.\n");
  return 1;
}

close_door(str) {
  if(str!="door" && str!="doors") return 0;
  if(!door_is_open) { 
    write("They are already closed!\n");
    return 1;
  }
  write("The doors are too heavy. You can't move them.\n");
  return 1;
}
