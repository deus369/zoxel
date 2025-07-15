extern void add_debug_cube(ecs_world_t *world, const ecs_entity_t e, const float3 size);
const float3 initial_bone_size = (float3) { 0.03f, 0.03f, 0.03f };

ecs_entity_t spawn_prefab_bone(ecs_world_t *world) {
    zox_prefab()
    zox_prefab_name("bone")
    zox_prefab_set(e, Position3D, { float3_zero })
    zox_prefab_set(e, Rotation3D, { float4_identity })
    zox_prefab_set(e, Scale1D, { 1 }) // initial_bone_size | 0.5
    zox_prefab_set(e, TransformMatrix, { float4x4_identity() })
    zox_prefab_set(e, LocalPosition3D, { float3_zero })
    zox_prefab_set(e, LocalRotation3D, { quaternion_identity })
    zox_prefab_add(e, BonePosition)
    zox_prefab_add(e, BoneSize)
    zox_prefab_add(e, Children)
    return e;
}

ecs_entity_t spawn_bone(ecs_world_t *world, const ecs_entity_t prefab, const float3 skeleton_position, const float3 local_position, const float3 bone_size) {
    zox_instance(prefab)
    zox_set(e, LocalPosition3D, { local_position })
    zox_set(e, Position3D, { skeleton_position })
    zox_set(e, BonePosition, { skeleton_position }) // actually position within skeleton, local to root bone
    zox_set(e, BoneSize, { bone_size })
#ifdef zox_debug_bones
    add_debug_cube(world, e, bone_size);
#endif
    return e;
}
