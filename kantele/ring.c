int worn,i;
object worn_by;

id(str) { return str == "ring"; }

init()
{
   add_action("wear"); add_verb("wear");
   add_action("heal"); add_verb("heal");
}

long()
{
   write("A small gold ring, it has a large 'K' ingraved.\n");
   write("You can also see some healing runes on it.\n");
}

short()
{
   if(worn)
      return "A small gold ring (worn)";
   return "A small gold ring";
}

query_value() { return 1000 / (i + 1); }

wear(str)
{
   if(!id(str))
      return 0;
   if(environment() != this_player())
   {
      write("You must get it first!\n");
      return 1;
   }
   if(worn)
   {
      write("You alread wear it!\n");
      return 1;
   }
   worn_by = this_player();
   call_other(this_player(), "wear", this_object());
   worn = 1;
   return 1;
}

drop(silently)
{
   if(worn)
   {
      call_other(worn_by, "stop_wearing", 0);
      worn = 0;
      worn_by = 0;
      if(!silently)
         write("You drop the ring.\n");
   }
   return 0;
}

get() { return 1; }

query_weight() { return 1; }

un_wear()
{
   if(worn)
      worn = 0;
   worn_by = 0;
}

query_name() { return "ring"; }

heal()
{
   if(i < 4)
   {
      write("You are completely healed.\n");
      i = i + 1;
      call_other(this_player(), "heal_self", 1000);
      if(i == 3)
      {
         write("The ring suddenly crumbles to dust!\n");
         this_player()->add_weight(-1);
         move_object(this_object(), "players/kantele/store");
         return 1;
      }
   }
   return 1;
}
