#ifndef zox_rendering_core
#define zox_rendering_core

#include "data/settings.c"
zox_declare_tag(Shader)
zox_declare_tag(Material)
zox_declare_tag(SingleMaterial)
zox_declare_tag(RendererInstance)
zox_declare_tag(RendererColored)
zox_component_byte(ShaderSourceIndex)
zox_component_entity(ShaderLink) // links to a shader entity
zox_component_entity(InstanceLink) // links to a instance parent
zox_memory_component(MeshIndicies, int)
zox_memory_component(MeshVertices, float3)
zox_memory_component(MeshVertices2D, float2)
zox_memory_component(MeshUVs, float2)
zox_memory_component(MeshColors, color)
zox_memory_component(MeshColorRGBs, color_rgb)
#include "components/components.c"
#include "util/util.c"
#include "prefabs/shader.c"
#include "prefabs/material.c"
#include "prefabs/renderer_instance.c"
#include "systems/systems.c"

ecs_entity_t prefab_renderer_instance;

void spawn_prefabs_rendering_core(ecs_world_t *world) {
    spawn_prefab_shader(world);
    spawn_prefab_material(world);
    prefab_renderer_instance = spawn_prefab_renderer_instance(world);
}

void process_arguments_rendering(ecs_world_t *world, char* args[], int count) {
    for (int i = 1; i < count; i++) {
        if (strcmp(args[i], "-e") == 0 || strcmp(args[i], "--opengles") == 0) {
            override_opengl_es = 1;
        } else if (strcmp(args[i], "-v") == 0 || strcmp(args[i], "--vulkan") == 0) {
            is_using_vulkan = 1;
        }
    }
}

void initialize_rendering_core(ecs_world_t *world) {
    initialize_render_loop();
    initialize_hook_load_shader();
    initialize_gpu_systems();
    add_hook_terminal_command(process_arguments_rendering);
}

void dispose_rendering_core(ecs_world_t *world, void *ctx) {
    dispose_render_loop();
    dispose_gpu_systems();
    dispose_hook_load_shader();
}

zox_begin_module(RenderingCore)
    initialize_rendering_core(world);
    zox_module_dispose(dispose_rendering_core)
    zox_define_tag(Shader)
    zox_define_tag(Material)
    zox_define_tag(SingleMaterial)
    zox_define_tag(RendererInstance)
    zox_define_tag(RendererColored)
    zox_define_component_entity(InstanceLink)
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
    zox_define_component_w_dest(UboGPULink)
    zox_define_component_byte(ShaderSourceIndex)
    zox_define_component_entity(ShaderLink) // links to a shader entity
    zox_define_memory_component(MeshIndicies)
    zox_define_memory_component(MeshVertices)
    zox_define_memory_component(MeshVertices2D)
    zox_define_memory_component(MeshUVs)
    zox_define_memory_component(MeshColors)
    zox_define_memory_component(MeshColorRGBs)
    define_systems_rendering(world);
    spawn_prefabs_rendering_core(world);
zox_end_module(RenderingCore)

#endif

/*#ifdef zoxel_render3D_uvs_system_overdebug
    check_opengl_error("[pre render3D_uvs_system Error]");
    GLint memory_used, memory_total;
    glGetIntegerv(GL_GPU_MEMORY_INFO_CURRENT_AVAILABLE_VIDMEM_NVX, &memory_used);
    glGetIntegerv(GL_GPU_MEMORY_INFO_DEDICATED_VIDMEM_NVX, &memory_total);
#endif*/
