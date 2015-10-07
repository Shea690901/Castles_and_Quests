long() {
    write("A big black iron cauldron. I wonder what it has been used for?\n");
}

reset(arg) {
    if (arg) return;
    /* first reset */

}

catch_it(str) {
  string a,b;
  if(sscanf(str,"%skashmirak gorondolum%s",a,b)==2) {
    if(check_ingredients()) {
      reward();
    }
    else write("Nothing happens.\n");
  }
}

reward() {
  int lev;
  object me;
  object ob, next_ob;
  object ring;

  me=this_player();
  lev=call_other(me,"query_level",0);
  write("Gosh! Steam comes out of the cauldron!\n");
  say("Gosh! Steam comes out of the cauldron!\n");

  ob=first_inventory(this_object());
  while(ob) {
    next_ob=next_inventory(ob);
    destruct(ob);
    ob=next_ob;
  }


  if(lev<12) {
    int x;
    object money;
    x=lev*100+random(100);
    money=clone_object("obj/money");
    call_other(money,"set_money",x);
    move_object(money,this_object());
  }

    ring=clone_object("players/angmar/o/silver_ring");
    move_object(ring,this_object());
}

check_ingredients() {
  object corpse;
  string a;

  if(!present("dead fish") ||
     !present("slimy mushroom") ||
     !present("rat skeleton") ||
     !present("corncob") ||
     !present("angmars recipe")) return 0;

  corpse=present("corpse");
  if(!corpse) return 0;
return (sscanf(call_other(corpse,"short",0),"corpse of %s",a)==1)||
       (sscanf(call_other(corpse,"short",0),"Corpse of %s",a)==1);
}


query_weight() {
    return 100;
}

add_weight(w) {
  return 1;
}

short() {
    return "A big cauldron";
}

id(str) {
    return str == "cauldron";
}

query_value() {
    return 0;
}

can_put_and_get() { return 1; }

get() {
    return 0;
}
