inherit "room/room";		/* Rewritten by Pell */
 
#define SIGN \
"To your immediate west lies the Village of the Trolls.\n" + \
"These are not garden-variety trolls. They are tough, and\n" + \
"abundant. Seriously consider teamwork to dispatch them if\n" + \
"you are of low level. Running might take you into even\n" + \
"deeper caca than before. They are damn tough. You have\n" + \
"been duly warned.\n\n" + \
"Quantos Tanthalon		   Master of DesertWorld"

init() {::init(); add_action("read", "read");}

reset(arg)
{
  if (arg) return;
  set_light(1);
  short_desc = "Northernmost part (so far) of desert";
  long_desc = 
"The middle of the desert.\n" +
"There is a new sign here.\n" +
"The dune you are on slopes down to the west, toward a small village.\n";
  items = ({"sign", SIGN});
  dest_dir = ({"players/quantos/desert/desert1", "south",
	       "players/quantos/desert/track1", "west",
	       "players/quantos/desert/mirage", "east"});
}

read(arg)
{
  if (arg == "sign") {
    long("sign");
    return 1;
  }
  notify_fail("Read what?\n");
  return 0;
}
