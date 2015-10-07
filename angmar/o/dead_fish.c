inherit "obj/treasure";

init() {
  ::init();
}

reset(arg) {
  if(!arg) {
    set_id("fish");
    set_short("A dead fish");
     set_long(
	      "It smells.\n");
    set_value(1);
    set_weight(1);
    set_alias("dead fish");
  }
}
query_destruct_when_sold(){
return 1;
}
