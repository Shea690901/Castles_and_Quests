/* Daemon that maintains the weather */
/* fails miserably */
/* weather goes from 0-36 = hot and sunny to big storm */
/* the statistical distribution is 1/f noise which should 
   match real weather, sort of. */
/* values:
   0 very hot and humid
   1 very hot and sunny
   2 hot and humid
   3 hot and sunny
   4 very warm and sunny
   5 warm and sunny
   6 warm and humid
   7 warm and sunny
   8 sunny
   9 pleasantly cool and sunny
  10 pleasantly cool, but sunny
  11 cool, but sunny
  12 pleasantly cool
  13 cool
  14 chilly
  15 very chilly
  16 cold
  17 ice cold
  18 frigid
  19 misty
  20 foggy
  21 drizzling
  22 sprinkling
  23 raining
  24 rainy
  25 a downpour
  26 raining very hard
  27 sleeting
  28 raining extremely hard
  29 stormy
  30 very stormy
  31 extremely stormy
  32 hailing
  33 hailing hard
  34 hailing very hard
  35 hurricane
  36 large hurricane
*/

int c1, c2, c3, c4, c5, w1, w2, w3, w4, oldweather, currentweather;

reset(arg)
{
    if (arg)
        return;
    set_heart_beat(1);
    say("We now have weather!\n");
    c1=random(8);
    c2=random(8);
    c3=random(8);
    c4=random(8);
    c5=random(8);
    w1=random(10);
    w2=random(10);
    w3=random(10);
    w4=random(10);
    oldweather=w1+w2+w3+w4;
    currentweather=w1+w2+w3+w4;
}

short() {
    return "A weather daemon";
}

long() {
    return ("A very strange daemon.\n" +
    "It just sits here, controlling the weather.\n");
}

id(str) { return str == "daemon"; }

heart_beat()
{
    if (c1 == 0) {
        c1=20;
        oldweather=w1+w2+w3+w4;
        if (c2 == 0) {
            c2=8;
            if (c3 == 0) {
                c3=8;
                if (c4 == 0) {
                    c4=8;
                    if (c5 == 0) {
                        c5=8;
                        w4=random(10);
		    }
                    c5=c5-1;
		    w3=random(10);
		}
                c4=c4-1;
                w2=random(10);
	    }
            c3=c3-1;
            w1=random(10);
	}
        c2=c2-1;
        currentweather=w1+w2+w3+w4;
        if (oldweather == currentweather) {
            say("It is still ");
        } else {
            say("It is now ");
        }
        if (currentweather ==  0) { say("very hot and humid"); } else
        if (currentweather ==  1) { say("very hot and sunny"); } else
        if (currentweather ==  2) { say("hot and humid"); } else
        if (currentweather ==  3) { say("hot and sunny"); } else
        if (currentweather ==  4) { say("very warm and sunny"); } else
        if (currentweather ==  5) { say("warm and very humid"); } else
        if (currentweather ==  6) { say("warm and humid"); } else
        if (currentweather ==  7) { say("warm and sunny"); } else
        if (currentweather ==  8) { say("sunny"); } else
        if (currentweather ==  9) { say("pleasantly cool and sunny"); } else
        if (currentweather == 10) { say("pleasantly cool, but sunny"); } else
        if (currentweather == 11) { say("cool, but sunny");  } else
        if (currentweather == 12) { say("pleasantly cool"); } else
        if (currentweather == 13) { say("cool"); } else
        if (currentweather == 14) { say("chilly"); } else
        if (currentweather == 15) { say("very chilly"); } else
        if (currentweather == 16) { say("cold");  } else
        if (currentweather == 17) { say("ice cold"); } else
        if (currentweather == 18) { say("frigid"); } else
        if (currentweather == 19) { say("misty"); } else
        if (currentweather == 20) { say("foggy"); } else
        if (currentweather == 21) { say("drizzling"); } else
        if (currentweather == 22) { say("sprinkling"); } else
        if (currentweather == 23) { say("raining"); } else
        if (currentweather == 24) { say("rainy"); } else
        if (currentweather == 25) { say("a downpour"); } else
        if (currentweather == 26) { say("raining very hard"); } else
        if (currentweather == 27) { say("sleeting"); } else
        if (currentweather == 28) { say("raining extremely hard"); } else
        if (currentweather == 29) { say("stormy"); } else
        if (currentweather == 30) { say("very stormy"); } else
        if (currentweather == 31) { say("extremely stormy"); } else
        if (currentweather == 32) { say("hailing"); } else
        if (currentweather == 33) { say("hailing hard"); } else
        if (currentweather == 34) { say("hailing very hard"); } else
        if (currentweather == 35) { say("hurricane"); } else
        if (currentweather == 36) { say("large hurricane"); }
        say(".\n");
    }
    c1=c1-1;
}

query_weather() {
    return currentweather;
}
