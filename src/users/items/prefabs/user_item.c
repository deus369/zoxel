ecs_entity_t spawn_user_item_quantity(ecs_world_t *world, const ecs_entity_t prefab, const ecs_entity_t user, const unsigned char quantity) {
    const ecs_entity_t e = spawn_user_item(world, prefab, user);
    zox_prefab_set(e, Quantity, { quantity })
    return e;
}
