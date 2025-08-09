zox_tag(Mesh);
zox_tag(Shader);
zox_tag(Material);
zox_tag(SingleMaterial);
zox_tag(RendererInstance);
zox_tag(VoxMesh);
zoxc_byte(MeshDirty);
zoxc_entity(MeshLink);
zoxc_byte(TextureDirty);
zoxc_byte(MeshAlignment);
zoxc_byte(RenderLod);
zoxc_byte(RenderLodDirty);
zoxc_byte(RenderDistance);
zoxc_byte(RenderDisabled);
zoxc_byte(RenderDistanceDirty);
zoxc_float(Brightness);
zoxc_float(Alpha);
zoxc_entity(MaterialLink);
zoxc_int2(TextureSize);
zoxc_byte(ShaderSourceIndex);
zoxc_entity(ShaderLink); // links to a shader entity
zoxc_entity(InstanceLink); // links to a instance parent
// zoxc_array(InstanceLinks, entity, 8)
zoxc_arrayd(MeshIndicies, int)
zoxc_arrayd(MeshVertices, float3)
zoxc_arrayd(MeshVertices2D, float2)
zoxc_arrayd(MeshUVs, float2)
zoxc_arrayd(MeshColors, color)
zoxc_arrayd(MeshColorRGBs, color_rgb)
#include "material_gpu_link.c"
#include "texture_gpu_link.c"
#include "ubo_gpu_link.c"
#include "mesh_gpu_link.c"
#include "uvs_gpu_link.c"
#include "colors_gpu_link.c"
#include "shader_gpu_link.c"
#include "compute_shader.c"
// Models
zoxc_entities(ModelLinks)
zoxc_entity(ModelLink);                 // a render instance links to model
zoxc_array(ModelLods, entity, 6);       // a model has multiple models per LOD

static inline int2 get_texture_size(ecs* world, entity e) {
    return zox_get_value(e, TextureSize);
}

void define_components_rendering(ecs *world) {
    zox_define_tag(Mesh);
    zox_define_tag(Shader);
    zox_define_tag(Material);
    zox_define_tag(SingleMaterial);
    zox_define_tag(RendererInstance);
    zox_define_tag(VoxMesh);
    zox_define_component_byte(MeshDirty);
    zox_define_component_byte(MeshAlignment);
    zox_define_component_entity(MeshLink);
    zox_define_component_byte(TextureDirty);
    zox_define_component_byte(RenderLod);
    zox_define_component_byte(RenderLodDirty);
    zox_define_component_byte(RenderDistance);
    zox_define_component_byte(RenderDistanceDirty);
    zox_define_component_byte(RenderDisabled);
    zox_define_component_float(Brightness);
    zox_define_component_float(Alpha);
    zox_define_component_entity(MaterialLink);
    zox_define_component_int2(TextureSize);
    zox_define_component_entity(InstanceLink);
    zox_define_component(MaterialInstancedGPULink);
    zox_define_component_w_dest(ShaderGPULink);
    zox_define_component_w_dest(MaterialGPULink);
    zox_define_component_w_dest(TextureGPULink);
    zox_define_component_w_dest(MeshGPULink);
    zox_define_component_w_dest(UvsGPULink);
    zox_define_component_w_dest(ColorsGPULink);
    zox_define_component_w_dest(ComputeShaderLink);
    zox_define_component_w_dest(UboGPULink);
    zox_define_component_byte(ShaderSourceIndex);
    zox_define_component_entity(ShaderLink);
    zox_define_memory_component(MeshIndicies);
    zox_define_memory_component(MeshVertices);
    zox_define_memory_component(MeshVertices2D);
    zox_define_memory_component(MeshUVs);
    zox_define_memory_component(MeshColors);
    zox_define_memory_component(MeshColorRGBs);
    // Models
    zox_define_entities_component(ModelLinks);
    zox_define_component_entity(ModelLink);
    zox_define_component_array(ModelLods);
}