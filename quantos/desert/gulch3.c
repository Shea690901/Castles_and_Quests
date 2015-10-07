#include "std.h"

#undef EXTRA_LONG
#define EXTRA_LONG \
write("The gulch tapers off to an end here, and slopes up to the west\n" +\
      "onto an expansive plateau. Squinting, you see some type of\n" +\
      "building far to the west. The forest seems to be far away now.\n\n" +\
      "You see light scrub plants around you, and the occasional jackrabbit\n" +\
      "bolts from hiding to escape the trod of your boots. A rusted green\n" +\
      "sign in the brush to your left reads 'Alamogordo  43 Miles'.\n\n" +\
      "To the right, a newly-erected sign reads:\n\n" +\
      "                     D A N G E R !\n" +\
      "                     -------------\n" +\
      "This plateau contains old, abandoned mineshafts which are NOT\n" +\
      "obvious to the untrained eye. If you want to stay healthy,\n" +\
      "WATCH WHERE YOU STEP. The management takes No responsibility\n" +\
      "for injuries sustained during the exploration of the plateau,\n" +\
      "and warns all patrons that if they should fall into one of\n" +\
      "these shafts, they will need a light source, and NO WIZARDS\n");


TWO_EXIT ("players/quantos/desert/gulch2", "east",
	  "players/quantos/plateau/plat", "west",
	  "West gulch: Read the sign or face the consequences!!!!!",
	  "will help to extricate them. YOU HAVE BEEN DULY WARNED.\n", 1)
