string shortname;
int worn;

reset(arg) {
  if(arg) return;
  shortname="A platinum ring";
}

query_weight() { return 0; }
query_value() { return 0; }

short() { 
  if(worn) return shortname+" (worn)";
  else return shortname;
}

get() { 
  if(!call_other(this_player(),"query_npc",0)) {
    write("The platinum ring slips onto one of your fingers by\n");
    write("some invisible force as you take it.\n");
    worn=1;
  }
  return 1;
}

long() { 
  write("A pretty platinum ring. It has some inscriptions, but the\n");
  write("words seems like gibberish, except for the name Angmar.\n");
}

init() {
add_action("read", "read");
  add_action("wear_ring"); add_verb("wear");
  add_action("quit"); add_verb("quit");
}

wear_ring(str) {
  if(id(str)) {
    if(worn) write("You are already wearing it.\n");
    else write("You must get it first.\n");
    return 1;
  }
}

id(str) { return str== "ring" || str=="platinum ring" || str=="trlock2"; }

destring() {
    write("The platinum ring suddenly disappears in a puff of smoke.\n");
    say("The platinum ring suddenly disappears in a puff of smoke.\n");
    destruct(this_object());
}

drop(silent) {
  if(!worn) return 0;
  return 1;
}

quit() {
  if(!worn) return 1;
  write("The platinum ring suddenly disappears in a puff of smoke.\n");
  say("The platinum ring suddenly disappears in a puff of smoke.\n");
  destruct(this_object());
  call_other(this_player(),"quit",0);
}
read(str){
if (!str) return 0;
if (str != "ring" && str != "writing") return 0;
write ("The writing on the ring is in a different language.\n");
write ("However, you recognize some of the glyphs to mean 'Angmar'.\n");
return 1;
}
