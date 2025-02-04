// based off cube prefab
ecs_entity_t spawn_prefab_pickup(ecs_world_t *world, const ecs_entity_t prefab) {
    zox_prefab_child(prefab)
    zox_prefab_name("prefab_pickup")
    zox_add_tag(e, Pickup)
    prefab_add_sphere_collider(world, e, 0.15f);
    zox_prefab_set(e, OverlapEvent, { &on_overlap_pickup })
    zox_prefab_set(e, PickedUp, { pickup_state_none })
    float4 rotation_speed = quaternion_from_euler( (float3) { 0, pickup_rotaion_speed * degreesToRadians, 0 });
    zox_set(e, EternalRotation, { rotation_speed })
    return e;
}

ecs_entity_t spawn_pickup(ecs_world_t *world, const ecs_entity_t prefab, const float3 position) {
#ifdef zox_prefabs_non_textured
    const ecs_entity_t e = spawn_cube(world, prefab, position);
#else
    const ecs_entity_t e = spawn_cube_textured(world, prefab, position);
#endif
    zox_name("pickup")
    return e;
}
