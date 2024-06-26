const int inventory_count = 16; // 10; // having blank items seems to b reak it

void spawn_character_items(ecs_world_t *world, const ecs_entity_t e, const ecs_entity_t player) {
    if (!player) return;
    ItemLinks *items = zox_get_mut(e, ItemLinks)
    if (!items) return;
    initialize_memory_component(ItemLinks, items, ecs_entity_t, inventory_count)
    if (!items->value) {
        zox_log(" ! failed allocating memory for items\n")
        return;
    }
    for (int i = 0; i < items->length; i++) items->value[i] = 0; // blanks are item slots
    // first block
    if (meta_item_block) {
        const ecs_entity_t item_block = spawn_user_item(world, meta_item_block, e);
        // set item data, quantity here
        // zox_set_name(item_block, "block"); // shold inherit name from meta
        // link up
        items->value[0] = item_block;
        // zox_log(" + spawned inventory item [%lu] character [%lu]\n", item_block, e)
    } else {
        zox_log(" ! meta_item_block not found\n")
    }
    zox_modified(e, ItemLinks)
}
