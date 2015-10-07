inherit "obj/treasure";

init() {
  ::init();
}

reset(arg) {
  if(!arg) {
    set_name("corncob");
    set_short("A corncob");
     set_long(
	      "A rattly little corncob.  You wouldn't want to eat it.\n");
    set_value(10);
    set_weight(1);
    set_alias("cob");
  }
}
query_destruct_when_sold(){
return 1;
}
