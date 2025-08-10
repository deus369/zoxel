#ifndef zoxm_hierarchy
#define zoxm_hierarchy

zoxc_byte(ChildIndex);
zoxc_entities(Children)
zoxc_child(ParentLink, Children)
#include "util/_.c"

zox_begin_module(Hierarchys)
    zoxd_byte(ChildIndex);
    zox_define_entities_component(Children);
    zox_define_component_entities_child(ParentLink);
zox_end_module(Hierarchys)

#endif