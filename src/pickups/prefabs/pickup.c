// based off cube prefab
ecs_entity_t spawn_prefab_pickup(ecs_world_t *world, const ecs_entity_t prefab) {
    float pickup_radius = 0.15f;
    float4 rotation_speed = quaternion_from_euler( (float3) { 0, pickup_rotaion_speed * degreesToRadians, 0 });
    zox_prefab_child(prefab)
    zox_prefab_name("prefab_pickup")
    zox_add_tag(e, Pickup)
    zox_prefab_set(e, PickedUp, { pickup_state_none })
    zox_prefab_set(e, EternalRotation, { rotation_speed })
    zox_prefab_set(e, OverlapEvent, { &on_overlap_pickup })
    // collider
    zox_add_tag(e, SphereCollider)
    zox_prefab_set(e, SphereRadius, { pickup_radius })
    zox_prefab_set(e, CollisionDisabled, { 0 })
    return e;
}

ecs_entity_t spawn_pickup(ecs_world_t *world, const float3 position, const ecs_entity_t voxel) {
    ecs_entity_t e;
#ifdef zox_prefabs_non_textured
    e = spawn_cube(world, prefab_pickup_basic, position);
#else
    if (zox_has(voxel, Textures)) {
        zox_geter(voxel, Textures, textures)
        if (textures->length) {
            if (textures->length == 1) {
                const ecs_entity_t texture = textures->value[0];
                e = spawn_cube_textured(world, prefab_pickup, position, texture);
            } else {
                const ecs_entity_t texture = textures->value[block_side_down];
                e = spawn_cube_textured(world, prefab_pickup, position, texture);
            }
        } else {
            e = spawn_cube(world, prefab_pickup_basic, position);
        }
    } else {
        e = spawn_cube(world, prefab_pickup_basic, position);
    }
#endif
    zox_name("pickup")
    return e;
}
