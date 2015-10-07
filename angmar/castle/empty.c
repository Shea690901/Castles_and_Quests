#include "std.h"

int stat;
status angry;
object spirit;
object intruder;
object doomsgiver;

reset(arg) {
if (!arg) set_light(1);
if (!spirit || !living(spirit)) {
     create_spirit();
     stat=1;
}
}

init() {
  add_action("west");add_verb("west");
  if (any_here()) set_heart_beat(1);
}

west() {
  call_other (this_player(),"move_player","west#players/angmar/castle/corridor");
  return 1;
}

short() {
  return "Empty room";
}

long() {
  write("You are in a totally empty room. You feel the presence of\n"+
        "a magic force here...\n");
  write("    The only obvious exit is west\n");
}

any_here() {
  object ob;
  ob = first_inventory(this_object());
  while(ob) {
     if (ob != this_object() && living(ob) &&
	 !call_other(ob,"query_npc")) {
	 intruder = ob;
	 return 1;
     }
     ob = next_inventory(ob);
 }
  intruder = 0;
   return 0;
}

heart_beat() {
   string str1,str2,str3,str4,str5;

   if(!spirit || !living(spirit)) { stat=20; return; }
   if(spirit && call_other(spirit,"query_attack",0)) angry=1;

   if(!any_here()) {
      set_heart_beat(0);
      if( !angry && (stat>=12) && (stat<17) ) {
                     if(doomsgiver) destruct(doomsgiver);
                     destruct(spirit);
                     create_spirit();
                     stat=1;
                     return;
                   }
      if(stat<12) { stat = 1; return; }
      stat = 12;
      return;
   }

   if(stat>=17) return;


   str1 = "You get an uneasy feeling...\n";
   str2 = "Something is very wrong in here. Your brain is screaming\n"+
          "to you to get out of here immediately!\n";
   str3 = "A shimmering light slowly appears in front of you.\n";
   str4 = "A half transparent luminous spirit hovers in the air.\n";
   str5 = "The spirit begins to wail in a hair-raising voice.\n";

   stat+=1;
   if(stat==4) { say(str1); write(str1); }
   if(stat==7) { say(str2); write(str2); }
   if(stat==10) { say(str3); write(str3); }
   if(stat==12) { move_object(spirit,this_object());
                  say(str4); write(str4);
                }
   if(stat==14) { say(str5); write(str5); }
   if(stat==17) {
       call_other(spirit,"attacked_by",intruder);
   }
}


create_spirit() {

  angry=0;

  spirit=clone_object("obj/monster");
  call_other(spirit,"set_name","spirit");
  call_other(spirit,"set_level",19);
  call_other(spirit,"set_hp",250);
  call_other(spirit,"set_wc",35);
  call_other(spirit,"set_ac",10); /* 8 Guru: Spiritis are hard to hit! */
  call_other(spirit,"set_al",-300);
  call_other(spirit,"set_ep",333333); /* 666666 Guru: Lower the xp */
  call_other(spirit,"set_short","An evil powerful spirit");
  call_other(spirit,"set_long","Get out of here! It will kill you!\n");
  call_other(spirit,"set_aggressive",0);
  call_other(spirit,"set_spell_mess1","The spirit conjures a "+
              "fire elemental");
  call_other(spirit,"set_spell_mess2","The spirit throws a fire "+
              "elemental at you.");
  call_other(spirit,"set_chance",50); /* 30 Guru: He likes spells! */
  call_other(spirit,"set_spell_dam",35);
  
doomsgiver = clone_object("players/angmar/o/doomsgiver");
move_object(doomsgiver,spirit);
}

