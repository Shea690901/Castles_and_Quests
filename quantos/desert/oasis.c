object newspaper, top_list;

reset(arg) {
  if (!top_list || !present(top_list)) {
    top_list = clone_object("obj/level_list");
    move_object(top_list, this_object());
  }
  if (arg) return;
  set_light( 1);
}

short() {
  return "An oasis";
}

init() {
  add_action ("move"); add_verb ("west");
  add_action ("north"); add_verb ("north");
  add_action ("order"); add_verb ("order");
  add_action ("order"); add_verb ("buy");
  add_action ("read"); add_verb ("read");
  add_action ("dest"); add_verb ("dest");
}

move() {
  object ob;
  call_other(this_player(), "move_player",  "west#players/quantos/desert/desert1");
  return 1;
}

north() {
  call_other(this_player(), "move_player", "north#players/quantos/desert/mirage");
  return 1;
}

long() {
  write("You have entered a desert oasis.\n");
  write("You can order drinks here.\n\n");
  write("Type 'read menu' to see a list of drinks.\n");
  write("Type 'read dest' to see a list of teleporter destinations.\n");
}

read(str) {
  if (str == "menu") {
/* New, lower prices, except for non-alco /Pell */
    write("-------------------------------------------\n");
    write("|           Alcoholic beverages           |\n");
    write("|           -------------------           |\n");
    write("|            Cerveza : 4 coins            |\n");
    write("|         Pin~a Colada : 25 coins         |\n");
    write("|           Mai-tai : 50 coins            |\n");
    write("|            Kahlua : 100 coins           |\n");
    write("|         Tequila shot : 150 coins        |\n");
/*    write("|      (Breathalyzer test : 10 coins)     |\n"); /Pell */
    write("|                                         |\n");
    write("|         Non-alcoholic beverages         |\n");
    write("|         -----------------------         |\n");
    write("|             Water : 15 coins            |\n");
    write("|         Mango juice : 100 coins         |\n");
    write("|           Perrier : 250 coins           |\n");
    write("|         Papaya juice : 600 coins        |\n");
    write("|       Pineapple juice : 750 coins       |\n");
    write("|         Coconut milk : 900 coins        |\n");
    write("-------------------------------------------\n");
    return 1;
  }
  else if (str == "dest") {
    write("The teleporter panel is here. Type 'dest #' to go to the\n");
    write("destination designated by the number.\n\n");
    write("(1) Old humpbacked bridge\n");
    write("(2) Village shop\n");
    write("(3) Church\n");
    write("(4) Orc Valley\n"); /* Pell */
    write("(5) The plain by the ruins\n\n");
/* Changed to use spell points instead /Pell */
    write("The teleportation service costs 25 spell points.\n");
    return 1;
  }
  return 0;
}

dest(str) {
/* Changed to use spell points instead /Pell */
  if (call_other (this_player(), "query_spell_points", 0) < 25) { /* Pell */
    write ("You feel to weak to teleport!\n"); /* Pell */
    return 1;
  }
  else {
    call_other (this_player(), "restore_spell_points", - 25); /* Pell */
    if (str == "1") {
      call_other (this_player(), "move_player", "one#room/hump");
      return 1;
    }
    else if (str == "2") {
      call_other (this_player(), "move_player", "two#room/shop");
      return 1;
    }
    else if (str == "3") {
      call_other (this_player(), "move_player", "three#room/church");
      return 1;
    }
    else if (str == "4") {
      call_other (this_player(), "move_player", "four#room/orc_vall");
      return 1;
    }
    else if (str == "5") {
      call_other (this_player(), "move_player", "five#room/plane3");
      return 1;
    }
    else { return 0; }
  }
}

order(str)
{
  string name, short_desc, mess;
  int value, cost, strength, heal;
  
  if (!str) {
    write("Order what ?\n");
    return 1;
  }
  if (str == "cerveza") {
    mess = "That feels good";
    heal = 1;
    value = 4;
    strength = 3;
  }
  else if (str == "pin~a" || str == "colada" || str == "pin~a colada") {
    mess = "You get a pleasant buzz from the drink";
    heal = 5;
    value = 25;
    strength = 4;
  }
  else if (str == "mai" || str == "tai" || str == "mai-tai") {
    mess = "A tingling feeling goes through your body";
    heal = 10;
    value = 50;
    strength = 8;
  }
  else if (str == "kahlua") {
    mess = "Your brain fragments like an eggshell, then reassembles";
    heal = 18;
    value = 100;
    strength = 10;
  }
  else if (str == "tequila" || str == "shot" || str == "tequila shot") {
    mess = "A shock wave runs through your body";
    heal = 25;
    value = 150;
    strength = 12;
  }
#ifdef this_thing_is_too_good			/* Pell */
  else if (str == "breathalyzer" || str == "test" || str == "breathalyzer test") {
    mess = "You breathe out some of the alcoholic fumes in your system";
    heal = 0;
    value = 10;
    strength = -1;
  }
#endif
  else if (str == "water") {
    mess = "Water in the desert...a great idea";
    heal = 1;
    value = 15;
    strength = 0;
  }
  else if (str == "mango" || str == "mango juice") {
    mess = "Nice, cool, and refreshing";
    heal = 6;
    value = 100;
    strength = 0;
  }
  else if (str == "perrier") {
    mess = "Not bad at all! And you thought only yuppies drank this...";
    heal = 15;
    value = 250;
    strength = 0;
  }
  else if (str == "papaya" || str == "papaya juice") {
    mess = "A pleasant sensation cools your palate";
    heal = 35;
    value = 600;
    strength = 0;
  }
  else if (str == "pineapple" || str == "pineapple juice") {
    mess = "The flavor tingles on your tongue as you sip";
    heal = 48;
    value = 750;
    strength = 0;
  }
  else if (str == "coconut" || str == "milk" || str == "coconut milk") {
    mess = "A strange but not unpleasant taste greets your tongue";
    heal = 56;
    value = 900;
    strength = 0;
  }
  else {
    write("The waiter stares at you, saying: We don't have that.\n");
    return 1;
  }

  if (call_other(this_player(), "query_money", 0) < value) {
    write("That costs " + value + " gold coins, which you don't have.\n");
    return 1;
  }
  if (strength > (call_other(this_player(), "query_level") + 2)) {
    if (strength > (call_other(this_player(), "query_level") + 5)) {
      /* This drink is *much* too strong for the player */
      say(call_other(this_player(), "query_name", 0) + " orders a " +
	  str + ", and immediately throws it up.\n");
      write("You order a " + str + ", try to drink it, and throw up.\n");
    } else {
      say(call_other(this_player(), "query_name", 0) + " orders a " +
	  str + ", and spews it all over you!\n");
      write("You order a " + str + ", try to drink it, and sputter it all over the room!\n");
    }
    call_other(this_player(), "add_money", - value);
    return 1;
  }
  if (!call_other(this_player(), "drink_alcohol", strength)) {
    write("The bartender says: I think you've had enough.\n");
    say(call_other(this_player(), "query_name", 0) + " asks for a " +
	str + " but the bartender refuses.\n");
    
    return 1;
  }
  write("You pay " + value + " coins for a " + str + ".\n");
  say(call_other(this_player(), "query_name", 0) + " sips a " + str + ".\n");
  call_other(this_player(), "add_money", - value);
  call_other(this_player(), "heal_self", heal);
  write(mess + ".\n");
  return 1;
}
