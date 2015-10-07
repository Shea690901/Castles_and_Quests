long() {
  write("A stone statue of an elf. It is very well made, it\n");
  write("looks almost alive...\n");
}
reset(arg) {
  if (arg) return;
  /* first reset */
}
query_weight() {
  return 200;
}
short() {
  return "A stone statue";
}
id(str) {
  return str=="statue" || str=="stone statue";
}
get() {
  return 0;
}
revive() {
  object elfwarrior,we,sta;
  sta=this_object();
  write("The statue begins to glow!\n");
  say("The statue begins to glow!\n");
  write("The statue has suddenly transformed into an elfwarrior!\n");
  say("The statue has suddenly transformed into an elfwarrior!\n");

  elfwarrior=clone_object("obj/monster");
  call_other(elfwarrior,"set_name","elfwarrior");
  call_other(elfwarrior,"set_level",18);
  call_other(elfwarrior,"set_hp",200);
/*  call_other(elfwarrior,"set_wc",20); Removed due to change in monsters /Tanzi */
  call_other(elfwarrior,"set_ac",5);
  call_other(elfwarrior,"set_short","An elfwarrior");
  call_other(elfwarrior,"set_alias","warrior");
  call_other(elfwarrior,"set_al",100);
  call_other(elfwarrior,"set_long",
    "He looks very confused. He probably wonders where\n"+
    "the wizard he just fought went\n");

  we=clone_object("obj/weapon");
  call_other(we,"set_name","mace");
  call_other(we,"set_short","A heavy mace");
  call_other(we,"set_long","It has fresh bloodstains on it.\n");
  call_other(we,"set_class",15);
  call_other(we,"set_value",1000);
  call_other(we,"set_weight",4);
  move_object(we,elfwarrior);

  we=clone_object("players/angmar/o/mithril_ring");
  move_object(we,elfwarrior);

  move_object(elfwarrior,environment(sta));
  call_other(elfwarrior,"init_command","wield mace");
  destruct(this_object());
}
