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
#include "systems/mesh2D_update_system.c"
#include "systems/mesh2D_uvs_update_system.c"
#include "systems/render2D_instance_system.c"
#include "systems/render2D_system.c"

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
    zox_render3D_system(RenderMaterial2DSystem, [in] transforms2.d.Position2D, [in] transforms2.d.Rotation2D, [in] transforms.Scale1D, [in] rendering.Brightness, [in] rendering.core.MaterialGPULink, [in] rendering.core.TextureGPULink, [none] !rendering.core.MeshGPULink)
    zox_system_1(Mesh2DUpdateSystem, zox_pip_mainthread, [out] rendering.MeshDirty, [in] rendering.core.MeshIndicies, [in] rendering.core.MeshVertices2D, [in] rendering.core.MeshGPULink, [in] rendering.core.MaterialGPULink, [none] !rendering.core.MeshUVs, [none] !rendering.core.MeshColorRGBs)
    zox_system_1(Mesh2DUvsUpdateSystem, zox_pip_mainthread, [in] rendering.core.MeshIndicies, [in] rendering.core.MeshVertices2D, [in] rendering.core.MeshUVs, [in] rendering.core.MeshGPULink, [in] rendering.core.UvsGPULink, [out] rendering.MeshDirty)
zox_end_module(RenderingBasics2D)

#endif