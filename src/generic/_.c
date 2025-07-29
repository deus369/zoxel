#ifndef zox_mod_generic
#define zox_mod_generic

#include "components/_.c"
#include "data/_.c"
#include "macros/names.c"
#include "util/_.c"
#include "prefabs/generic_event.c"
#include "systems/_.c"

void dispose_generic(ecs_world_t *world, void *ctx) {
    dispose_component_ids();
}

void spawn_prefabs_generic(ecs_world_t *world) {
    spawn_prefab_generic_event(world);
}

zox_begin_module(Generic)
    zox_module_dispose(dispose_generic)
    initialize_component_ids();
    define_components_generic(world);
    define_systems_generic(world);
    spawn_prefabs_generic(world);
zox_end_module(Generic)

#endif