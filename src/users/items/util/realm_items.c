ecs_entity_t meta_item_block;

void spawn_realm_items(ecs_world_t *world, ecs_entity_t realm) {
    ItemLinks *items = zox_get_mut(realm, ItemLinks)
    resize_memory_component(ItemLinks, items, ecs_entity_t, 1)
    items->value[0] = spawn_meta_item(world, "block");
    zox_modified(realm, ItemLinks)
    meta_item_block = items->value[0];
}
