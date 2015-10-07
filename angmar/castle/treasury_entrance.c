object listener;
object thief;
int trig,trig2;
string plrnam;

reset(arg) {
  if(!arg) set_light(1);

    trig=0;

    if((!thief || !living(thief)) && 
       call_other("players/angmar/castle/treasury","query_door",0)) {
    object stiletto;
    thief=clone_object("obj/monster");
    call_other(thief,"set_name","thief");
    call_other(thief,"set_level",14);
    call_other(thief,"set_hp",200);
    call_other(thief,"set_wc",13);
    call_other(thief,"set_ac",6); /* Guru: More protection */
    call_other(thief,"set_short","A suspicious looking thief");
    thief->set_male(); /* ### MUTARA: Set the thief to be male. */
    call_other(thief,"set_long",
      "He seems to be doing something with the doors.\n");

    /* Guru: Changing to use monster.c instead of obsolete monster.talk */
#if 0
    call_other(thief,"set_a_chat_chance",50);
    call_other(thief,"load_a_chat",
      "Noo! I got here first!\n");
    call_other(thief,"load_a_chat",
      "Get lost! This is my treasure!\n");
    call_other(thief,"load_a_chat",
      "It's mine it's mine it's mine!\n");
#endif

    thief->load_a_chat(50, ({ "Thief says: Noo! I got here first!\n",
			    "Thief says: Get lost! This is my treasure!\n",
			    "Thief says: It's mine it's mine it's mine!\n" }));

    stiletto=clone_object("obj/weapon");
    call_other(stiletto,"set_name","stiletto");
    call_other(stiletto,"set_short","A stiletto");
    call_other(stiletto,"set_long","Ouch! Looks nasty!\n");
    call_other(stiletto,"set_class",13);
    call_other(stiletto,"set_weight",1);
    call_other(stiletto,"set_value",700);
    move_object(stiletto,thief);
    move_object(thief,"players/angmar/castle/treasury_entrance");
    command("wield stiletto", thief); /* Guru: Make him nastier */
  }
}
init() {
  add_action("open"); add_verb("open");
  add_action("close"); add_verb("close");
  add_action("open"); add_verb("open");
  add_action("south"); add_verb("south");
  add_action("north"); add_verb("north");
  if(got_rings()) activate();
}

got_rings() {
  object tplr;
  tplr=this_player();
   return (present("trlock1",tplr) && present("trlock2",tplr) &&
           present("trlock3",tplr));
}

activate() {
  set_heart_beat(1);
  trig=3;
  plrnam=call_other(this_player(),"query_name",0);
  if(!listener || !living(listener)) {
    listener=clone_object("players/angmar/o/catch_password.c");
    call_other(listener,"set_room","players/angmar/castle/treasury");
    call_other(listener,"set_call","catch_it");
    move_object(listener,this_object());
  }
}

password_ok() {  /* called from treasury */
  object tplr;
  object ring1,ring2,ring3;

  trig=0;trig2=0;

  tplr=this_player();
  
  /* destruct rings */
  ring1=present("trlock1",tplr);
  ring2=present("trlock2",tplr);
  ring3=present("trlock3",tplr);
  if(ring1 && ring2 && ring3) {
    destruct(ring1);
    destruct(ring2);
    destruct(ring3);
    write("Your rings begin to glow even brighter, and then they disappear!\n");
    say(call_other(tplr,"query_name",0));
    say("'s rings disappear.\n");
   }
}

doors_open() {
  tell_room(this_object(),
     "The doors to the treasury slams shut with a deafening boom!\n");
}

heart_beat() {
  if(trig>0) {
    trig-=1;
    if(trig==0) {
      say(plrnam);
      say("'s rings begin to glow!\n");
      say("Suddenly a face seems to materialize deep within the doors.\n");
      say("The face whispers: 'Do you have the password?'\n");
      trig2=15;
    }
  }
  
  if(trig2>0) {
    trig2-=1;
    if(trig2==0) {
      say("The face fades away. Your rings no longer glow.\n");
      set_heart_beat(0);
    }
  }

}

short() { return "The entrance to Angmar's treasury"; }  

long(str) {
  if(str=="door" || str=="doors" || str == "huge iron doors" ||
str == "twin doors" || str == "giant doors" || str == "giant twin doors" ||
     str == "iron doors" || str == "huge doors") {
    if(!call_other("players/angmar/castle/treasury","query_door",0))
        write("The doors to the treasury are open.\n");
    else
        write("You see reliefs of three rings on the huge iron doors.\n");
        write("The doors are closed.\n");
    return 1;
  }

  if(call_other("players/angmar/castle/treasury","query_door",0)) {
    write("This is the entrance to Angmar's treasury. Many are the tales\n");
    write("about his hidden treasures. So far, nobody has been able to\n");
    write("enter. Maybe you will be the first one?\n");
    write("There are two giant twin doors to the north.\n");
    write("The only obvious exit is to the south.\n");
    }
  else {
    write("This is the entrance to Angmar's treasury. The doors\n");
    write("are open.\n");
  }
}
id(str) {
  return str=="door" || str=="doors";
}

south() {
  call_other(this_player(),"move_player","south#players/angmar/castle/midstairs");
  return 1;
}

open(str) {
  string nam;
  nam=call_other(this_player(),"query_name",0);
  if(str!="door"&&str!="doors") return 0;
  write("A blue flash strikes out and hits you as you reach for\n");
  this_player()->reduce_hit_point(5); /* ### MUTARA: Foolish players.
					 Beware of traps. :) */
  write("the doors. You gasp in pain.\n");
  say(nam);
  say(" is hit by a blue flash as he reaches for the doors.\n");
  say(nam+" gasps in pain.\n");
  return 1;
}

close(str) {
  if(str!="door"&&str!="doors") return 0;
  call_other("players/angmar/castle/treasury","close_door","door");
  return 1;
}

north() {
  if(call_other("players/angmar/castle/treasury","query_door",0)) {
    write("The iron doors are closed.\n");
    return 1;
  }
  call_other(this_player(),"move_player","north#players/angmar/castle/treasury");
  return 1;
}
