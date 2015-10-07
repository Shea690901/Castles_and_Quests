#include "../obj/living.h" /* Pell */
reset() {	       	/* Very tough, but no law against that... /Pell */
  set_heart_beat(1);
  weapon_class=28;
  max_hp=800;
  armour_class=12;		/* Pell */
  hit_point=800;
  alignment = -750;
  level=20;			/* Pell, was 18 (american inflation...) */
  experience=962500;
  is_npc=1;
  name = "minotaur";
  cap_name = "Minotaur";
  set_living_name(name);	/* Pell */
  enable_commands();
}

short() {
    return "The minotaur of the labyrinth";
}

long() {
    write ("This enormous bull-headed human looks very strong.\n");
    write ("The axe he carries does nothing to alleviate your concerns.\n");
}

id(str) { return str == "minotaur"; }

heart_beat() {
    int numx;
    object ob;
    if (attacker_ob) attack();

    ob = first_inventory(environment(this_object()));
    while(ob) {
	if(ob != this_object() && living(ob) && !call_other(ob, "query_ghost"))
	{
	    attack_object(ob);
	    return;
	}
	ob = next_inventory(ob);
    }
    numx = random(1400);
    if(numx>1300) { command("enter"); return 1; }
    if(numx>1200) { command("exit"); return 1; }
    if(numx>1100) { command("in"); return 1; }
    if(numx>1000) { command("out"); return 1; }
    if(numx>900) { command("e"); return 1; }
    if(numx>800) { command("w"); return 1; }
    if(numx>700) { command("s"); return 1; }
    if(numx>600) { command("n"); return 1; }
    if(numx>500) { command("u"); return 1; }
    if(numx>400) { command("d"); return 1; }
}

can_put_and_get(str) {
  if(!str) {
    write("Yeah, right.\n");
    return 0;
  }
  return 1;
}

catch_tell(str) {
    string who, extra;
    if(sscanf(str, "%s arrives%s", who, extra) == 2)
	test_if_any_here();
}
