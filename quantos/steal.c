steal()
{
    object ob, who;
    int weight;

    who = this_player();
    while(who) {
	if (who != this_object() && living(who)) {
	    ob = first_inventory(who);
	    if (ob == 0)
		return;
	    else if (ob == this_object()) {
		ob = next_inventory(who);
		return;
	    }
	    weight = call_other(ob, "query_weight");
	    if (!add_weight(weight))
		return;
	    call_other(ob, "drop");
	    call_other(who, "add_weight", -weight);
	    move_object(ob, this_object());
	    return;
	}
	who = next_inventory(who);
    }
}
