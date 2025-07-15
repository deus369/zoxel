#ifndef zox_game
    // includes default game
    #define zox_game zoxel
#endif
#define str_macro(x) #x
#define inc_nexus_game(x) str_macro(nexus/x/x.c)
#define zox_nexus_game inc_nexus_game(zox_game)

// #define inc_nexus_defines(x) str_macro(nexus/x/defines.c)
// #define zox_nexus_defines inc_nexus_defines(zox_game)