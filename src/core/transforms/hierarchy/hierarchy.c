#ifndef zoxel_hierarchy
#define zoxel_hierarchy

// zoxel_entities_component(Children, ecs_entity_t);
zoxel_memory_component(Children, ecs_entity_t);
zoxel_component(ParentLink, ecs_entity_t);
#include "util/hierarchy_util.c"

void on_parent_destroyed(ecs_iter_t *it) {
    // zoxel_log("on_parent_destroyed [%i]\n", it->count);
    const Children *children = ecs_field(it, Children, 1);
    for (int i = 0; i < it->count; i++) {
        const Children *children2 = &children[i];
        for (int j = 0; j < children2->length; j++) {
            ecs_delete(it->world, children2->value[j]);
        }   
        // ecs_delete(it->world, it->entities[i]);
    }
}

zoxel_begin_module(Hierarchys)
// zoxel_entities_component_define(world, Children);
zoxel_define_memory_component(Children)
ecs_observer_init(world, &(ecs_observer_desc_t) {
    .filter.expr = "[in] Children",
    .callback = on_parent_destroyed,
    .events = { EcsOnRemove },
});
// ECS_OBSERVER(world, on_parent_destroyed, EcsOnStore, Children);
zoxel_define_component(ParentLink)
zoxel_end_module(Hierarchys)

#endif