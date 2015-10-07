inherit "room/room";

init(){
  ::init();
    add_action("east", "east");
  }
     

reset(arg) {
  if (!arg){
    set_light(1);
    short_desc = "By Great Lake";
    no_castle_flag = 0;
    long_desc = 
        "You are standing by Great Lake.  You can hear the gulls crying.\n"
        + "If you go east, you will end up in a clump of reeds.\n";
    dest_dir = 
        ({
        "players/angmar/fairyland/crossing", "west",
        "players/angmar/fairyland/reeds", "east",
        });
    items = 
        ({
"lake", "Great Lake, the lake where Smaug is said to drink",
"reeds", "You think you see something behind the reeds",

        "gulls", "They flit off in the distance, echoes of their cries in the air",
        });
  }
}

query_light() {
    return 1;
}

realm()
{
  return ("fairyland");
}

query_inorout() { return 2; }

east() {
  object boots;
  boots=present("rubber boots",this_player());
  if(boots) {
    if(call_other(boots,"query_worn",0)) {
      call_other(this_player(),"move_player",
              "east#players/angmar/fairyland/reeds");
      return 1;
    }
  }
  write("No! You wouldn't want to get your feet wet, would you?\n");
  write("You could use a pair of rubber boots.\n");
  say(call_other(this_player(),"query_name",0));
  say(" was about to go into the reeds, but changed\n");
  say("his mind when he saw the cold water.\n");
  return 1;
}  
