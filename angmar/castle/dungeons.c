inherit "room/room";

reset(arg) {

  object rat,cash;
  object jailer;

  if (!arg){
    set_light(1);
    short_desc = "The dungeons";
    no_castle_flag = 0;
    long_desc = 
      "A long row of small dirty cells with heavy iron doors lies in front\n"
        + "of you. Though the castle has been uninhabited for many hundred years\n"
	  + "the dungeons seem to have been used recently...\n";
    dest_dir = 
      ({
        "players/angmar/castle/corridor", "north",
      });
    items = 
      ({
        "dungeons", "There are dried pools of blood and vomit on the floor",
        "floor", "The floor hasn't been washed in years",
        "pools", "Ech....you stand away from the odor",
        "rows", "Hundreds of prisoners must have been kept here at one time",

	"cells", 
	"They housed one prisoner each.  Any more would have been barbaric",

	"blood", 
	"From the color, you believe it to be human blood.  Strangely enough\nthough, there seems to be some dark liquid dried up.  Demon ichor, perhaps..",

	"vomit", 
	"Fortunately, in a way, you are not an expert on vomit.  It looks normal",
	"doors", "They look as if they have been rusted shut",
        });
  }

  if(!present("rat skeleton", this_object()))
    move_object(clone_object("players/angmar/o/rat_skeleton"), this_object());
  
  if(!present("jailer", this_object())){
    jailer=clone_object("obj/monster");
    call_other(jailer,"set_name","jailer");
    call_other(jailer,"set_level",6);
    call_other(jailer,"set_hp",100);
    call_other(jailer,"set_wc",10);
    call_other(jailer,"set_al",-40);
    call_other(jailer,"set_short","The jailer");
    call_other(jailer,"set_long","He guards the dungeons.\n");
    call_other(jailer,"set_aggressive",0);
    jailer->set_male(); /* ### MUTARA: Made the jailer male.*/
    move_object(jailer,this_object());
    cash=clone_object("obj/money");
    call_other(cash,"set_money",100+random(50));
    move_object(cash,jailer);
  }
}

query_light() {
    return 1;
}

query_inorout() { return 1; }

init(){
  add_action("open", "open");
  add_action("close", "close");
  add_action("enter", "enter");
  add_action("kick", "kick");
  ::init();
}

open(str){
  if (!str)
    return 0;
  if (str == "door" || str == "doors"){
    write("The doors have been rusted shut for all of the cells.\n");
    say(this_player()->query_name() + " struggles to open a door, but fails.\n");
    return 1;
  }
  else if (str == "cells"){
    write("You struggle, but you cannot open the cell.  Perhaps a door?\n");
    return 1;
  }
  else
    return 0;
}

close(str){
  if (!str)
    return 0;
  if (str == "cells" || str == "cell"){
    write("The cells already have closed doors.\n");
    return 1;
  }
  else if (str == "doors" || str == "door"){
    write ("The doors are rusted shut.\n");
    return 1;
  }
  else
    return 0;
}

enter(str){
  if (!str)
    return 0;
  if (str == "cells"){
    write("The doors are rusted shut.  You cannot enter.\n");
    return 1;
  }
  else
    return 0;
}

kick(str){
  if (!str)
    return 0;
  if (str == "door" || str == "doors"){
    write("You kick the door with all your might.\n");
    write("You hear something snap, and hope it was the door.\n");
    say(this_player()->query_name() + " kicks the door, and howls in pain.\n");
    return 1;
  }
  else
    return 0;
}
