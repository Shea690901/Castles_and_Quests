int current_page;
status recipeflag;
reset(arg) {
  if(arg) return;
  current_page = 0;
  recipeflag=0;
}

query_weight() {
  return 1;
}

query_value() { return 10; }
short() { return "A notebook"; }
get() { return 1; }

long() {
  write("It is a small notebook with various formulas scribbled in it.\n");
}

init() {
    add_action("open"); add_verb("open");
    add_action("close"); add_verb("close");
    add_action("read_book"); add_verb("read");
}

id(str) { return str == "book" || str == "notebook"; }

open(str) {
    object recipe;
    if (!id(str))
	return 0;
    if (current_page > 0) {
	write("The notebook is already open.\n");
	return 1;
    }
    current_page = 1;
    write("Ok.\n");
    if(!recipeflag) {
      recipeflag=1;
      recipe=clone_object("players/angmar/o/recipe");
      move_object(recipe,environment(this_player()));
      write("Something fell out of the notebook.\n");
      say("Something falls out of the notebook as "+
      call_other(this_player(),"query_name",0)+
      " opens it.\n");
    }
    return 1;
}

close(str)
{
    if (!id(str))
	return 0;
    if (current_page == 0) {
	write("It is already closed.\n");
	return 1;
    }
    current_page = 0;
    write("Ok.\n");
    return 1;
}

read_book(str)
{
    if (!id(str))
	return 0;
    if (current_page == 0) {
	write("It is closed.\n");
	return 1;
    }
    if (current_page == 1)
      write("You can't understand the language.\n");
    return 1;
}

/* Already defined above /Tanzi
get() {
  return 1;
}
*/
