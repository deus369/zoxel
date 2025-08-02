#ifndef zoxm_hierarchy
#define zoxm_hierarchy

zox_component_byte(ChildIndex)
zox_entities_component(Children)
zox_declare_component_entities_child(ParentLink, Children)
#include "util/_.c"

zox_begin_module(Hierarchys)
    zox_define_component_byte(ChildIndex)
    zox_define_entities_component(Children)
    zox_define_component_entities_child(ParentLink)
zox_end_module(Hierarchys)

#endif