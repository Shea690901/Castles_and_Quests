/* #include "std.h" /Pell */

object sitter;			/* Pell */

reset (arg) {
    if(!arg) {
	set_light(1);
	sitter = 0;		/* Pell */
    }
}

init() {
    add_action ("west"); add_verb ("west");
    add_action ("east"); add_verb ("east");
    add_action ("south"); add_verb ("south");
    add_action ("down"); add_verb ("down");
    add_action ("down"); add_verb ("north");
    add_action ("sit"); add_verb ("sit"); /* Pell */
}

sit(w)				/* "sit" by Pell */
{
  if (!w || w == "table" || w == "at table" || w == "on table") {
    write("You sit down and enjoy the desert scenery. You feel very\n");
    write("calm and relaxed. You get up after a while.\n");
    say(this_player()->query_name() + " sits on the table for a while.\n");
    if (sitter != this_player()) { /* Refresh her/him/it, but only once */
      sitter = this_player();	/* This *could* be exploited by two smart */
      sitter->heal_self(5);	/* players, but... Oh, well. */
    }
    return 1;
  }
  notify_fail("Sit on what?\n");
  return 0;
}

west() {
    call_other (this_player(), "move_player", "west#players/quantos/plateau/nwplat");
    return 1;
}

east() {
    call_other (this_player(), "move_player", "east#players/quantos/desert/track3");
    return 1;
}

south() {
    call_other (this_player(), "move_player", "south#players/quantos/plateau/plat");
    return 1;
}

down() {
    call_other (this_player(), "move_player", "down#players/quantos/desert/vall1");
    return 1;
}

id(str) { return str == "table"; } /* Pell */

long(str) {
    if (str == "table")		/* Pell */
      write("A small, low table of rock. Try to relax and enjoy the scenery.\n");	/* Pell */
    else {			/* Pell */
      write ("You are on the northernmost part of the plateau.\n");
      write ("From here, the plateau slopes downward to the north into a wide\n");
      write ("valley, and extends east into a track towards the village.\n\n");
      write ("There is a small low table of rock here for you to sit upon\n");
      write ("while you enjoy the desert scenery and warm air.\n");
    }				/* Pell */
}

short() {
    return "North plateau";
}
