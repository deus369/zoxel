#ifndef zox_elements3D
#define zox_elements3D

zox_declare_tag(Element3D)
zox_declare_tag(Text3D)
zox_component_float3(UITrail)
zox_component_float(Text3DScale)
#include "data/_.c"
#include "settings/_.c"
#include "util/_.c"
#include "prefabs/_.c"
#include "util/popup.c"
#include "systems/_.c"

zox_begin_module(Elements3D)
    zox_define_tag(Element3D)
    zox_define_tag(Text3D)
    zox_define_component(UITrail)
    zox_define_component_float(Text3DScale)
    define_systems_elements3D(world);
    spawn_prefabs_elements3D(world);
    add_hooks(world);
zox_end_module(Elements3D)

#endif