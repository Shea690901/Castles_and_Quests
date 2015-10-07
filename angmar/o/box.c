int box_open;
status scrollflag;
reset(arg) {
  if(arg) return;
  box_open = 0;
  scrollflag=0;
}

query_weight() {
  return 1;
}

query_value() { return 20; }
short() { return "A small box"; }
get() { return 1; }

long() {
write("It is a small rusty box. It must have been very long in the water.\n");
}

init() {
    add_action("open"); add_verb("open");
    add_action("close"); add_verb("close");
}

id(str) { return str == "box" || str == "small box" || str=="rusty box"; }

open(str) {
    object scroll;
    if (!id(str))
	return 0;
    if (box_open) {
	write("The small box is already open.\n");
	return 1;
    }
    box_open = 1;
    write("Ok.\n");
    if(!scrollflag) {
      scrollflag=1;
      scroll=clone_object("players/angmar/o/scroll");
      move_object(scroll,environment(this_player()));
      write("Something fell out of the small box.\n");
      say("Something falls out of the small box as "+
      call_other(this_player(),"query_name",0)+
      " opens it.\n");
    }
    return 1;
}

close(str)
{
    if (!id(str))
	return 0;
    if ( box_open == 0) {
	write("It is already closed.\n");
	return 1;
    }
    box_open = 0;
    write("Ok.\n");
    return 1;
}

/* ### Guru: Unnecessary get. Declared earlier. 
get() {
  return 1;
}
*/
