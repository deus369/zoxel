/*
 *  Zox Input
 *
 *      - defines base types for device handling
 *      - emulates state changes of physical devices
 *
 *  todo:
 *
 *      - refactor keyboard as a list of keys
 *
 * */
#ifndef zox_mod_inputs
#define zox_mod_inputs

#include "data/data.c"
#include "components/components.c"
#include "util/util.c"
#include "prefabs/prefabs.c"
#include "systems/systems.c"

void module_dispose_inputs(ecs_world_t *world, void *ctx) {
    dispose_hook_key_down();
}

zox_begin_module(Inputs)
    zox_module_dispose(module_dispose_inputs)
    initialize_hook_key_down();
    define_components_inputs(world);
    define_systems_input(world);
    spawn_prefabs_inputs(world);
zox_end_module(Inputs)

#endif