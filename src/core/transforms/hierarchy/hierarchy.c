#ifndef zoxel_hierarchy
#define zoxel_hierarchy

zox_component_byte(ChildIndex)
zox_entities_component(Children)
zox_component(ParentLink, ecs_entity_t)

zox_begin_module(Hierarchys)
zox_define_component_byte(ChildIndex)
zox_define_entities_component(Children)
zox_define_component(ParentLink)
zoxel_end_module(Hierarchys)

#endif
