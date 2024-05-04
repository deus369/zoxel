#ifndef zoxel_rendering_core
#define zoxel_rendering_core

// settings
// #define zox_log_gpu_management
#define zox_pipelines_rendering EcsOnStore
// float3 viewport_clear_color = { 125 / 255.0f, 125 / 255.0f, 125 / 255.0f };
const float3 viewport_clear_color = (float3) { 0.3f, 0.1f, 0.1f };
#define zox_max_shaders 64
unsigned char shaders_count = 0;
const GLchar* shader_verts[zox_max_shaders];
const GLchar* shader_frags[zox_max_shaders];
// zoxel_component_includes
zox_declare_tag(Shader)
zox_declare_tag(Material)
zox_declare_tag(SingleMaterial)
#include "util/mesh_indicies.c"
zox_component_byte(ShaderSourceIndex)
zox_component_entity(ShaderLink) // links to a shader entity
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
#include "fun/resource_management.c"
#include "util/mesh_util.c"
#include "util/mesh_indicies2.c"
#include "util/shader_loading.c"
// zoxel_prefab_includes
#include "prefabs/shader.c"
#include "prefabs/material.c"
// zoxel_system_includes
#include "systems/mesh_dispose_system.c"
#include "systems/mesh_restore_system.c"
#include "systems/material_dispose_system.c"
#include "systems/material_restore_system.c"
#include "systems/shader_dispose_system.c"
#include "systems/shader_restore_system.c"
// zoxel_function_includes
#include "fun/camera_render_system.c"

unsigned char get_new_shader_source_index() {
    shaders_count++;
    return shaders_count - 1;
}

void spawn_prefabs_rendering_core(ecs_world_t *world) {
    spawn_prefab_shader(world);
    spawn_prefab_material(world);
}

void dispose_rendering_core(ecs_world_t *world) {
    dispose_render_loop();
    dispose_shader_loading();
    dispose_gpu_systems();
}

zox_begin_module(RenderingCore)
initialize_render_loop();
initialize_shader_loading();
initialize_gpu_systems();
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
zox_define_component_byte(ShaderSourceIndex)
zox_define_component_entity(ShaderLink) // links to a shader entity
zox_define_memory_component(MeshIndicies)
zox_define_memory_component(MeshVertices)
zox_define_memory_component(MeshVertices2D)
zox_define_memory_component(MeshUVs)
zox_define_memory_component(MeshColors)
zox_define_memory_component(MeshColorRGBs)
// zoxel_system_defines
zox_gpu_dispose_system(MeshGPUDisposeSystem, [in] MeshGPULink)
zox_gpu_dispose_system(MeshUvsGPUDisposeSystem, [in] UvsGPULink)
zox_gpu_dispose_system(MeshColorsGPUDisposeSystem, [in] ColorsGPULink)
zox_gpu_dispose_system(TextureGPUDisposeSystem, [in] TextureGPULink)
zox_gpu_restore_system(MeshDirtyRestoreSystem, [out] MeshDirty)
zox_gpu_restore_system(MeshGPURestoreSystem, [out] MeshGPULink)
zox_gpu_restore_system(UvsGPULinkRestoreSystem, [out] UvsGPULink)
zox_gpu_restore_system(ColorsGPULinkRestoreSystem, [out] ColorsGPULink)
zox_gpu_restore_system(TextureRestoreSystem, [out] TextureGPULink, [out] TextureDirty)
zox_gpu_dispose_system(ShaderDisposeSystem, [in] ShaderGPULink)
zox_gpu_restore_system(ShaderRestoreSystem, [in] ShaderSourceIndex, [out] ShaderGPULink)
zox_gpu_dispose_system(MaterialDisposeSystem, [in] MaterialGPULink)
zox_gpu_restore_system(MaterialRestoreSystem, [in] ShaderLink, [out] MaterialGPULink)
zox_system_1(CameraRender3DSystem, zox_pipelines_rendering, [in] cameras.ViewMatrix, [in] cameras.FieldOfView, [in] cameras.ScreenPosition, [in] cameras.ScreenDimensions, [none] !cameras.CameraUI)
zox_system_1(CameraRenderUISystem, zox_pipelines_rendering, [in] cameras.ViewMatrix, [in] cameras.FieldOfView, [in] cameras.ScreenPosition, [in] cameras.ScreenDimensions, [none] cameras.CameraUI)
zoxel_end_module(RenderingCore)

#endif

/*#ifdef zoxel_render3D_uvs_system_overdebug
    check_opengl_error("[pre render3D_uvs_system Error]");
    GLint memory_used, memory_total;
    glGetIntegerv(GL_GPU_MEMORY_INFO_CURRENT_AVAILABLE_VIDMEM_NVX, &memory_used);
    glGetIntegerv(GL_GPU_MEMORY_INFO_DEDICATED_VIDMEM_NVX, &memory_total);
#endif*/
