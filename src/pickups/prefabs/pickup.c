// based off cube prefab
ecs_entity_t spawn_prefab_pickup(ecs_world_t *world, const ecs_entity_t prefab) {
    float pickup_radius = 0.15f;
    float4 rotation_speed = quaternion_from_euler( (float3) { 0, pickup_rotaion_speed * degreesToRadians, 0 });
    zox_prefab_child(prefab)
    zox_prefab_name("pickup")
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

ecs_entity_t spawn_pickup_basic(ecs_world_t *world,
    const float3 position)
{
    ecs_entity_t e = spawn_cube(world, prefab_pickup_basic, position);
    zox_name("pickup_basic")
    return e;
}

ecs_entity_t spawn_pickup_block(ecs_world_t *world,
    const float3 position,
    const ecs_entity_t block)
{
#ifdef zox_prefabs_non_textured
    ecs_entity_t e = spawn_cube(world, prefab_pickup_basic, position);
#else
    ecs_entity_t texture = 0;

    if (zox_valid(block) && zox_has(block, TextureLinks)) {
        zox_geter(block, TextureLinks, textures)
        if (textures->length) {
            if (textures->length == 1) {
                texture = textures->value[0];
            } else {
                texture = textures->value[block_side_down];
            }
        }
    }

    ecs_entity_t e;
    if (zox_valid(texture)) {
        e = spawn_cube_textured(world, prefab_pickup, position, texture);
    } else {
        e = spawn_cube(world, prefab_pickup_basic, position);
    }
#endif
    zox_name("pickup")
    return e;
}