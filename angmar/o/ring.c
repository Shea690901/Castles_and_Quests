object mon;
int new_value,new_hp,new_wc,new_al,new_level,new_ac;
string new_name,new_short,new_long,type;

id(str) { return str=="ring"; }

short() {
 return "A golden ring";
}

long() {
    write("A small plain golden ring. It is totally smooth.\n");
}

init() {
 add_action("create");add_verb("create"); 
 add_action("read2");add_verb("read");
}


query_weight() { return 1; }

get() { return 1; }



query_value() { return 10000; }

reset(arg) {
 if(arg) return;
 mon=clone_object("obj/monster.talk");
}

create(str)
{
    if (str && (str != "note" && str != "treasure" && str != "monster"))
	return 0;
    if(!mon) {
     write("Fatal error\n");
     destruct(this_object());
     return 1;
    }
    type = str;
    write("The ring gets warm, and activates.\n");
    say(call_other(this_player(), "query_name") +
	" activates the ring.\n");
    write("You are now creating a new object.\n");
/*    if (call_other(this_player(), "query_level") < 20) {
	write("Something falters ...\n");
	return 1;
    }                         */
    if (type == "note") {
	write("Give the name of the file: ");
	input_to("set_note_file");
	return 1;
    }
    else if (type == "monster") {
	write("Give the name of the monster: ");
	input_to("set_monster_name");
	return 1;
    }
    write("Give the name of the object: ");
    input_to("set_new_name");
    return 1;
}

set_new_name(str)
{
    if (str == "") {
	write("Aborted\n");
	return;
    }
    new_name = lower_case(str);
    write("Give the short description of the object: ");
    input_to("set_new_short");
}

set_new_short(str)
{
    if (str == "") {
	write("Aborted\n");
	return;
    }
    new_short = str;
    write("Give the long description of the object (terminate with '**'):\n");
    input_to("set_new_long");
    new_long = 0;
}

set_new_long(str)
{
    if (str == "") {
	write("Aborted.\n");
	return;
    }
    if (str == "**") {
	write("Give the value of the object: ");
	input_to("set_new_value");
	return;
    }
    if (new_long)
	new_long = new_long + str + "\n";
    else
	new_long = str + "\n";
    input_to("set_new_long");
}

set_new_value(str)
{
    object temp;

    if (str == "") {
	write("Aborted.\n");
	return;
    }
    if (sscanf(str, "%d", new_value) == 1) {
	write("DONE.\n");
	temp = clone_object("obj/treasure");
	say(call_other(this_player(), "query_name") +
	    " has created " + new_short + ".\n");
	write("You have created " + new_short + ".\n");
	call_other(temp, "set_id", new_name );
	call_other(temp, "set_short", new_short);
	call_other(temp, "set_long", new_long);
	call_other(temp, "set_value", new_value);
	call_other(temp, "set_read", "Made by the ring of creation.\n");
	move_object(temp, this_player());
	return;
    }
    write("Bad value. Aborted.\n");
}

set_note_file(str)
{
    object t;
    if (str == "") {
	write("Aborted.\n");
	return;
    }
    t = clone_object("obj/note");
    call_other(t, "set_mess" , str);
    move_object(t, this_player());
}

set_monster_name(str)
{
    if (str == "") {
	write("Aborted.\n");
	return;
    }
    new_name = lower_case(str);
    write("Give the short description of the object: ");
    input_to("set_monster_short");
}

set_monster_short(str)
{
    if (str == "") {
	write("Aborted\n");
	return;
    }
    new_short = str;
    write("Give the long description of the object (terminate with '**'):\n");
    input_to("set_monster_long");
    new_long = 0;
}

set_monster_long(str)
{
    if (str == "") {
	write("Aborted.\n");
	return;
    }
    if (str == "**") {
	write("Give the level of the monster: ");
	input_to("set_monster_level");
	return;
    }
    if (new_long)
	new_long = new_long + str + "\n";
    else
	new_long = str + "\n";
    input_to("set_monster_long");
}

set_monster_level(str)
{
    if (str == "") {
	write("Aborted.\n");
	return;
    }
    if (sscanf(str, "%d", new_level) == 1) {
	write("Give the hit points of the monster: ");
	input_to("set_monster_hp");
	return;
    }
    write("Bad value. Aborted.\n");
}

set_monster_hp(str)
{
    if (str == "") {
	write("Aborted.\n");
	return;
    }
    if (sscanf(str, "%d", new_hp) == 1) {
	write("Give the combat factor (wc) of the monster (max 20): ");
	input_to("set_monster_wc");
	return;
    }
    write("Bad value. Aborted.\n");
}

set_monster_wc(str)
{
    if (str == "") {
	write("Aborted.\n");
	return;
    }
    if (sscanf(str, "%d", new_wc) == 1) {
	write("Give the ac of the monster: ");
	input_to("set_monster_ac");
	return;
    }
    write("Bad value. Aborted.\n");
}

set_monster_ac(str)
{
    if (str == "") {
	write("Aborted.\n");
	return;
    }
    if (sscanf(str, "%d", new_ac) == 1) {
	write("Give the alignment of the monster ( -/+ 200 ): ");
	input_to("set_monster_al");
	return;
    }
    write("Bad value. Aborted.\n");
}

set_monster_al(str)
{
    object mons;
    
    if (str == "") {
	write("Aborted.\n");
	return;
    }
    if (sscanf(str, "%d", new_al) == 1) {
	write("DONE.\n");
	call_other(mon, "set_name" , new_name );
	write("DONE id.\n");
	call_other(mon, "set_short" , new_short );
	write("DONE short.\n");
	call_other(mon, "set_long" , new_long );
	write("DONE long.\n");
	call_other(mon, "set_level" , new_level );
	write("DONE level.\n");
	call_other(mon, "set_hp" , new_hp );
	write("DONE hp.\n");
	call_other(mon, "set_wc" , new_wc );
	write("DONE wc.\n");
	call_other(mon, "set_ac" , new_ac );
	write("DONE wc.\n");
	call_other(mon, "set_al" , new_al ); 
	write("DONE al.\n");
	move_object(mon, this_player());
	write("DONE move.\n");
        write("The ring begins to glow and "+new_short+" appears.\n");
        say("The ring begins to glow and "+new_short+" appears.\n");
/*	call_other(mon, "set_enable" ,0 );  */
        mon=clone_object("obj/monster.talk");
	return;
    }
    write("Bad value. Aborted.\n");
}
