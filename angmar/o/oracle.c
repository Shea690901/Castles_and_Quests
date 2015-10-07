#include <living.h>

int trig,trig2,trig3,destsword;
string nam,str1,str2,str3;
object tplr,meob;

reset(arg)
{
    if (arg)
       return;
    max_hp = 30;
    hit_point = 30;
    armour_class = 9999;
    level = 3;
    experience = 2000;
    weapon_class = WEAPON_CLASS_OF_HANDS;
    is_npc = 1;
    name = "oracle";
    cap_name = "Oracle";
    alignment = 100;
    trig=0; trig2=0; trig3=0;
    enable_commands();
    meob=this_object();
}

init() {
  set_heart_beat(1);  
  tplr=this_player();
  nam=call_other(tplr,"query_name",0);
  if(here_before(nam)) trig3=1;  /* ask mission */
  else trig=1;  /* first greet */
}

short() {
   return "The all-wise oracle";
}

long() {
    write("He sits here alone meditating over things incomprehensible\n");
    write("to ordinary humans. If you have a problem, he might be\n");
    write("able to help you.\n");
}

id(str) { return str == name; }

catch_tell(str) {
  object old_room;
  string fromwho,towho,what;
  set_heart_beat(1);
  if(sscanf(str,"%s gives %s to %s.",fromwho,what,towho)==3) {
    if(what=="doomsgiver" && towho=="Oracle" && present("doomsgiver")) {

/*      call_other("players/angmar/castle/treasury","reset",1); */

      say("The Oracle smiles and says: Thank you, "+fromwho+". \n");
      say("He says: 'Now listen carefully. The password to the doors\n");
      say("changes all the time. It is '");
      say(call_other("players/angmar/castle/treasury","query_password",0));
      say("' right now,\n");
      say("but can change any minute, so hurry! And good luck!'\n");
      forget(fromwho);
      call_other("players/angmar/castle/treasury","prevent_reset",0);
      destsword=2;
    }
  }
}

heart_beat() {
  age += 1;

  if(destsword>0) {
    object sword;
    destsword-=1;
    if(destsword==0) {    
      sword=present("doomsgiver");
      if(sword) {
        destruct(sword);
        say("The Oracle makes a magical gesture and the sword disappears.\n"); 
      }
    }
  }

  if(trig>0) {
    trig -= 1;
    if(trig==0) {
      /* first greet */
      say("The Oracle says: Welcome ");
      say(nam);
      say(".\n"); 
      if(got_rings()) {
        trig2=2;      /* give mission */
      }
    }
  }

  if(trig3>0) {
    trig3-=1;
    if(trig3==0 && present(tplr)) {
      /* ask mission */
      say("The Oracle says: Welcome again, ");
      say(nam);
      say("!\n");
      if(!got_rings()) {
        say("The Oracle sigs. He says: 'Lost the rings? Too bad. There\n");
        say("is no way to get that treasure without the rings. Sorry.'\n");
        forget(nam);
        }
      else {
        say("Did you get the sword for me as you promised?\n");
      }
    }
  }

  if(trig2>0) {
    trig2-=1;
    if(trig2==0 && present(tplr)){
say("The Oracle smiles. He says: 'I can see that you have found the\n");
say("rings. Looking for the password, eh?' The Oracle laughs.\n");
say("'Well, I do nothing for free, you see.' He lower his voice, leans\n");
say("closer to you and says: 'If you could find the famous sword\n");
say("Doomsgiver and give it to me, I might help you.'\n");
say("It is said to be found somewhere deep in the castle of\n");
say("Angmar, but beware! The legend also tells about a fearful\n");
say("spirit guarding the mighty sword!\n");
say("The oracle returns to his meditating and says no more.\n");
remember(nam);
    }
  }
}

got_rings() {
 return (present("trlock1",tplr) && present("trlock2",tplr) &&
        present("trlock3",tplr));
}

remember(str) {
  str3=str2;
  str2=str1;
  str1=lower_case(str);
}

here_before(str) {
  str=lower_case(str);
  return(str==str1 || str==str2 || str==str3);
}

forget(str) {
  str=lower_case(str);
  if(str==str1) str1="";
  if(str==str2) str2="";
  if(str==str3) str3="";
}
