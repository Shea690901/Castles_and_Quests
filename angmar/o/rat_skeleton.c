inherit "obj/treasure";

init() {
  ::init();
}

reset(arg) {
  if(!arg) {
    set_id("skeleton");
    set_short("A rat skeleton");
     set_long(
	      "A perfectly preserved rat skeleton.  The jailer's lunch, perhaps?\n");
    set_value(1);
    set_weight(1);
    set_alias("rat skeleton");
  }
}
query_destruct_when_sold(){
return 1;
}
