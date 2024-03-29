#ifndef zoxel_rendering_core
#define zoxel_rendering_core

// settings
// float3 viewport_clear_color = { 125 / 255.0f, 125 / 255.0f, 125 / 255.0f };
const float3 viewport_clear_color = (float3) { 0.3f, 0.1f, 0.1f };
// zoxel_component_includes
zox_declare_tag(Shader)
zox_declare_tag(Material)
zox_declare_tag(SingleMaterial)
#include "util/mesh_indicies.c"
zox_memory_component(MeshIndicies, int)
zox_memory_component(MeshVertices, float3)
zox_memory_component(MeshVertices2D, float2)
zox_memory_component(MeshUVs, float2)
zox_memory_component(MeshColors, color)
zox_memory_component(MeshColorRGBs, color_rgb)
#include "components/material_gpu_link.c"
#include "components/texture_gpu_link.c"
#include "components/mesh_gpu_link.c"
#include "components/uvs_gpu_link.c"
#include "components/colors_gpu_link.c"
#include "components/shader_gpu_link.c"
// zoxel_util_includes
#include "util/mesh_util.c"
#include "util/mesh_indicies2.c"
#include "util/shader_loading.c"
// zoxel_prefab_includes
#include "prefabs/shader.c"
#include "prefabs/material.c"
// zoxel_system_includes
#include "systems/mesh_restore_system.c"
#include "systems/mesh_dispose_system.c"
// zoxel_function_includes
#include "fun/render_loop.c"
#include "fun/gpu_dispose.c"
#include "fun/gpu_restore.c"

void spawn_prefabs_rendering_core(ecs_world_t *world) {
    spawn_prefab_shader(world);
    spawn_prefab_material(world);
}

void dispose_rendering_core(ecs_world_t *world) {
    dispose_render_loop();
    dispose_shader_loading();
}

zox_begin_module(RenderingCore)
initialize_render_loop();
initialize_shader_loading();
// zoxel_component_defines
zox_define_tag(Shader)
zox_define_tag(Material)
zox_define_tag(SingleMaterial)
zox_define_component(MaterialInstancedGPULink)
zox_define_component_w_dest(ShaderGPULink)
zox_define_component_w_dest(MaterialGPULink)
zox_define_component_w_dest(TextureGPULink)
zox_define_component_w_dest(MeshGPULink)
zox_define_component_w_dest(UvsGPULink)
zox_define_component_w_dest(ColorsGPULink)
zox_define_memory_component(MeshIndicies)
zox_define_memory_component(MeshVertices)
zox_define_memory_component(MeshVertices2D)
zox_define_memory_component(MeshUVs)
zox_define_memory_component(MeshColors)
zox_define_memory_component(MeshColorRGBs)
// zoxel_system_defines
zox_system_1(MeshGPUDisposeSystem, 0, [in] MeshGPULink)
zox_system_1(MeshColorsGPUDisposeSystem, 0,[in] ColorsGPULink)
zox_system_1(MeshUvsGPUDisposeSystem, 0,[in] UvsGPULink)
zox_system_1(ShaderGPUDisposeSystem, 0, [in] ShaderGPULink)
zox_system_1(MaterialGPUDisposeSystem, 0, [in] MaterialGPULink)
zox_system_1(MeshDirtyRestoreSystem, 0, [out] MeshDirty)
zox_system_1(MeshGPURestoreSystem, 0, [out] MeshGPULink)
zox_system_1(UvsGPULinkRestoreSystem, 0, [out] UvsGPULink)
zox_system_1(ColorsGPULinkRestoreSystem, 0, [out] ColorsGPULink)
zoxel_end_module(RenderingCore)

#endif

/*#ifdef zoxel_render3D_uvs_system_overdebug
    check_opengl_error("[pre render3D_uvs_system Error]");
    GLint memory_used, memory_total;
    glGetIntegerv(GL_GPU_MEMORY_INFO_CURRENT_AVAILABLE_VIDMEM_NVX, &memory_used);
    glGetIntegerv(GL_GPU_MEMORY_INFO_DEDICATED_VIDMEM_NVX, &memory_total);
#endif*/
