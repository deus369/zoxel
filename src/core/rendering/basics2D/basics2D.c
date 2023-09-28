#ifndef zoxel_rendering_basics2D
#define zoxel_rendering_basics2D

// implements some basic default shaders
// shaders
#include "shaders/instanced2D.c"
#include "shaders/textured2D.c"
// util
#include "util/material2D.c"
#include "util/instanced2D_material.c"
#include "util/shader_textured2D.c"
// systems
#include "systems/element_render_system.c" // move to ui core
#include "systems/mesh2D_update_system.c"
#include "systems/mesh2D_uvs_update_system.c"
#include "systems/render2D_instance_system.c"
#include "systems/render2D_system.c"

// for now until I move it all to ecs
void rendering_dispose_basic_shaders2D() {
    dispose_shader2D_instance_material();
    dispose_shader2D_textured();
}

void rendering_load_basic_shaders2D(ecs_world_t *world) {
    if (load_instance2D_material()) zoxel_log("    ! error loading [instance2D_material]\n");
    if (load_shader2D_textured()) zoxel_log("    ! error loading [shader2D_textured]\n");
}

void rendering_restore_basic_shaders2D(ecs_world_t *world) {
    if (load_instance2D_material()) zoxel_log("    ! error loading [instance2D_material]\n");
    if (load_shader2D_textured()) zoxel_log("    ! error loading [shader2D_textured]\n");
}

zox_begin_module(RenderingBasics2D)
add_load_shader_function((funfun) { &rendering_load_basic_shaders2D });
add_restore_shader_function((funfun) { &rendering_restore_basic_shaders2D });
// zoxel_define_components
// zoxel_define_systems
#ifdef zoxel_transforms2D
    //zox_system_1(InstanceRender2DSystem, 0, [in] Position2D, [in] Rotation2D, [in] Scale1D, [in] Brightness, [none] !MaterialGPULink, [none] !MeshGPULink)
    //zox_system_1(RenderMaterial2DSystem, 0, [in] Position2D, [in] Rotation2D, [in] Scale1D, [in] Brightness, [in] MaterialGPULink, [in] TextureGPULink, [none] !MeshGPULink)
    //zox_system_1(ElementRenderSystem, 0, [none] ElementRender, [in] Position2D, [in] Rotation2D, [in] Scale1D, [in] Layer2D, [in] Brightness, [in] MeshGPULink, [in] UvsGPULink, [in] MaterialInstancedGPULink, [in] TextureGPULink, [in] MeshDirty)
    //add_to_render2D_loop(ecs_id(ElementRenderSystem));
    zox_render2D_system(ElementRenderSystem, [none] ElementRender, [in] Position2D, [in] Rotation2D, [in] Scale1D, [in] Layer2D, [in] Brightness, [in] MeshGPULink, [in] UvsGPULink, [in] MaterialInstancedGPULink, [in] TextureGPULink, [in] MeshDirty)
#endif
zox_system_1(Mesh2DUvsUpdateSystem, main_thread_pipeline, [out] MeshDirty, [in] MeshIndicies, [in] MeshVertices2D, [in] MeshUVs, [in] MeshGPULink, [in] UvsGPULink, [none] !MeshColorRGBs)
zoxel_end_module(RenderingBasics2D)

// zox_system_1(Mesh2DUpdateSystem, main_thread_pipeline, [out] MeshDirty, [in] MeshIndicies, [in] MeshVertices2D, [in] MeshGPULink, [in] MaterialGPULink, [none] !MeshUVs, [none] !MeshColorRGBs)
// zox_system_1(Mesh2DInstancedUpdateSystem, main_thread_pipeline, [out] MeshDirty, [in] MeshIndicies, [in] MeshVertices2D, [in] MeshGPULink, [in] MaterialInstancedGPULink, [none] !MeshUVs, [none] !MeshColorRGBs)

#endif