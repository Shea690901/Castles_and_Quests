	elemental = clone_object ("obj/monster");
	call_other (elemental, "set_name", "elemental");
	call_other (elemental, "set_alias", "fire elemental");
	call_other (elemental, "set_race", "elemental");
	call_other (elemental, "set_short", "A fire elemental");
	call_other (elemental, "set_level", 15);
	call_other (elemental, "set_hp", 250);
	call_other (elemental, "set_wc", 16);
	call_other (elemental, "set_al", -250);
	call_other (elemental, "set_aggressive", 1);
	move_object (elemental, this_object());

