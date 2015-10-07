reset (arg) {
  if (!arg)
    set_light(1);
  extra_reset();
  sign();
}


extra_reset () {
  object troll1, troll2, troll3, money, treas, weapon;
  int n, i;
  
  if (!present ("troll")) {
    i = 0;
    while (i<2) {
      i += 1;
      troll1 = clone_object ("obj/monster");
      call_other (troll1, "set_name", "troll");
      call_other (troll1, "set_alias", "blacktroll");
      call_other (troll1, "set_race", "troll");
      call_other (troll1, "set_level", 12);
      call_other (troll1, "set_hp", 140);
      /*	call_other (troll1, "set_ep", 175000);*/ /* Pell */
      call_other (troll1, "set_al", -125);
      call_other (troll1, "set_short", "A black troll");
      call_other (troll1, "set_long",
		  "It is a hideously ugly troll. with coruscating sparks of electricity\n" +
		  "    cascading off its mottled hide.\n");
      call_other (troll1, "set_aggressive", 1);
      call_other (troll1, "set_wc", 15);
      call_other (troll1, "set_ac", 4);
      call_other (troll1, "set_spell_mess1",
		  "The troll throws lightning!");
      call_other (troll1, "set_spell_mess2",
		  "The troll hurls a bolt of electricity at you!");
      call_other (troll1, "set_chance", 18);
      call_other (troll1, "set_spell_dam", 20);
      move_object (troll1, this_object());
      treas = clone_object ("obj/treasure");
      call_other (treas, "set_id", "corundum");
      call_other (treas, "set_alias", "stone");
      call_other (treas, "set_short", "A piece of corundum");
      call_other (treas, "set_value", random(200) + 100);
      move_object (treas, troll1);
    }
    troll2 = clone_object ("obj/monster");
    call_other (troll2, "set_name", "troll");
    call_other (troll2, "set_alias", "redtroll");
    call_other (troll2, "set_race", "troll");
    call_other (troll2, "set_level", 15); /* Pell */
    call_other (troll2, "set_hp", 150);
    /*	call_other (troll2, "set_ep", 175000);*/ /* Pell */
    call_other (troll2, "set_al", -125);
    call_other (troll2, "set_short", "A red troll");
    call_other (troll2, "set_long",
		"It is an enormous troll, with bulging muscles. It looks VERY strong.\n");
    call_other (troll2, "set_aggressive", 1);
    call_other (troll2, "set_wc", 20);
    call_other (troll2, "set_ac", 6);
    call_other (troll2, "set_spell_mess1",
		"The troll throws a sucker punch!");
    call_other (troll2, "set_spell_mess2",
		"The troll punches you, rupturing some vital organ!");
    call_other (troll2, "set_chance", 5);
    call_other (troll2, "set_spell_dam", 24);
    move_object (troll2, this_object());
    weapon = clone_object ("obj/weapon");
    call_other (weapon, "set_name", "club");
    call_other (weapon, "set_alias", "spiked club");
    call_other (weapon, "set_short", "A huge spiked club");
    call_other (weapon, "set_class", 12);
    call_other (weapon, "set_weight", 4);
    call_other (weapon, "set_value", 500);
    move_object (weapon, troll2);
    
    n = 0;
    while(n<5) {
      n +=1;
      troll3 = clone_object ("obj/monster.talk");
      call_other (troll3, "set_name", "troll");
      call_other (troll3, "set_race", "troll");
      call_other (troll3, "set_level", random(4) + 7);
      call_other (troll3, "set_hp", random(20) + 90);
      call_other (troll3, "set_al", -75);
      call_other (troll3, "set_short", "A troll");
      call_other (troll3, "set_long",
		  "A run-of-the-mill troll.\n");
      call_other (troll3, "set_aggressive", 1);
      call_other (troll3, "set_wc", random(3) + 9);
      call_other (troll3, "set_a_chat_chance", 30);
      call_other (troll3, "load_a_chat", "Troll says: Raaaaaaarrrrrrrgh!\n");
      call_other (troll3, "load_a_chat", "Troll says: Smash human!\n");
      call_other (troll3, "load_a_chat", "Troll says: Tell me about the rabbits, George!\n");
      call_other (troll3, "load_a_chat", "Troll says: Crunch dem bones!\n");
      move_object (troll3, this_object());
      money = clone_object ("obj/money"); 
      call_other (money, "set_money", random(200));
      move_object (money, troll3);
    }
  }
}

sign() {
  
  object sign;
  
  if (!present("sign")) {
    sign = clone_object ("obj/treasure");
    call_other (sign, "set_id", "sign");
    call_other (sign, "set_short", "An important sign");
    call_other (sign, "set_long", "The sign says: WARNING!\n\n" +
		"The hut to the north contains a creature which is very tough.\n" + /* Pell */
		"Do not enter for the risk of your life. Watch out!\n"); /* Pell */
    call_other (sign, "set_read", "The sign says: WARNING!\n\n" + /* Pell */
		"The hut to the north contains a creature which is very tough.\n" + /* Pell */
		"Do not enter for the risk of your life. Watch out!\n"); /* Pell */
    call_other (sign, "set_value", 0);
    call_other (sign, "set_weight", 10000);
    move_object (sign, this_object());
  }
}

init() {
  add_action ("east"); add_verb ("east");
  add_action ("north"); add_verb ("north");
  add_action ("west"); add_verb ("west");
}

east() {
  call_other (this_player(), "move_player", "east#players/quantos/desert/track1");
  return 1;
}

north() {
  if (present ("troll")) {
    write ("A troll moves to intercept you.\n");
    return 1;
  }
  call_other (this_player(), "move_player", "north#players/quantos/desert/troll_hut");
  return 1;
}

west() {
  call_other (this_player(), "move_player", "west#players/quantos/desert/track2");
  return 1;
}

id(str) { return str == "hut"; } /* Pell */

long(str) {			/* Pell */
  if (str == "hut")		/* Pell */
    write("A small hut. Some strange noises can be heard from the inside...\n"); /* Pell */
  else {			/* Pell */
    write ("This is the desert village of a group of trolls.\n");
    write ("There is a large hut to the north.\n");
    write ("The track through the village leads east and west.\n");
  }				/* Pell */
}

short() {
  return "The troll village";
}
