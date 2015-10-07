string hatname;
int saystate;

id(str) { return ((str == "hat") || (str == "ND") || (str == hatname)); }

short() { return hatname; }

query_value() { return 1; }

long() { write("This is the "+hatname+" for a wizard.\n"); }

init() { if (call_other(this_player(), "query_level") > 20) {
        add_action("list_uses"); add_verb("use");
        add_action("charm_it"); add_verb("charm");
        add_action("remove_charm"); add_verb("free");
        add_action("set_charm"); add_verb("command"); }
        add_action("gag_it"); add_verb("gag");
        add_action("remove_gag"); add_verb("rgag");
        add_action("rename_hat"); add_verb("hatname");
        add_action("zap"); add_verb("zap");
        add_action("stats"); add_verb("stat");
        add_action("set_say"); add_verb("quotes");
        saystate=0;
}

list_uses(arg) {
    if (!id(arg)) return 0;
    write("Use:        list uses.\n");
    write("Charm:      charm a living thing.\n");
    write("Free:       uncharm a living thing.\n");
    write("Command:    tell a charmed thing to follow something.\n");
    write("Gag:        keep a player from shouting.\n");
    write("Rgag:       remove a gag from a player.\n");
    write("Zap:        silently zap a monster.\n");
    write("Stat charm: see someone's charm status.\n");
    write("Quotes:     turn on say with echo and quotes.\n");
}

reset(arg) {
    if(arg) return;
    hatname="Pointy Hat";
}

init_arg(arg) { hatname=arg; }

rename_hat(arg) { hatname=arg; return 1; }

gag_it(str) {
    object liv, ob;
    liv = find_living(str);
    if (!liv) {
        write("Can't find "+str+".\n");
        return 1;
    }
    if (call_other(liv, "query_level") >= call_other(this_player(),
          "query_level")) {
        write("You are not allowed to do that!\n");
        return 1;
    }
    ob = present("throat", liv);
    if (ob) {
        write(str + " already has a sore throat.\n");
        return 1;
    }
    ob = clone_object("players/morgar/throat");
    transfer(ob,liv);
    tell_object(liv, "You suddenly, without any reason, get a sore throat.\n");
    write("Done.\n");
    return 1;
}

remove_gag(str) {
    object liv, ob;
    liv = find_living(str);
    if (!liv) {
        write("Can't find "+str);
        return 1;
    }
    if (call_other(liv, "query_level") >= call_other(this_player(),
          "query_level")) {
        write("You are not allowed to do that!\n");
        return 1;
    }
    ob = present("throat", liv);
    if (!ob) {
        write(str + " has no sore throat.\n");
        return 1;
    }
    tell_object(liv, "Your throat feels better now.\n");
    transfer(ob, environment(liv));
    write("Done.\n");
    destruct(ob);
    return 1;
}

charm_it(str) {
    object liv, ob;
    liv = find_living(str);
    if (!liv) {
        write("Can't find "+str+".\n");
        return 1;
    }
    ob = present("charm", liv);
    if (ob) {
        write(str + " is already charmed.\n");
        return 1;
    }
    ob = clone_object("players/morgar/charm");
    transfer(ob,liv); /* may want to tell them.  Nahhh. */
    write("Charm done.\n");
    return 1;
}

remove_charm(str) {
    object liv, ob;
    liv = find_living(str);
    if (!liv) {
        write("Can't find "+str+"\n");
        return 1;
    }
    ob = present("charm", liv);
    if (!ob) {
        write(str + " is not charmed.\n");
        return 1;
    } /* don't tell them, of course */
    transfer(ob, environment(liv));
    write("Free done.\n");
    destruct(ob);
    return 1;
}

set_charm(str) {
    object liv, ob, targ;
    string livstr, targstr;
    if (sscanf(str,"%s follow %s",livstr,targstr) != 2) {
        write("Bad syntax.\n");
        return 1;
    }
    liv = find_living(livstr);
    if (!liv) {
        write("Can't find "+livstr+"\n");
        return 1;
    }
    targ = find_living(targstr);
    if (!targ) {
        write("Can't find "+targstr+"\n");
        return 1;
    }
    ob = present("charm", liv);
    if (!ob) {
        write(str + " is not charmed.\n");
        return 1;
    } /* don't tell them, of course */
    call_other(ob, "startfollow", targstr);
    write("Command done.\n");
    return 1;
}

get() {
   if(call_other(this_player(), "query_level") > 20) {
       return 1;
       }
   write("The "+hatname+" is too heavy to get.\n");
   say(call_other(this_player(), "query_name") + " fails to get the "
       + hatname + ".\n");
   return 0;
}

drop() { return 1; }

query_auto_load() {
    return("players/morgar/hat:"+hatname);
}

zap(str) {
    object liv, ob;
    liv = find_living(str);
    if (!liv) {
        write("Can't find "+str+".\n");
        return 1;
    }
    if (call_other(liv, "query_npc") != 1) {
        write("Don't zap players!\n");
        return 1;
    }
    call_other(liv,"hit_player",100000);
    write("Modified zap done.\n");
    return 1;
}

stats(arg) {
    string name,checkstr;
    object liv,ob;
    name=call_other(this_player(),"query_real_name",0);
    checkstr="charm";
    if(arg!="charm" && sscanf(arg,"%s %s",checkstr,name)==0) {return 0;}
    if (checkstr != "charm") {return 0;}
    liv = find_living(name);
    if (!liv) {
        write("Can't find "+name+".\n");
        return 1;
    }
    ob = present("charm", liv);
    if (!ob) {
        write(name + " is not charmed.\n");
        return 1;
    } /* don't tell them, of course */
    call_other(ob, "query_stats", 0);
    return 1;
}
set_say(arg) {
    if (arg != "on") {
        if (arg != "off") {return 0;}
        if (saystate==0 || saystate==2) {
            write ("Quotes are already off.\n");
            return 1;
        }
        saystate=2;
        write("Quotes turned off.\n");
        return 1;
    }
    if (saystate==1) {
        write("Quotes are already on.\n");
        return 1;
    }
    if (saystate==0) {
        add_action("talk"); add_verb("say");
    }
    write ("Quotes turned on.\n");
    saystate=1;
    return 1;
}

talk(str) {
    if (saystate != 1) {return 0;}
    if (str==0) {
        say(call_other(this_player(),"query_name",0)+" has nothing to say.\n");
        write("You have nothing to say.\n");
        return 1;
    }
    say(call_other(this_player(),"query_name",0)+" says \""+str+"\"\n");
    write("You say \""+str+"\"\n");
    return 1;
}
