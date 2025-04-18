// todo: use iterative instance function: prefab_children

void make_test_skeleton(ecs_world_t *world, const ecs_entity_t e) {
    const float3 test_spawn_bone_position = (float3) { 0, 0.18f, -0.03f };
    const float3 test_bone_position = (float3) { 0, 0.28f, -0.03f };
    Children *children = &((Children) { 0, NULL });
    BoneLinks *boneLinks = &((BoneLinks) { 0, NULL });

    zox_add_tag(e, Skeleton)
    zox_add_tag(e, SkeletonRenderer)
    // add_gpu_bone_index(world, e);
    spawn_gpu_bone_index(world, e);
    zox_prefab_add(e, BoneIndexes)
    // zox_prefab_add(e, BoneLinks)
#ifdef zox_paint_skeletons
    zox_add_tag(e, PaintedSkeleton)
#endif
    // add bone one
    const ecs_entity_t bone = spawn_bone(world, prefab_bone, float3_zero, float3_zero);
    zox_set(bone, ParentLink, { e })
    add_to_Children(children, bone);
    add_to_BoneLinks(boneLinks, bone);
    // add head bone
    // zox_get_muter(bone, Children, bone_children)
    Children *bone_children = &((Children) { 0, NULL });
    const ecs_entity_t bone_child = spawn_bone(world, prefab_bone, float3_zero, test_spawn_bone_position);
    zox_set(bone_child, ParentLink, { bone })
    zox_add_tag(bone_child, HeadBone)
    // add osccilation to head bone
    zox_set(bone_child, OscillateStartPosition3D, { test_bone_position })
    zox_add_tag(bone_child, OscillatePosition3D)
    add_to_Children(bone_children, bone_child);
    add_to_BoneLinks(boneLinks, bone_child);
    zox_set(bone, Children, { bone_children->length, bone_children->value })

    zox_set(e, Children, { children->length, children->value })
    zox_set(e, BoneLinks, { boneLinks->length, boneLinks->value })
}
