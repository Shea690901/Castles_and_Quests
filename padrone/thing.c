/*
 *   A thing. It can be read, either with a fixed message or a file.
 *   Thomas Padron-McCarthy, padrone@lysator.liu.se, 1990
 *	Clone this object to get a generic thing, then use set_name,
 *	and (optional) set_alias, set_short, set_long, set_read, set_read_file,
 *      set_can_get, set_weight and set_value.
 *   Latest update: January 20, 1991
 */

string name, alias_name, short_desc, long_desc, read_message, read_file;
status can_get;
int weight, value;

short() {
    return short_desc;
}

long() {
    if (long_desc)
	write(long_desc);
    else if (read_file || read_message)
	read(name);
    else
	write("You see nothing special.\n");
}

reset(arg) {
    if (arg)
	return;
    set_name("thing");
    long_desc = 0;	/* Use read() if no long_desc set! */
    can_get = 1;
    read_message = 0;
    read_file = 0;
    weight = 1;
    value = 1;
}

init() {
    add_action("read", "read");
}

id(str) {
    return str == name || str == alias_name;
}

read(str) {
    if (!id(str))
	return 0;
    else if (!read_file && !read_message)
	return 0;
    else {
	say(this_player()->query_name() + " reads the " + name + ".\n");
        if (read_file)
	    cat(read_file);
	else
	    write(read_message);
	return 1;
    }
} /* read */

get() {
    return can_get;
}

query_name() { return name; }
query_weight() { return weight; }
query_value() { return value; }

set_name(n) { name = n; short_desc = capitalize(n); }
set_short(sh) { short_desc = sh; }
set_long(long) { long_desc = long; }
set_read(str) { read_message = str; }
set_read_file(filename) { read_file = filename; }
set_weight(w) { weight = w; }
set_value(v) { value = v; }
set_alias(n) { alias_name = n; }
set_can_get(n) { can_get = n; }
