#ifndef zoxel_hierarchy
#define zoxel_hierarchy

// zoxel_entities_component(Children, ecs_entity_t);
zoxel_memory_component(Children, ecs_entity_t);
zoxel_component(ParentLink, ecs_entity_t);
#include "util/hierarchy_util.c"

//! Hierarchy Module.
void HierarchysImport(ecs_world_t *world)
{
    zoxel_module(Hierarchys)
    // zoxel_entities_component_define(world, Children);
    zoxel_memory_component_define(world, Children);
    zoxel_define_component(ParentLink)
}
#endif