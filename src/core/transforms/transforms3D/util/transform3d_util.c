void add_transform3Ds(ecs_world_t *world, const ecs_entity_t e) {
    zox_prefab_set(e, Position3D, { float3_zero })
    zox_prefab_set(e, Rotation3D, { float4_identity })
    zox_prefab_set(e, Scale1D, { 1 })
}

void set_position_from_parents(ecs_world_t *world, const ecs_entity_t parent, float3 *position3D, const float3 local_position3D) {
    if (!parent || !zox_has(parent, Position3D) || !zox_has(parent, Rotation3D)) return;
    const float3 parent_position = zox_get_value(parent, Position3D)
    const float4 parent_rotation = zox_get_value(parent, Rotation3D)
    *position3D = local_position3D;
    float4_rotate_float3_p(parent_rotation, position3D);
    float3_add_float3_p(position3D, parent_position);
}

void set_rotation_from_parents(ecs_world_t *world, const ecs_entity_t parent, float4 *rotation3D, const float4 local_rotation3D) {
    if (!parent || !zox_has(parent, Rotation3D)) return;
    const float4 parent_rotation = zox_get_value(parent, Rotation3D)
    *rotation3D = parent_rotation;
    quaternion_rotate_quaternion_p(rotation3D, local_rotation3D);
}
