#ifndef zoxel_hierarchy
#define zoxel_hierarchy

// shared components
// zoxel_entities_component(Children, ecs_entity_t);
zoxel_memory_component(Children, ecs_entity_t);
zoxel_component(ParentLink, ecs_entity_t);
// util
#include "util/hierarchy_util.c"

//! Hierarchy Module.
void HierarchysImport(ecs_world_t *world)
{
    ECS_MODULE(world, Hierarchys);
    // zoxel_entities_component_define(world, Children);
    zoxel_memory_component_define(world, Children);
    ECS_COMPONENT_DEFINE(world, ParentLink);
}
#endif