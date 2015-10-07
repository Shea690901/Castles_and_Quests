reset(arg) {
  if(arg) return;
  /* */
}
query_weight() { return 1; }
query_value() { return 10; }
short() { return "A recipe"; }
get() { return 1; }
long() { read_recipe("recipe"); }

init() {
  add_action("read_recipe"); add_verb("read");
}

id(str) { return str== "recipe" || str=="angmars recipe"; }

read_recipe(str) {
  if(!id(str)) return 0;
  write("Ingredients:\n\n");
  write("The fresh corpse of a monster\n");
  write("A dead fish\n");
  write("A slimy mushroom\n");
  write("A corncob\n");
  write("The skeleton of a rat\n\n");
  write("Mix all ingredients in a magically prepared container.\n");
  write("Add this recipe to the mixture and speak the magic words\n");
  write("kashmirak gorondolum\n");
  return 1;
}
    
query_destruct_when_sold(){
return 1;
}
