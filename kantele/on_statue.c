inherit "room/room";

int eyes;
object diamond, shagath;

reset(arg)
{
   eyes = 2;
   if(arg)
      return;
   short_desc = "You are on the statue";
   long_desc = "You are on the statue. You can climb down.\n";
   set_light(1);
   dest_dir = ({"players/kantele/behind_altar","down"});
}

init()
{
   ::init();
   add_action("get_diamond", "pray");
}

get_diamond(arg)
{
   if(eyes > 0 && (arg == "of eye" || arg == "of eyes"))
   {
      eyes--;
      write("You pray of a diamond eye.\n");
      say(call_other(this_player(), "query_name") +
          " prays of a diamond eye.\n");
      diamond  = clone_object("obj/treasure");
      call_other(diamond, "set_id", "diamond");
      call_other(diamond, "set_short", "A huge glittering diamond");
      call_other(diamond, "set_weight", 1);
      call_other(diamond, "set_value", random(2000));
      call_other(diamond, "set_alias", "gem");
      move_object(diamond, this_object());
      if(random(3))
         summon_avatar();
      return 1;
   }
}

summon_avatar()
{
   object behind_altar;
   behind_altar = find_object("players/kantele/behind_altar");
   if(!behind_altar)
      return;
   if(!shagath || !living(shagath))
   {
      shagath = clone_object("obj/monster");
      call_other(shagath, "set_name", "shagath");
      call_other(shagath, "set_alias", "avatar");
      call_other(shagath, "set_level",19);
      call_other(shagath, "set_al", -300);
      call_other(shagath, "set_short", "Shagath the avatar of Kali");
      call_other(shagath, "set_wc",30);
      call_other(shagath, "set_ac",5);
      call_other(shagath, "set_aggressive", 1);
      call_other(shagath, "set_chance",40);
      call_other(shagath, "set_spell_mess1",
                 "Shagath throws Hellfire at you.");
      call_other(shagath, "set_spell_mess2",
                 "You are hit by the Hellfire");
      call_other(shagath, "set_spell_dam",60);
      move_object(shagath, behind_altar);
   }
   write("You are shaken down from the statue !\n");
   this_player()->move_player("X", behind_altar);
   tell_room(behind_altar, "The Whole Temple shakes. You can feel the Wrath of Kali!\n");
   tell_room(behind_altar, "Shagath the avatar of Kali arrives in a puff of smoke!\n");
}
