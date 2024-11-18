#if !defined(zox_mod_bones) && defined(zox_mod_transforms)
#define zox_mod_bones

const float3 test_spawn_bone_position = (float3) { 0, 0.18f, -0.03f };
const float3 test_bone_position = (float3) { 0, 0.58f, -0.03f };

zox_declare_tag(Bone)
zox_declare_tag(Skeleton)
zox_declare_tag(SkeletonRenderer)
zox_component_float3(BonePosition)
zox_memory_component(BoneIndexes, unsigned char)
zox_memory_component(BoneLinks, ecs_entity_t)
#include "components/bone_index.c"
#include "shaders/bone.c"
#include "prefabs/prefabs.c"
#include "systems/skeleton_render3D_system.c"
#include "systems/bone_index_generate_system.c"
#include "systems/bone_index_upload_system.c"
#include "util/test.c"

void spawn_shaders_bones(ecs_world_t *world) {
    spawn_material_bone(world);
}

zox_begin_module(Bones)
add_load_shader_function(&spawn_shaders_bones);
zox_define_tag(Bone)
zox_define_tag(Skeleton)
zox_define_tag(SkeletonRenderer)
zox_define_component_float3(BonePosition)
zox_define_component(MaterialBone)
zox_define_memory_component(BoneIndexes)
zox_define_memory_component(BoneLinks)
zox_define_component_w_dest(BoneIndexGPULink)
zox_render3D_plus_system(SkeletonRender3DSystem, [in] MeshIndicies, [in] MeshGPULink, [in] ColorsGPULink, [in] BoneIndexGPULink, [in] TransformMatrix, [in] RenderDisabled, [in] BoneLinks, [none] Skeleton, [none] MeshColorRGBs, [none] !UvsGPULink)
// generating bone indexes here
zox_system(BoneIndexGenerateSystem, EcsOnUpdate, [in] MeshDirty, [in] MeshVertices, [out] BoneIndexes)
zox_system_1(BoneIndexUploadSystem, zox_pip_mainthread, [in] MeshDirty, [in] BoneIndexes, [out] BoneIndexGPULink)
spawn_prefabs_bones(world);
zoxel_end_module(Bones)

#endif
