zox_declare_tag(Mesh)
zox_declare_tag(Shader)
zox_declare_tag(Material)
zox_declare_tag(SingleMaterial)
zox_declare_tag(RendererInstance)
zox_declare_tag(RendererColored)
zox_component_byte(MeshDirty)
zox_component_entity(MeshLink)
zox_component_byte(TextureDirty)
zox_component_byte(MeshAlignment)
zox_component_byte(RenderLod)
zox_component_byte(RenderDistance)
zox_component_byte(RenderDisabled)
zox_component_byte(RenderDistanceDirty)
zox_component_float(Brightness)
zox_component_float(Alpha)
zox_component_entity(MaterialLink)
zox_component_int2(TextureSize)
zox_component_byte(ShaderSourceIndex)
zox_component_entity(ShaderLink) // links to a shader entity
zox_component_entity(InstanceLink) // links to a instance parent
zox_memory_component(MeshIndicies, int)
zox_memory_component(MeshVertices, float3)
zox_memory_component(MeshVertices2D, float2)
zox_memory_component(MeshUVs, float2)
zox_memory_component(MeshColors, color)
zox_memory_component(MeshColorRGBs, color_rgb)
#include "material_gpu_link.c"
#include "texture_gpu_link.c"
#include "ubo_gpu_link.c"
#include "mesh_gpu_link.c"
#include "uvs_gpu_link.c"
#include "colors_gpu_link.c"
#include "shader_gpu_link.c"
#include "compute_shader.c"

static inline int2 get_texture_size(ecs_world_t* world, ecs_entity_t e) {
    return zox_get_value(e, TextureSize)
}

void define_components_rendering(ecs_world_t *world) {
    zox_define_tag(Mesh)
    zox_define_tag(Shader)
    zox_define_tag(Material)
    zox_define_tag(SingleMaterial)
    zox_define_tag(RendererInstance)
    zox_define_tag(RendererColored)
    zox_define_component_byte(MeshDirty)
    zox_define_component_byte(MeshAlignment)
    zox_define_component_entity(MeshLink)
    zox_define_component_byte(TextureDirty)
    zox_define_component_byte(RenderLod)
    zox_define_component_byte(RenderDistance)
    zox_define_component_byte(RenderDistanceDirty)
    zox_define_component_byte(RenderDisabled)
    zox_define_component_float(Brightness)
    zox_define_component_float(Alpha)
    zox_define_component_entity(MaterialLink)
    zox_define_component_int2(TextureSize)
    zox_define_component_entity(InstanceLink)
    zox_define_component(MaterialInstancedGPULink)
    zox_define_component_w_dest(ShaderGPULink)
    zox_define_component_w_dest(MaterialGPULink)
    zox_define_component_w_dest(TextureGPULink)
    zox_define_component_w_dest(MeshGPULink)
    zox_define_component_w_dest(UvsGPULink)
    zox_define_component_w_dest(ColorsGPULink)
    zox_define_component_w_dest(ComputeShaderLink)
    zox_define_component_w_dest(UboGPULink)
    zox_define_component_byte(ShaderSourceIndex)
    zox_define_component_entity(ShaderLink) // links to a shader entity
    zox_define_memory_component(MeshIndicies)
    zox_define_memory_component(MeshVertices)
    zox_define_memory_component(MeshVertices2D)
    zox_define_memory_component(MeshUVs)
    zox_define_memory_component(MeshColors)
    zox_define_memory_component(MeshColorRGBs)
}