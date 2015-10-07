status door_is_open;
int resetcounter;
string password;
object listener;

realm() return ("NT");

reset(arg) {
  if(!arg) set_light(1);
  if(!listener || !living(listener)) {
    listener=clone_object("players/angmar/catch_password.c");
    call_other(listener,"set_call","catch_it");
    move_object(listener,"players/angmar/treasury_entrance");
  }
  new_password();
}

catch_it(str) {
  string a,b;
  if(sscanf(str,"%s"+password+"%s",a,b) == 2) {
    call_other("players/angmar/treasury_entrance","password_ok",0);
  }
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

query_password() {
  return password;
}

query_resetcounter() {
  return resetcounter;
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
        "south#players/angmar/treasury_entrance");
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
