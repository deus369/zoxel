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
#ifndef zoxm_inputs
#define zoxm_inputs

#include "data/_.c"
#include "components/_.c"
#include "util/_.c"
#include "prefabs/_.c"
#include "systems/_.c"

void module_dispose_inputs(ecs *world, void *ctx) {
    (void) world;
    (void) ctx;
    dispose_hook_key_down();
}

zox_begin_module(Inputs)
    zox_module_dispose(module_dispose_inputs);
    initialize_hook_key_down();
    define_components_inputs(world);
    define_systems_input(world);
    add_hook_spawn_prefabs(spawn_prefabs_inputs);
zox_end_module(Inputs)

#endif