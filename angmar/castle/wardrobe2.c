status door_is_open;

reset(arg) {
  if(!arg) {
    set_light(1);
    door_is_open=0;
  }
}

query_door() { return !door_is_open; }

init() {
  add_action("open_door"); add_verb("open");
  add_action("close_door"); add_verb("close");
  add_action("out"); add_verb("out");
}

short() { return "Inside a wardrobe"; }

long(str) {
  if(str=="door") {
    if(door_is_open)
        write("It is open.\n");
    else
        write("It is closed.\n");
    return 1;
  }
  write("You are inside a wardrobe. You feel magic forces\n");
  write("waiting to be released...\n");
  if(door_is_open) {
        write("The door is open.\n");
        write("The only obvious exit is out.\n");
        }
  else
        write("The door is closed.\n");
}

id(str) { return str=="door"; }

out() {
  if(!door_is_open) {
    write("The door is closed.\n");
    return 1;
  }
  call_other(this_player(),"move_player",
        "out#players/angmar/fairyland/road1");
  return 1;
}

open_door(str) {
  if(str!="door") return 0;
  if(door_is_open) { 
    write("It is already open!\n");
    return 1;
  }
  door_is_open=1;
  write("Ok.\n");
  say(call_other(this_player(),"query_name",0)+" opened the door.\n");
  return 1;
}

close_door(str) {
  if(str!="door") return 0;
  if(!door_is_open) { 
    write("It is already closed!\n");
    return 1;
  }
  door_is_open=0;
  write("Ok.\n");
  say(call_other(this_player(),"query_name",0)+" closed the door.\n");
  move_to_other();
  return 1;
}

move_to_other() {
  object ob, next_ob;
  ob=first_inventory(this_object());
  while(ob) {
    next_ob=next_inventory(ob);
    move_object(ob,"players/angmar/castle/wardrobe1");
    tell_object(ob,"You feel weightless for a moment.\n");
    ob=next_ob;
  }
}
