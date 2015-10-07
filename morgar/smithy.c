#include "std.h"

#undef EXTRA_INIT
#define EXTRA_INIT\
    add_action("buy"); add_verb("buy");\
    add_action("list"); add_verb("list");

ONE_EXIT("room/narr_alley", "east",
         "The smithy",
         "You are in a smithy. You can buy weapons and armour here.\n" +
         "Commands are: 'buy item', 'list',\n", 1)

buy(item) {
    if (!item)
        return 0;
    call_other("players/morgar/smithystore", "fill", 0);
    call_other("players/morgar/smithystore", "buy", item);
    return 1;
}

list(obj) {
    call_other("players/morgar/smithystore", "fill", 0);
    call_other("players/morgar/smithystore", "inventory", obj);
    return 1;
}

find_item_in_player(i)
{
    object ob;

    ob = first_inventory(this_player());
    while(ob) {
        if (call_other(ob, "id", i))
            return ob;
        ob = next_inventory(ob);
    }
    return 0;
}
