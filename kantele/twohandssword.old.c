status wielded;
string wielded_by;
string name_of_weapon;
string alt_name;
int class_of_weapon;
int value;
int local_weight;
    string who;
object kill_ob;


query_name() { return "twohandsword"; }

long() { write("The Twohandsword is covered with black runes.\n"); }

reset(arg)
{
   if(arg)
      return;
   wielded = 0;
   value = 0;
}

init()
{
   add_action("wield"); add_verb("wield");
   add_action("magic"); add_verb("fireball");
   add_action("magic"); add_verb("shock");
   add_action("magic"); add_verb("missile");
   add_action("magic"); add_verb("heal");
   add_action("magic"); add_verb("whimpy");
   add_action("not_quit"); add_verb("quit");
}

wield(str)
{
   if(!id(str))
      return 0;
   if(environment() != this_player())
   {
      write("You must get it first!\n");
      return 1;
   }
   if(wielded)
   {
      write("You already wield it!\n");
      return 1;
   }
   wielded_by = this_player();
   call_other(this_player(), "wield", this_object());
   wielded = 1;
   return 1;
}

short()
{
   if(wielded)
      return "twohandsword (wielded)";
   return "twohandsword";
}

weapon_class() { return 26; }

id(str) { return str == "twohandsword" || str == "sword"; }

drop(silently)
{
   if(wielded && (call_other(this_player(), "query_level", 0) < 20))
   {
      write("The sword don't want to be dropped !\n");
      return 1;
   }
}

un_wield()
{
   if(wielded)
      wielded = 0;
}

set_class() { class_of_weapon = 30; }

magic()
{
   if(call_other(this_player(), "query_level", 0) > 20)
      return 0;
   write("The Sword doesn't like magic, You are jolted by an electric shock !\n");
   call_other(this_player(), "hit_player", 15);
   return 1;
}

set_name() { name_of_weapon ="twohandsword"; }
query_value() { return 0; }
set_value() { value = 0; }
query_weight() { return 4; }
set_weight() { local_weight = 5; }
get() { return 1; }
set_alt_name() { alt_name = "sword"; }

not_quit()
{
   if(call_other(this_player(), "query_level", 0) > 20)
      return 0;
   else
   {
      write("You can't wimp out now ! HAR.HAR");
      return 1;
   }
}
