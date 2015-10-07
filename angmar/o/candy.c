inherit "obj/treasure";

init(){
  add_action("Eat_candy", "eat");
  add_action("Lick_candy", "lick");
}

reset(arg){
  set_id("candy");
  set_alias("taffy");
  set_short("Candy");
  set_long("It's a small piece of salt-water taffy.  There's a bit of dirt\n" +
	   "and dust on the candy, but it looks edible enough.  It brings\n" +
	   "you back a few years, to when you were a child, and loved candy.\n");
  set_value(4);
  set_weight(1);
}

Eat_candy(str){
  if (!str) return 0;
  if (str != "candy" && str != "taffy") return 0;
  write("You sink your teeth into the candy.  It tastes delicious.\n");
  say(this_player()->query_name() + " eats a bit of candy.\n");
  transfer(this_object(), environment(this_player()));
  destruct(this_object());
  return 1;
}

Lick_candy(str){
  if (!str) return 0;
  if (str != "candy" && str != "taffy") return 0;
  write("The candy dissolves as your tongue touches it.  It was delicious.\n");
  say(this_player()->query_name() + " eats a bit of candy.\n");
  transfer(this_object(), environment(this_player()));
  destruct(this_object());
  return 1;
}
