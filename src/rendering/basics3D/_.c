#ifndef zox_mod_rendering_basics3D
#define zox_mod_rendering_basics3D

// #define is_catch_basic3D_errors
zox_declare_tag(MeshBasic3D)
zox_declare_tag(TexturedMesh3D)
#include "data/_.c"
#include "materials/_.c"
#include "util/_.c"
#include "systems/_.c"

zox_begin_module(RenderingBasics3D)
    zox_define_tag(MeshBasic3D)
    zox_define_tag(TexturedMesh3D)
    zox_define_component(MaterialTextured3D)
    zox_define_component(MaterialColored3D)
    zox_define_component(MaterialVoxInstance)
    zox_define_component(MaterialBasic3D)
    define_systems_basics3D(world);
    add_hook_load_shader(&spawn_shaders_basics3D);
zox_end_module(RenderingBasics3D)

#endif