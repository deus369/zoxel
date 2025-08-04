// todo: use iterative instance function: prefab_children
/*void prefab_make_skeleton(ecs_world_t *world, const ecs_entity_t e) {
    zox_add_tag(e, Skeleton)
    zox_add_tag(e, SkeletonMesher)
    zox_prefab_set(e, Children, { 0, NULL });
    zox_prefab_add(e, BoneLinks)
    zox_prefab_add(e, BoneIndexes)
    // add_gpu_bone_index(world, e);
    // zox_prefab_add(e, BoneLinks)
    spawn_gpu_bone_index(world, e);
#ifdef zox_paint_skeletons
    zox_add_tag(e, PaintedSkeleton)
#endif
}*/
// will this effect other children though?
void spawn_skeleton_bones(ecs_world_t *world, const ecs_entity_t e, float head_move_y) {
    // prefab_make_skeleton(world, e);

    // todo: apply voxel scale to skeleton spawning
    // float scale = 1 / 64.0f; // player_vox_scale;
    const float3 test_bone_size_body = (float3) { 0.08f, 0.08f, 0.08f };
    // head
    const float3 bone_head_position = (float3) { 0, 0.15f, 0 }; //  -0.03f * 0.5f };
    const float3 test_bone_head_size = (float3) { 0.1f, 0.1f, 0.1f };
    // animating
    const float head_delta = randf_range(0.01f, 0.01f + head_move_y);
    const float3 test_bone_position_animating = (float3) { 0, 0.15f + head_delta * 2, 0 };
    const float3 test_bone_position_animating_delta = (float3) { 0, head_delta, 0 };

    Children children = (Children) { 0, NULL };
    BoneLinks bones = (BoneLinks) { 0, NULL };

    // = Body Bone =
    const ecs_entity_t bone_body = spawn_bone(world, prefab_bone, float3_zero, float3_zero, test_bone_size_body);
    zox_set(bone_body, ParentLink, { e })
    add_to_Children(&children, bone_body);
    add_to_BoneLinks(&bones, bone_body);

    Children bone_children = (Children) { 0, NULL };
    const ecs_entity_t bone_child = spawn_bone(world, prefab_bone, bone_head_position, bone_head_position, test_bone_head_size);
    zox_set(bone_child, ParentLink, { bone_body })
    zox_add_tag(bone_child, HeadBone)
    // add osccilation to head bone
    zox_set(bone_child, OscillateStartPosition3D, { test_bone_position_animating })
    zox_set(bone_child, OscillateDeltaPosition3D, { test_bone_position_animating_delta })

    zox_add_tag(bone_child, OscillatePosition3D)
    add_to_Children(&bone_children, bone_child);
    add_to_BoneLinks(&bones, bone_child);
    zox_set_ptr(bone_body, Children, bone_children)

    zox_set_ptr(e, Children, children)
    zox_set_ptr(e, BoneLinks, bones)
}
