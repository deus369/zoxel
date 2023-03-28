#ifndef zoxel_hierarchy
#define zoxel_hierarchy

// zoxel_entities_component(Children, ecs_entity_t);
zoxel_memory_component(Children, ecs_entity_t);
zoxel_component(ParentLink, ecs_entity_t);
#include "util/hierarchy_util.c"

zoxel_begin_module(Hierarchys)
// zoxel_entities_component_define(world, Children);
zoxel_define_memory_component(Children)
zoxel_define_component(ParentLink)
zoxel_end_module(Hierarchys)

#endif