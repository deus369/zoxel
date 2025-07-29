#ifndef zox_game
    #define zox_game zoxel
#endif
#define str_macro(x) #x
#define inc_nexus_game(x) str_macro(nexus/x/_.c)
#define zox_nexus_game inc_nexus_game(zox_game)