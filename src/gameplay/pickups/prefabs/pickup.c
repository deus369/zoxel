// base off cube prefab
ecs_entity_t spawn_prefab_pickup(ecs_world_t *world, const ecs_entity_t prefab) {
    zox_prefab_child(prefab)
    zox_prefab_name("prefab_pickup")
    zox_add_tag(e, Pickup)
    return e;
}

ecs_entity_t spawn_pickup(ecs_world_t *world, const ecs_entity_t prefab, const float3 position) {
    const ecs_entity_t e = spawn_cube(world, prefab, position);
    // zox_name("cube")
    return e;
}
