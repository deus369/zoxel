#ifndef zoxel_hierarchy
#define zoxel_hierarchy

zox_component_byte(ChildIndex)
zox_entities_component(Children)
zox_component(ParentLink, ecs_entity_t)
#include "util/parent_link.c"

void on_child_added(ecs_world_t *world, const ecs_entity_t parent, const ecs_entity_t child) {
    // zox_log(" + added [%lu] to canvas [%lu]\n", e, canvas)
    // todo: make this generic for when component is set, event
    // this isn't systematic enough for children linking!
    Children *children = zox_get_mut(parent, Children)
    if (add_to_Children(children, child)) zox_modified(parent, Children)
}

zox_begin_module(Hierarchys)
zox_define_component_byte(ChildIndex)
zox_define_entities_component(Children)
zox_define_component(ParentLink)
ecs_observer_init(world, &(ecs_observer_desc_t) {
    .filter.expr = "ParentLink",
    .callback = on_destroyed_ParentLink,
    .events = { EcsOnRemove },
});
zoxel_end_module(Hierarchys)

#endif
