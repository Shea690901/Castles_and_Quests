/* #include "std.h" /Pell */

reset (arg) {
  if(!arg)
    set_light(1);
  extra_reset();
}

extra_reset () {
  object money, troll, weapon;
  int i;
  
  i = 0;
  if (!present ("troll")) {
    while (i<3) {
      i += 1;
      troll = clone_object ("obj/monster");
      call_other (troll, "set_name", "troll");
      call_other (troll, "set_alias", "blacktroll");
      call_other (troll, "set_race", "troll");
      call_other (troll, "set_level", 12);
      call_other (troll, "set_hp", 140);
      call_other (troll, "set_ep", 175000);
      call_other (troll, "set_al", -125);
      call_other (troll, "set_short", "A black troll");
      call_other (troll, "set_long",
		  "It is a hideously ugly troll. with coruscating sparks of electricity\n" +
		  "    cascading off its mottled hide.\n");
      call_other (troll, "set_aggressive", 1);
      call_other (troll, "set_wc", 15);
      call_other (troll, "set_ac", 4);
      call_other (troll, "set_spell_mess1",
		  "The troll throws lightning!");
      call_other (troll, "set_spell_mess2",
		  "The troll hurls a bolt of electricity at you!");
      call_other (troll, "set_chance", 18);
      call_other (troll, "set_spell_dam", 20);
      move_object (troll, this_object());
      money = clone_object ("obj/money");
      call_other (money, "set_money", random (600)); /* Was 1200 /Pell */
      move_object (money, troll);
    }
  }
}

init() {
  add_action ("west"); add_verb ("west");
  add_action ("east"); add_verb ("east");
  add_action ("south"); add_verb ("south");
}

west() {
  call_other (this_player(), "move_player", "west#players/quantos/desert/track3");
  return 1;
}

east() {
  call_other (this_player(), "move_player", "east#players/quantos/desert/village");
  return 1;
}

south() {
  write ("You would not survive the fall to the bottom of the gulch.\n");
  return 1;
}

long() {
  write ("You are on a track just west of the troll village. The path\n");
  write ("leads east and west. To the south is a long gulch.\n");
}

short() {
  return "Village track (west)";
}
