/* This room was completely refurbished /Pell */
inherit "room/room";

reset(arg)
{
  if (arg) return;
  
  set_light(1);
  short_desc = "Middle of gulch";
  long_desc = 
"You are in the middle of a long desert gulch. There is a skull\n" +
"of some manner of cattle half-buried in the sand here, but it\n" +
"cannot be obtained.\n";
  items = ({"skull", "A skull from some cattle, buried in the sand"});
  dest_dir = ({"players/quantos/desert/gulch1", "east",
	       "players/quantos/desert/gulch3", "west"});
}
