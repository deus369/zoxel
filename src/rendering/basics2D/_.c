#ifndef zox_mod_rendering_basics2D
#define zox_mod_rendering_basics2D

#include "settings/_.c"
#include "materials/_.c"
#include "util/_.c"
#include "systems/_.c"

zox_begin_module(Rendering2)
    zox_define_component(MaterialTextured2D)
    zox_define_component(MaterialAttributesRenderTexture)
    define_systems_basics2D(world);
    add_hook_load_shader(&spawn_shaders_basics2D);
zox_end_module(Rendering2)

#endif