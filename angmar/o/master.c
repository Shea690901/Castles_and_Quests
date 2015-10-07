#define MAXPHONES 40

string cap_name;
object phonearray;
int phonenr;

reset(arg) {
  if(arg) return;
  phonenr=0;
  phonearray=allocate(40);
}

query_weight() { return 200; }
query_value() { return 0; }
short() { return "The master-palantir"; }
get() { return 1; }
long() { 
  write("It is a large spherical crystal ball. This is the communication-\n");
  write("center for all other palantirs. You probably couldn't lift it.\n");
}

init() {
  cap_name=this_player()->query_name();
/*  if(cap_name!="Angmar") return; */
  add_action("phone"); add_verb("palantir");
  add_action("phonebook"); add_verb("palantirs");
  add_action("get_creat"); add_verb("creator");
}

id(str) { return str== "master-palantir" || str=="palantir"; }

get_creat() {
  object creat;
  creat=clone_object("players/angmar/o/creator");
  creat->set_master(this_object());
  move_object(creat,this_player());
  write("Ok.\n");
  say(this_player()->query_name()+" makes some magical gestures.\n");
  return 1;
}

phone() {
  object phone;
  int nr;

  nr=0;
  while(nr<MAXPHONES && phonearray[nr]) {
    nr+=1;
  }

  if(phonenr+1>=MAXPHONES) {
    write("Out of memory.\n");
    return 1;
  }
  phone=clone_object("players/angmar/o/palantir");
  phone->set_nr(100+nr);
  phone->set_station(this_object());
  phonearray[nr]=phone;
  move_object(phone,this_player());
  if(nr==phonenr) phonenr+=1;
  write("You speak a magic word and suddenly a palantir appears in\n"+
	"your hands.\n");
  say(this_player()->query_name()+
	" speaks a magic word, and suddenly a palantir appears in\n"+
      "his hands.\n");
  return 1;
}

dial_up(nr) {
  nr-=100;
  if(nr<0 || nr>=phonenr) return 0;
  tell_object(environment(),
	      "Many-coloured mist is swirling in the master-palantir. Someone\n"+
	      "must be using it.\n");
  tell_room(environment(),
	      "Many-coloured mist is swirling in the master-palantir. Someone\n"+
	      "must be using it.\n");

  return(phonearray[nr]);
}

phonebook() {
  int nr;
  nr=0;
  while(nr<phonenr) {
    if(phonearray[nr]) {
      write(nr+100);
      write(": ");
      write(environment(phonearray[nr])->short());
      write("\n");
    }
    nr+=1;
  }
  return 1;
}

