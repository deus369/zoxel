#ifndef zox_elements3D
#define zox_elements3D

zox_declare_tag(Element3D)
zox_declare_tag(Text3D)
zox_component_float3(UITrail)
#include "util/log.c"
#include "util/prefab.c"
#include "util/can_render.c"
#include "util/debug.c"
#include "data/data.c"
#include "prefabs/prefabs.c"
#include "systems/systems.c"

zox_begin_module(Elements3D)
    zox_define_tag(Element3D)
    zox_define_tag(Text3D)
    zox_define_component(UITrail)
    define_systems_elements3D(world);
    spawn_prefabs_elements3D(world);
    add_hooks(world);
zox_end_module(Elements3D)

#endif