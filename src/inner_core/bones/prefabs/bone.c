extern void add_debug_cube(ecs_world_t *world, const ecs_entity_t e, const float size);
const float initial_bone_size = 0.03f;

ecs_entity_t spawn_prefab_bone(ecs_world_t *world) {
    zox_prefab()
    zox_prefab_name("prefab_bone")
    add_transform3Ds(world, e, 1);
    // zox_set(e, Scale1D, { initial_bone_size })
    // zox_set(e, Scale1D, { 0.5f })
    zox_prefab_set(e, TransformMatrix, { float4x4_identity() })
    zox_prefab_set(e, LocalPosition3D, { float3_zero })
    zox_prefab_set(e, LocalRotation3D, { quaternion_identity })
    return e;
}

ecs_entity_t spawn_bone(ecs_world_t *world, const ecs_entity_t prefab, const float3 position) {
    zox_instance(prefab)
    zox_set(e, Position3D, { position })
    zox_add(e, Children)
#ifdef zox_debug_bones
    add_debug_cube(world, e, initial_bone_size);
#endif
    return e;
}
