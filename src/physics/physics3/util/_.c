void add_physics3D(ecs_world_t *world, const ecs_entity_t e, const float3 bounds) {
    zox_add_tag(e, Frictioned)
    zox_prefab_set(e, LastPosition3D, { float3_zero })
    zox_prefab_set(e, InitializePhysics3D, { 0 })
    zox_prefab_set(e, Velocity3D, { { 0, 0, 0 } })
    zox_prefab_set(e, Acceleration3D, { { 0, 0, 0 } })
    zox_prefab_set(e, Omega3D, { quaternion_identity })
    zox_prefab_set(e, Alpha3D, { quaternion_identity })
    zox_prefab_set(e, Gravity3D, { zox_default_gravity })
    zox_prefab_set(e, DisableGravity, { 0 })
    zox_prefab_set(e, Bounds3D, { bounds })
    zox_prefab_set(e, Grounded, { 0 })
    zox_prefab_set(e, Jump, { 0 })
    zox_prefab_set(e, DisableMovement, { 0 })
}

byte can_jump(ecs_world_t *world, const ecs_entity_t e) {
    return !zox_gett_value(e, DisableMovement) && zox_gett_value(e, Grounded);
}
