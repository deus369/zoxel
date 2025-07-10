#ifndef zox_mod_rendering_basics2D
#define zox_mod_rendering_basics2D

#include "data/settings.c"
#include "shaders/instanced2D.c"
#include "shaders/textured2D.c"
#include "shaders/render_texture.c"
#include "components/material_textured2D.c"
#include "util/square_mesh.c"
#include "util/material2D.c"
#include "util/instanced2D_material.c"
#include "util/render_util.c"
#include "prefabs/shader_textured2D.c"
#include "prefabs/render_texture.c"
#include "systems/_.c"

// for now until I move it all to ecs
void rendering_dispose_basic_shaders2D() {
    dispose_shader2D_instance_material();
    dispose_square_mesh();
}

// spawns after, when opengl loads
void spawn_shaders_basics2D(ecs_world_t *world) {
    spawn_material_textured2D(world);
    spawn_material_render_texture(world);
    initialize_square_mesh_textured();
    load_instance2D_material();
}

zox_begin_module(RenderingBasics2D)
    add_hook_load_shader(&spawn_shaders_basics2D);
    zox_define_component(MaterialTextured2D)
    zox_define_component(MaterialAttributesRenderTexture)
    define_systems_basics2D(world);
zox_end_module(RenderingBasics2D)

#endif