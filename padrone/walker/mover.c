/* players/padrone/walker/mover.c
 *  -- the invisible monster that does the walking for the walking castle.
 *  She also repeats everything that happens in the room,
 *  so it can be sen on the bridge!
 */

#include "walker.h"

inherit "obj/monster";
add_money(m) { money = money + m; }     /* Without add_worth! */

reset(arg) {
    ::reset(arg);

    if (!arg) {
	/* First reset */
	set_name("invisible castle mover");
	set_alias("icm");
        set_level(1);
        set_female();
        set_al(0);
        set_short(0);
        set_long("She is invisible and moves the castle. Don't touch her!\n");
        set_aggressive(0);
	set_spell_mess1("Invisible castle mover says: This is utterly ludicrous. Go away!");
	set_spell_mess2("Invisible castle mover says: This is utterly ludicrous. Go away!");
	set_chance(15);
	set_spell_dam(0);

	is_invis = 1;	/* Invisible. */

	/* Monsters and players CAN attack it! */
        set_hp(1000000);
        set_ac(1000000);
    }
} /* reset */

come_here() {
    move_object(this_object(), call_other(CASTLE, "query_environment"));
} /* come_here */

query_environment() {
    return environment(this_object());
}

catch_tell(str) {
    call_other(CASTLE, "tell_bridge", str);
}
