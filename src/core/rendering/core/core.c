#ifndef zox_rendering_core
#define zox_rendering_core

// #define zox_log_gpu_management
#define zox_pipelines_rendering EcsOnStore
#define zox_max_shaders 64
unsigned char shaders_count = 0;
const GLchar* shader_verts[zox_max_shaders];
const GLchar* shader_frags[zox_max_shaders];
zox_declare_tag(Shader)
zox_declare_tag(Material)
zox_declare_tag(SingleMaterial)
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
#include "components/compute_shader.c"
#include "components/frame_buffer.c"
#include "components/render_buffer.c"
#include "util/mesh_indicies.c"
#include "util/resource_management.c"
#include "util/mesh_util.c"
#include "util/mesh_indicies2.c"
#include "util/shader_loading.c"
#include "util/render_passes.c"
#include "prefabs/shader.c"
#include "prefabs/material.c"
#include "systems/mesh_dispose_system.c"
#include "systems/mesh_restore_system.c"
#include "systems/material_dispose_system.c"
#include "systems/material_restore_system.c"
#include "systems/shader_dispose_system.c"
#include "systems/shader_restore_system.c"
#include "systems/camera_render_system.c"

void spawn_prefabs_rendering_core(ecs_world_t *world) {
    spawn_prefab_shader(world);
    spawn_prefab_material(world);
}

void initialize_rendering_core(ecs_world_t *world) {
    initialize_render_loop();
    initialize_shader_loading();
    initialize_gpu_systems();
}

void dispose_rendering_core(ecs_world_t *world, void *ctx) {
    dispose_render_loop();
    dispose_shader_loading();
    dispose_gpu_systems();
}

zox_begin_module(RenderingCore)
initialize_rendering_core(world);
zox_module_dispose(dispose_rendering_core)
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
zox_define_component_w_dest(ComputeShaderLink)
zox_define_component_w_dest(FrameBufferLink)
zox_define_component_w_dest(RenderBufferLink)
zox_define_component_byte(ShaderSourceIndex)
zox_define_component_entity(ShaderLink) // links to a shader entity
zox_define_memory_component(MeshIndicies)
zox_define_memory_component(MeshVertices)
zox_define_memory_component(MeshVertices2D)
zox_define_memory_component(MeshUVs)
zox_define_memory_component(MeshColors)
zox_define_memory_component(MeshColorRGBs)
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
zox_system_1(CameraRender3DSystem, zox_pipelines_rendering, [in] cameras.ViewMatrix, [in] cameras.FieldOfView, [in] cameras.ScreenPosition, [in] ScreenDimensions, [none] !cameras.CameraUI)
zox_system_1(CameraRenderUISystem, zox_pipelines_rendering, [in] cameras.ViewMatrix, [in] cameras.FieldOfView, [in] cameras.ScreenPosition, [in] ScreenDimensions, [none] cameras.CameraUI)
spawn_prefabs_rendering_core(world);
zoxel_end_module(RenderingCore)

#endif

/*#ifdef zoxel_render3D_uvs_system_overdebug
    check_opengl_error("[pre render3D_uvs_system Error]");
    GLint memory_used, memory_total;
    glGetIntegerv(GL_GPU_MEMORY_INFO_CURRENT_AVAILABLE_VIDMEM_NVX, &memory_used);
    glGetIntegerv(GL_GPU_MEMORY_INFO_DEDICATED_VIDMEM_NVX, &memory_total);
#endif*/
