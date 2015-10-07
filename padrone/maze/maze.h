/* maze.h -- a room.h for the mirrormaze */

inherit "players/padrone/maze/maze";

#define EXTRA_INIT
#define EXTRA_RESET
#define EXTRA_LONG
#define EXTRA_NORTH
#define EXTRA_SOUTH
#define EXTRA_EAST
#define EXTRA_WEST

#define MAZE_ROOM(NORTH, SOUTH, EAST, WEST) \
\
reset(arg) { \
    EXTRA_RESET \
    if (arg) return; \
    set_light(1); north_room = NORTH; south_room = SOUTH; east_room = EAST; west_room = WEST; } \
\
init() { \
    ::init(); \
    EXTRA_INIT \
} \
\
north() { \
    EXTRA_NORTH \
    ::north(); \
    return 1; \
} \
\
south() { \
    EXTRA_SOUTH \
    ::south(); \
    return 1; \
} \
\
east() { \
    EXTRA_EAST \
    ::east(); \
    return 1; \
} \
\
west() { \
    EXTRA_WEST \
    ::west(); \
    return 1; \
}
