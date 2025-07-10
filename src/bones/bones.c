#if !defined(zox_mod_bones) && defined(zox_mod_transforms)
#define zox_mod_bones

// #define zox_debug_bones
// #define zox_transparent_skeletons

zox_declare_tag(Bone)
zox_declare_tag(Skeleton)
zox_declare_tag(SkeletonRenderer)
zox_declare_tag(PaintedSkeleton)
zox_declare_tag(HeadBone)
zox_component_float3(BonePosition)
zox_component_float3(BoneSize)
zox_memory_component(BoneIndexes, byte)
zox_memory_component(BoneLinks, ecs_entity_t)
#include "components/bone_index.c"
#include "shaders/_.c"
#include "prefabs/_.c"
#include "systems/_.c"
#include "util/test.c"

zox_begin_module(Bones)
    add_hook_load_shader(&spawn_shaders_bones);
    zox_define_tag(Bone)
    zox_define_tag(Skeleton)
    zox_define_tag(SkeletonRenderer)
    zox_define_tag(PaintedSkeleton)
    zox_define_tag(HeadBone)
    zox_define_component_float3(BonePosition)
    zox_define_component_float3(BoneSize)
    zox_define_component(MaterialBone)
    zox_define_memory_component(BoneIndexes)
    zox_define_memory_component(BoneLinks)
    zox_define_component_w_dest(BoneIndexGPULink)
    define_systems_bones(world);
    spawn_prefabs_bones(world);
zox_end_module(Bones)

#endif