// module core functions

void dispose_zox(ecs_world_t *world) {
    dispose_space(world);
    dispose_inner_core(world);
    dispose_game_store();
    dispose_core(world);
}

unsigned char initialize_zox(ecs_world_t *world) {
    if (initialize_core(world) == EXIT_FAILURE) return EXIT_FAILURE;
    initialize_inner_core(world);
    initialize_outer_core(world);
    initialize_space(world);
    return EXIT_SUCCESS;
}

void spawn_prefabs_engine(ecs_world_t *world) {
    spawn_prefabs_core(world);
    spawn_prefabs_inner_core(world);
    spawn_prefabs_outer_core(world);
    spawn_prefabs_users(world);
    spawn_prefabs_gameplay(world);
    spawn_prefabs_space(world);
}

// #includes nexus game
// for now we do this until we can control flecs module names
#ifndef zox_game_module
    #define zox_game_module Zoxel
#endif
#define capitalize_first(s) (toupper((s)[0]) + (s) + 1)
#define str_macro(x) #x
#define inc_nexus_game(x) str_macro(../../nexus/x/x.c)
#include inc_nexus_game(zox_game)

// temp fix for now while it is forcefully capitalized
void zox_import_game_module() {
    zox_import_module(zox_game_module)
}
