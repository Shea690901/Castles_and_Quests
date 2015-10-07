inherit "room/room";

reset(arg) {
  if (!arg){
    set_light(1);
    short_desc = "In the dragon's cave";
    no_castle_flag = 0;
    long_desc = 
        "This is where the great dragon lives and hoards his treasures.\n";
    dest_dir = 
        ({
        "players/angmar/fairyland/tunnel", "south",
        });
    items = 
        ({
        "treasures", "The usual things a dragon collects over a lifetime",
        });
  }
  if(!present("dragon", this_object())){
    object diamond,dragon,chainmail;
    dragon=clone_object("obj/monster");
    call_other(dragon,"set_name","dragon");
    call_other(dragon,"set_level",18);
    call_other(dragon,"set_hp",700); /* 250 Guru: A hardy dragon */
    call_other(dragon,"set_wc",35); /* 20 Guru: I think dragons are tough!! */
    call_other(dragon,"set_ac",17); /* 5 Guru: Needs good protection */
    call_other(dragon,"set_al",-200);
    /* Guru: Changed the description a bit to warn players */
    call_other(dragon,"set_short","A large ferocious red dragon");
    call_other(dragon,"set_long",
	       "A huge dragon. His name is Smaug and is rumoured to be the last.\n"+
	       "of his kind. When you see him you really hope so. He looks like\n" +
	       "he usually eat folks like you whole, and that his intent is to\n"+
	       "prove it to you rather soon. He gives you a gaze that could\n"+
	       "melt stone.  Fumes come out of his nostrils in a way that\n"+
	       "makes you feel that this dragon is sure of himself. He has NO\n" +
	       "thoughts about losing a battle. His scars make you realize why.\n"+
	       "The feeling his gaze inflicts in you gives you an insight in the\n"+
	       "term \"premonition\".\n");
    call_other(dragon,"set_alias","smaug");
dragon->set_male();
    call_other(dragon,"set_spell_mess1","The dragon breathes fire!");
    call_other(dragon,"set_spell_mess2","The dragon breathes fire at you!");
    call_other(dragon,"set_chance",30);
    call_other(dragon,"set_spell_chance",60); /* 30 Guru */
    call_other(dragon,"set_spell_dam",23);
    
    diamond=clone_object("players/angmar/o/platinum_ring");
    move_object(diamond,dragon);
    
    chainmail=clone_object("obj/armour");
    call_other(chainmail,"set_name","chainmail");
    call_other(chainmail,"set_short","mithril chainmail");
    call_other(chainmail,"set_long",
	       "It looks very light.\n");
    call_other(chainmail,"set_alias","mithril chainmail");
    call_other(chainmail,"set_value",3000);
    call_other(chainmail,"set_weight",6);
    call_other(chainmail,"set_ac",4);
    call_other(chainmail,"set_type","armour");
    move_object(chainmail,dragon);
    move_object(dragon,this_object());
  }
}

query_light() {
    return 1;
}

realm()
{
  return ("fairyland");
}

query_inorout() { return 1; }
