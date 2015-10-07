/* #include "std.h" /Pell */

reset (arg) {
    if(!arg)
	set_light(1);
}

long() {
    write ("You are standing at the outer perimeter of the city.\n");
    write ("Looking in at what you once believed might be a great metropolis,\n");
    write ("you realize that whatever happened here must have been cataclysmic.\n");
    write ("Despite the sheer numbers of buildings and lanes between them,\n");
    write ("you realize that there are *no human inhabitants* to be seen.\n");
    write ("In fact, staring down the streets, you note that the signs of\n");
    write ("are very few, consisting of crows and cats running about and\n");
    write ("scavenging bits of meat from the carcass of some unfortunate\n");
    write ("animal. Clouds of flies swarm about the cloying, decaying flesh\n");
    write ("The sight and smell make you wish you had delayed eating lunch\n");
    write ("a little longer....\n\n");
    write ("Looking around you, you notice a road leading north (NOT OPEN)\n");
    write ("into the city, as well as a rusted colorful sign to your left.\n");
    write ("In fancy script, the sign (what you can read of it,anyway) says\n");
    write ("'WE   M  T  L S  EG S'. A cryptic message at best.\n");
}

short() {
    return "Cibola city limits";
}

cab_arrives()			/* Pell */
{
  say("A cab arrives and stops to a screeching halt.\n");
}
