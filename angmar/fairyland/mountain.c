inherit "room/room";
/* 
 * Door code courtesy of Tanzi.
 */

#define LOCKED 0
#define CLOSED 1
#define OPEN 2
#define NAME this_player()->query_name()

int door;
object da_thing;

reset(arg) {
  call_other("players/angmar/fairyland/inn", "external_reset", 0);
  if (!arg){
    set_light(1);
    short_desc = "Misty Mountain";
    no_castle_flag = 0;
    long_desc = 
      "You are climbing Misty Mountain.  There is a door set into\n" +
	"the rock before you.\n";
    dest_dir = ({
      "players/angmar/fairyland/mountain_top", "up",
      "players/angmar/fairyland/mountain_foot", "down",
      "players/angmar/fairyland/rock_ledge", "east",
      "players/angmar/fairyland/tunnel", "north",
    });
    items = ({
      "misty mountain", "Misty Mountain still looms over you",
      "mountain", "Misty Mountain still looms over you",
    });
  }
  door = LOCKED;
}

init(){
  ::init();
    add_action("try_north", "north");
    add_action("open", "open");
    add_action("unlock", "unlock");
    add_action("look", "look");
    add_action("exa", "exa", 1);
    add_action("close", "close");
    add_action("lock", "lock");
}

lock(str){
  if (str != "door" && str != "door with key") return 0;
  if (door == LOCKED)
    write("The door is already locked.\n");
  else if (door == OPEN)
    write("The door is open.\n");
  else{
    da_thing = present ("key", this_player());
    if (da_thing){
      if (da_thing->query_code() == "auxd"){
	write("You lock the door.\n");
	say(NAME + " locks the door.\n");
	door == LOCKED;
      }
      else
	write("You don't seem to have the right key.\n");
    }
    else
      write("You don't have a key!\n");
  }
  return 1;
}


close(str){
  if (str != "door") return 0;
  if (door != OPEN) 
    write("The door is already closed!\n");
  else{
    write("You close the door\n");
    say(NAME + " closes the door.\n");
    door = CLOSED;
  }
  return 1;
}

look(str){
  string s1;
  if (!str) return 0;
  if (sscanf(str, "at %s", s1) == 1)
    return exa(s1);
  else
    return 0;
}

exa(str){
  if (str != "door") return 0;
  if (door == LOCKED || door == CLOSED)
    write("The door is closed.\n");
  else
    write("The door is open.\n");
  return 1;
}

try_north(){
  if (door == LOCKED){
    write("The door is locked!\n");
    return 1;
  }
  if (door == CLOSED){
    write("The door is closed.\n");
    return 1;
  }
  return 0;
}

open(str){
  if (str != "door") return 0;
  if (door == LOCKED){
    write("The door is locked.\n");
    return 1;
  }
  else{
    write("You open the door.\n");
    say(NAME + " opens the door.\n");
    door = OPEN;
    return 1;
  }
}

unlock(str){
  if (str != "door" && str != "door with key") return 0;
  if (door == OPEN) 
    write("The door was already open!\n");
  else if (door == CLOSED)
    write("The door is already unlocked.\n");
  else{
    da_thing = present("key", this_player());
    if (da_thing){
      if (da_thing->query_code() == "auxd"){
	if (present("key", this_player())){
	  door = CLOSED;
	  write("You unlock the door.\n");
	  say(NAME + " unlocks the door.\n");
	}
      }
      else
	write("You don't seem to have the right key!\n");
    }
    else
      write("You don't have a key!\n");
  }
  return 1;
}

query_light() {
  return 0;
}

query_door(){
  return door;
}

set_door(arg){
  door = arg;
  return arg;
}

auto_unlock(){
  door = OPEN;
  return 1;
}
