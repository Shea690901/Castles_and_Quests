/* This room was completely refurbished /Pell */
inherit "room/room";

reset(arg)
{
  if (arg) return;
  
  set_light(1);
  short_desc = "Desert entrance";
  long_desc = 
"The entrance to the desert. There are few trees here.\n" +
"You see vultures circling high overhead. The sun beats down\n" +
"like a suffocating weight. You can see some kind of dwellings\n" +
"through the heat to the northwest.\n";
  items = ({"tree", "A small tree, clinging to some last shreads of soil",
	    "trees", "A sparse collection of dried-out trees"});
  dest_dir = ({"room/forest2", "south",
	       "players/quantos/desert/desert1", "north"});
}
