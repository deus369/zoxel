zox_declare_tag(Bone)
zox_declare_tag(Skeleton)
zox_declare_tag(PaintedSkeleton)
zox_declare_tag(HeadBone)
zox_component_float3(BonePosition)
zox_component_float3(BoneSize)
zox_memory_component(BoneIndexes, byte)
zox_memory_component(BoneLinks, ecs_entity_t)
#include "bone_index.c"

void define_components_bones(ecs_world_t *world) {
    zox_define_tag(Bone)
    zox_define_tag(Skeleton)
    zox_define_tag(PaintedSkeleton)
    zox_define_tag(HeadBone)
    zox_define_component_float3(BonePosition)
    zox_define_component_float3(BoneSize)
    zox_define_component(MaterialBone)
    zox_define_memory_component(BoneIndexes)
    zox_define_memory_component(BoneLinks)
    zox_define_component_w_dest(BoneIndexGPULink)
}