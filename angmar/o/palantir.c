#define MAXRINGS 6

int number,is_calling,nr_of_rings, online;
object remotephone, station, caller, lastring;
string callername;

reset(arg) {
  if(arg) return;
  online=0; number=0; is_calling=0;
}

query_weight() { return 0; }
query_value() { return 1; }
short() { return "A palantir"; }
get() { return 1; }

long() { 
  write("It's a large spherical crystal ball.\n");
  write("Deep inside you can see the number "+number+" written in\n"+
	"letters of fire.\n");
  write(
"The palantir whispers to your mind the words of magic that makes it work:\n");
  write(" 'contact <nr>' where nr is a number of another palantir.\n");
  write("                This will make the palantir try to contact the other\n");
  write("                palantir. The owner of the other palantir can choose if\n");
  write("                he/she wants to answer or not.\n");
  write(" 'answer'       Will create a link between this and the\n");
  write("                calling palantir. The link will remain until\n");
  write("                either palantir owner breaks it, or the palantir is\n");
  write("                destroyed.\n");
  write(" 'break'        Will break a link, or stop trying to make contact.\n");
  write(" 'say <message>' Only the other palantir and its owner will hear it.\n");
  write(" 'palantirs'    Will contact the master-palantir, which will inform\n");
  write("                you about all other palantirs and their owners.\n");
  write(" 'split'        Will create a new palantir out of the old one.\n");
  write("                cost: 5 spellpoints.\n");               

  write("\nThis palantir was created by the palantir-creator inside Angmar's castle.\n");
  write(
"\nnote: this tool is under construction. PLEASE report bugs to Angmar.\n");
}

init() {
  add_action("dial"); add_verb("contact");
  add_action("answer"); add_verb("answer");
  add_action("hangup"); add_verb("break");
  add_action("phonebook"); add_verb("palantirs");
  add_action("mysay"); add_verb("say");
  add_action("split"); add_verb("split");
}

id(str) { return str== "palantir"; }

split() {
  if(!station) {
    say("The palantir begins to shimmer and slowly disappears. It whispers:\n");
    say("The master-palantir is destroyed!\n");
    write("The palantir begins to shimmer and slowly disappears. It whispers:\n");
    write("The master-palantir is destroyed!\n");
    destruct(this_object());
    return 1;
  }

  if(this_player()->query_spell_points()<5) {
    write("Too low on power.\n");
    return 1;
  }
  station->phone();
  this_player()->restore_spell_points(-5);
  return 1;
}

phonebook() {
  if(!station) {
    say("The palantir begins to shimmer and slowly disappears. It whispers:\n");
    say("The master-palantir is destroyed!\n");
    write("The palantir begins to shimmer and slowly disappears. It whispers:\n");
    write("The master-palantir is destroyed!\n");
    destruct(this_object());
    return 1;
  }
  station->phonebook();
  return 1;
}

hangup() {

  if(!station) {
    say("The palantir begins to shimmer and slowly disappears. It whispers:\n");
    say("The master-palantir is destroyed!\n");
    write("The palantir begins to shimmer and slowly disappears. It whispers:\n");
    write("The master-palantir is destroyed!\n");
    if(remotephone) remotephone->remote_hangup();
    remove_call_out("remote_ring");    
    destruct(this_object());
    return 1;
  }

  if(!online) {
    if(is_calling) {
      is_calling=0;
      online=0;
      caller=0;
      remotephone=0;
      say(this_player()->query_name()+" looks up from the palantir.\n");
      write("You break the magic connection.\n");
      remove_call_out("remote_ring");
      return 1;
    }
    write("The palantir is not activated.\n");
    return 1;
  }
  say(this_player()->query_name()+" looks up from the palantir.\n");
  write("You break the magic connection.\n");
  if(!remotephone) {
/*  write("Error. Online, but no other phone. Recovering.\n"); */
  }
  if(remotephone) remotephone->remote_hangup();
  is_calling=0;
  online=0;
  caller=0;
  remotephone=0;
  is_calling=0;
  return 1;
}

remote_hangup() {
  if(!online) return;
  if(caller) 
    tell_object(caller,"The palantir becomes black. The connection is broken.\n");
  if(callername && caller) say(callername+" looks up from the palantir.\n",caller);
  online=0;
  remotephone=0;
  caller=0;
  is_calling=0;
}

set_nr(nr) {
  number=nr;
}

set_station(obj) {
  station=obj;
}

dial(str) {
  int nr;
  object tmp;
  if(!station) {
    say("The palantir begins to shimmer and slowly disappears. It whispers:\n");
    say("The master-palantir is destroyed!\n");
    write("The palantir begins to shimmer and slowly disappears. It whispers:\n");
    write("The master-palantir is destroyed!\n");
    destruct(this_object());
    return 1;
  }
  if(!str) return 0;
  if(sscanf(str,"%d",nr)!=1) {
    write("Contact what number?\n");
    return 1;
  }
  caller=this_player();
  callername=this_player()->query_name();
  remotephone=station->dial_up(nr);
  if(online || is_calling || remotephone==this_object()) {
    if(!is_calling && !remotephone) {
/*    write("Error: Online, but no other phone. Recovering.\n"); */
      write("A red mist swirls in the palantir, then it goes black again.\n");
      online=0;
      caller=0;
      return 1;
    }
    write("You must break the link to the other palantir first.\n");
    return 1;
  }

  say(callername+" stares deep into the palantir.\n");

  if(remotephone==0) {
    write("You can see a grey mist swirl in the palantir, but nothing happens.\n");
  return 1;
  }

  tmp=remotephone->query_lastring();
  /* last check is to make sure a phone being called is marked busy */
  if(remotephone->query_calling() || remotephone->query_online() ||
     (tmp && tmp->query_calling() && (tmp->query_remote()==remotephone))) {
    write(
"You can hear voices whispering in the palantir for an instant, then it goes\n"+
"black again. The other palantir is probably busy.\n");
    return 1;
  }

  nr_of_rings=0;
  is_calling=1;
  remote_ring();
  return 1;
}

remote_ring() {
  if(!caller || (!present(caller,environment()) &&
			  !present(this_object(),caller))) {
    is_calling=0;
    remotephone=0;
    caller=0;
    return 1;
  }
  nr_of_rings+=1;
  if(nr_of_rings>=MAXRINGS) {
    tell_object(caller,"The palantir goes black again.\n");
    say(callername+" looks up from the palantir.\n");
    is_calling=0;
    caller=0;
    return;
  }

  if(!remotephone || remotephone->online() || remotephone->is_ringing()) {
    tell_object(caller,"The palantir becomes black. The connection is broken.\n");
  if(callername && caller) say(callername+" looks up from the palantir.\n",caller);
    is_calling=0;
    online=0;
    return;
  }

  tell_object(caller,"Blue mist swirls in the palantir.\n");
  remotephone->ring(this_object());
  call_out("remote_ring",5);
}

ring(obj) {
  tell_object(environment(this_object()),
     "The palantir whispers to your mind and tries to get your attention.\n");
  tell_room(environment(this_object()),
     "The palantir whispers to your mind and tries to get your attention.\n");
  lastring=obj;
}

query_calling() {
  return is_calling;
}

query_caller() {
  return caller;
}

query_online() {
  return online;
}

query_lastring() {
  return lastring;
}

query_remote() {
  return remotephone;
}

answer () {
  if(!station) {
    say("The palantir begins to shimmer and slowly disappears. It whispers:\n");
    say("The master-palantir is destroyed!\n");
    write("The palantir begins to shimmer and slowly disappears. It whispers:\n");
    write("The master-palantir is destroyed!\n");
    destruct(this_object());
    return 1;
  }
  caller=this_player();
  callername=caller->query_name();
  if(!lastring || !lastring->query_calling()) {
    tell_object(caller,"Nothing happens.\n");
    return 1;
  }
  say(callername+" stares deep into the palantir.\n");
  write("You stare deep into the palantir.\n");
  remotephone=lastring;
  remotephone->remote_answer();
  online=1;
  return 1;
}

remote_answer() {
  if(!caller || (!present(caller,environment()) &&
			  !present(this_object(),caller))) {
    if(remotephone) remotephone->remote_hangup();
    is_calling=0;
    online=0;
    remove_call_out("remote_ring");
    return;
  }
  tell_object(caller,
	      "Suddenly you can see a face in the palantir.\n");
  remove_call_out("remote_ring");
  is_calling=0;
  online=1;
}

tellphone(str) {
  object tellobj;
  if(!remotephone) {
    write("The palantir becomes black. The connection is broken.\n");
    if(callername && caller)
      say(callername+" looks up from the palantir.\n",caller);
/*    write("Error: remote phone not found. Recovering.\n"); */
    online=0;
    caller=0;
    return 0;
  }
  tellobj=remotephone->query_caller();
  if(!tellobj || (!present(tellobj,environment(remotephone)) &&
		  !present(remotephone,tellobj))) {
    remotephone->remote_hangup();
    remote_hangup();
    return 0;
  }
  tell_object(tellobj,str);
  return 1;
}

mysay(str) {
  if(!station) {
    say("The palantir begins to shimmer and slowly disappears. It whispers:\n");
    say("The master-palantir is destroyed!\n");
    write("The palantir begins to shimmer and slowly disappears. It whispers:\n");
    write("The master-palantir is destroyed!\n");
    destruct(this_object());
    return 0;
  }
  if(online && this_player() == caller) {
    if(!str) {
      write("Say what ?\n");
      return 1;
    }
    write("You whisper something to the palantir.\n");
   if(tellphone("The palantir whispers: " + str + "\n"))
     say(callername + " whispers something to the palantir.\n");
    return 1 ;
  }    
  this_player()->communicate(str);
  return 1;
}



