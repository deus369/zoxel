#ifndef zoxel_hierarchy
#define zoxel_hierarchy

zox_entities_component(Children)
zox_component(ParentLink, ecs_entity_t)
zox_byte_component(ChildIndex)

zox_begin_module(Hierarchys)
zox_define_entities_component(Children, [in] Children)
zox_define_component(ParentLink)
zox_define_component(ChildIndex)
zoxel_end_module(Hierarchys)

#endif