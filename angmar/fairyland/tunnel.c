inherit "room/room";

#define LOCKED 0
#define CLOSED 1
#define OPEN 2
#define NAME this_player()->query_name()
#define OUTSIDE "players/angmar/fairyland/mountain"
#define OSIDE "players/angmar/fairyland/mountain"->query_door()
object da_thing;

reset(arg) {
  if (!arg){
    set_light(1);
    short_desc = "A tunnel in the mountain";
    no_castle_flag = 0;
    long_desc = 
      "You are in a tunnel deep in the mountain.  You can see a red\n" +
	"glow far away.  A sign on the door says: 'If the door is\n" +
	  "locked just knock.\n";
    dest_dir = 
      ({
	OUTSIDE, "south",
	"players/angmar/fairyland/dragonroom", "north",
      });
    items = 
      ({
	"door", "The door seems very strong",
	"glow", "The glow lies to the north, and pulsates rhythmically",
	"sign", "The sign reads:\n     If the door is locked, just knock",
      });
  }
  
}

query_light() {
    return 1;
}

init(){
  ::init(); 
    add_action("try_south", "south");
    add_action("read", "read");
    add_action("open", "open");
    add_action("unlock", "unlock");
    add_action("look", "look");
    add_action("exa", "exa", 1);
    add_action("close", "close");
    add_action("lock", "lock");
    add_action("knock", "knock");
    
}

try_south(){
  if (OSIDE == LOCKED){
    write("The door is locked!\n");
    return 1;
  }
  if (OSIDE == CLOSED){
    write("The door is closed.\n");
    return 1;
  }
  return 0;
}

lock(str){
  if (str != "door" && str != "door with key") return 0;
  if (OSIDE == LOCKED)
    write("The door is already locked.\n");
  else if (OSIDE == OPEN)
    write("The door is open.\n");
  else{
    da_thing = present("key", this_player());
    if (da_thing){
      if (da_thing->query_code() == "auxd"){
	write("You lock the door.\n");
	say(NAME + " locks the door.\n");
	OUTSIDE->set_door(LOCKED);
      }
      else
	write("You don't seem to have the right key.\n");
    }
  }
  return 1;
}

close(str){
  if (str != "door") return 0;
  if (OSIDE != OPEN)
    write("The door is already closed!\n");
  else{
    write("You close the door.\n");
    say(NAME + " closes the door.\n");
    OUTSIDE->set_door(CLOSED);
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
  if (OSIDE == LOCKED || OSIDE == CLOSED)
    write("The door is closed.\n");
  else
    write("The door is open.\n");
  return 1;
}

open(str){
  if (str != "door") return 0;
  if (OSIDE == LOCKED){
    write("The door is locked.\n");
    return 1;
  }
  else{
    write ("You open the door.\n");
    say (NAME + " opens the door.\n");
    OUTSIDE->set_door(OPEN);
    return 1;
  }
}


unlock(str){
  if (str != "door" && str != "door with key") return 0;
  if (OSIDE == OPEN)
    write("The door is already open.\n");
  else if (OSIDE == CLOSED)
    write("The door is already unlocked.\n");
  else{
    da_thing = present("key", this_player());
    if (da_thing){
      if (da_thing->query_code() == "auxd"){
	if (present("key", this_player())){
	  OUTSIDE->set_door(CLOSED);
	  write("You unlock the door.\n");
	  say(NAME + " unlocks the door.\n");
	}
      }
      else
	write("You don't seem to have the right key.\n");
    }
    else
      write("You don't have a key!\n");
  }
  return 1;
}

knock(){
  write ("Ok.\n");
  say(this_player()->query_name() + " knocks on the door.\n");
  OUTSIDE->set_door(CLOSED);
  return 1;
}


read(str){
  if (!str) return 0;
  if (str != "sign") return 0;
  write("The sign reads:\n     If the door is locked, just knock.\n");
  say(this_player()->query_name() + " reads the sign.\n");
  return 1;
}

