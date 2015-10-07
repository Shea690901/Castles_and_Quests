#include "std.h"

#undef EXTRA_INIT
#define EXTRA_INIT extra_init();

FOUR_EXIT("room/clearing","north",
	 "players/morgar/base", "east",
	 "room/post", "south",
         "players/morgar/store", "up",
	 "Morgar's workroom",
	 "This is where Morgar works on strange new projects.\n", 1)

extra_init() {
    add_action("torch"); add_verb("torch");
    add_action("cash"); add_verb("cash");
}

torch() {
    object torch;
    torch = clone_object("obj/torch");
    call_other(torch, "set_name", "torch");
    call_other(torch, "set_fuel",9999);
    call_other(torch, "set_weight", 1);
    move_object(torch, this_object());
    return 1;
}

cash(arg) {
    object money;
    int amount;
    amount=1000000;
    money = clone_object("obj/money");
    call_other(money, "set_money",amount);
    move_object(money,this_object());
    return 1;
}
