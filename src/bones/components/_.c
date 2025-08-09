zox_tag(Bone);
zox_tag(Skeleton);
zox_tag(PaintedSkeleton);
zox_tag(HeadBone);
zoxc_float3(BonePosition);
zoxc_float3(BoneSize);
zoxc_arrayd(BoneIndexes, byte)
zoxc_arrayd(BoneLinks, entity)
#include "bone_index.c"

void define_components_bones(ecs *world) {
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