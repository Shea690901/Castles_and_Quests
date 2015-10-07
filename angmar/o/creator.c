object master;

id(str) { return str=="creator"; }
short() { return "A palantir creator"; }
get() { return 0; }

long() {
  write("This magical device will create communication palantirs.\n");
  write("Command: palantir\n");
  write("It will cost you 5 spell-points\n");
  return 1;
}

init() {
  add_action("palantir","palantir");
}

set_master(ob) {
  master=ob;
}


palantir() {
  if(!master) {
    destruct(this_object());
    return 0;
  }
  if(this_player()->query_spell_points()<5) {
    write("Too low on power.\n");
    return 1;
  }
  master->phone();
  this_player()->restore_spell_points(-5);
  return 1;
}
