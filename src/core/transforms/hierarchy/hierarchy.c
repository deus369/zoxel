#ifndef zoxel_hierarchy
#define zoxel_hierarchy

zoxel_entities_component(Children)
zoxel_component(ParentLink, ecs_entity_t)

zoxel_begin_module(Hierarchys)
zoxel_define_entities_component(Children, [in] Children)
zoxel_define_component(ParentLink)
zoxel_end_module(Hierarchys)

#endif