// Use these for custom adding zox modules to your flecs projects!!
// todo: make a md file about this use, start a blog like sanders?

// module core functions
#ifndef zox_game
    // includes default game
    #define zox_game zoxel
#endif
// #define capitalize_first(s) (toupper((s)[0]) + (s) + 1)
#define str_macro(x) #x
#define inc_nexus_game(x) str_macro(nexus/x/x.c)
#define zox_nexus_game inc_nexus_game(zox_game)

#define inc_nexus_defines(x) str_macro(../nexus/x/defines.c)
#define zox_nexus_defines inc_nexus_defines(zox_game)

// for custom builds people can include these
#ifndef zox_custom_build

#define zox_include_zero    // core, basics
    #define zox_include_transforms

#define zox_include_one     // builds on core
    #define zox_include_physics

#define zox_include_two     // users
    #define zox_include_stats
    #define zox_include_skills
    #define zox_include_items
    #define zox_include_actions

#define zox_include_three   // gameplay
    // for sub modules
    #define zox_include_characters

#define zox_include_four    // space

#endif
