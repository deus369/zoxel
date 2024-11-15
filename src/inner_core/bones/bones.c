#if !defined(zox_mod_bones) && defined(zox_mod_transforms)
#define zox_mod_bones

#define zox_debug_bones

zox_declare_tag(Bone)
zox_declare_tag(Skeleton)
zox_memory_component(BoneLinks, ecs_entity_t)
#include "prefabs/prefabs.c"
#include "systems/skeleton_render3D_system.c"

zox_begin_module(Bones)
zox_define_tag(Skeleton)
zox_define_tag(Bone)
zox_define_memory_component(BoneLinks)
zox_render3D_plus_system(SkeletonRender3DSystem, [in] MeshIndicies, [in] MeshGPULink, [in] ColorsGPULink, [in] TransformMatrix, [in] RenderDisabled, [in] BoneLinks, [none] Skeleton, [none] MeshColorRGBs, [none] !UvsGPULink)
spawn_prefabs_bones(world);
zoxel_end_module(Bones)

#endif
