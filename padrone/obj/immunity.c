/* Padrone's invisible object for some special purposes */

id(str) { return str=="no scare"; }     /* Dz's scare scroll */

/* If the monster dies, don't leave this object in the corpse! */
drop() { call_out("go_away", 1); return 0; }
go_away() { destruct(this_object()); }
