#ifndef zoxel_hierarchy
#define zoxel_hierarchy

zox_component_byte(ChildIndex)
zox_entities_component(Children)
zox_component_entity(ParentLink)
#include "util/parent_link.c"
#include "util/children_util.c"

zox_begin_module(Hierarchys)
zox_define_component_byte(ChildIndex)
zox_define_entities_component(Children)
zox_define_component_entity(ParentLink)
ecs_observer_init(world, &(ecs_observer_desc_t) {
    .filter.expr = "ParentLink",
    .callback = on_destroyed_ParentLink,
    .events = { EcsOnRemove },
});
zoxel_end_module(Hierarchys)

#endif
