int character_inventory_count = 8; // 8 | 16; // having blank items seems to b reak it
byte test_give_npcs_blocks = 1;

void spawn_character_items(ecs_world_t *world, spawned_character3D_data *data) {
    if (!data->p) {
        // todo: give them mushroom! or simple block for now
        if (test_give_npcs_blocks) {
            ItemLinks items = (ItemLinks) { 0, NULL };
            // get voxels
            zox_geter(data->realm, VoxelLinks, voxels)
            // give npc random voxel
            const ecs_entity_t block = voxels->value[rand() % voxels->length];
            if (zox_valid(block)) {
                zox_geter(block, ItemLink, itemLink)
                if (zox_valid(itemLink->value)) {
                    const ecs_entity_t item = spawn_user_item(world, itemLink->value, data->e);
                    zox_set(item, Quantity, { 1 + rand() % 3 })
                    add_to_ItemLinks(&items, item);
                    zox_set_ptr(data->e, ItemLinks, items)
                }
            }
        }
        return;
    }

    int inventory_count = character_inventory_count;
    if (test_items_blocks) {
        inventory_count = 16;
    }

    ItemLinks *items = &((ItemLinks) { 0, NULL });
    initialize_memory_component(ItemLinks, items, ecs_entity_t, inventory_count)
    if (!items->value) {
        zox_log_error(" ! failed allocating memory for items")
        return;
    }
    for (int i = 0; i < items->length; i++) {
        items->value[i] = 0; // blanks are item slots
    }
    // first block
    /*if (meta_item_block) {
        const ecs_entity_t item_block = spawn_user_item(world, meta_item_block, e);
        // set item data, quantity here
        // zox_set_name(item_block, "block"); // shold inherit name from meta
        // link up
        items->value[0] = item_block;
        // zox_log(" + spawned inventory item [%lu] character [%lu]\n", item_block, e)
    } else {
        zox_log(" ! meta_item_block not found\n")
    }*/
    int place_index = 0;
    if (test_items_blocks && data->p) {
        // get voxels
        zox_geter(data->realm, VoxelLinks, voxels)
        for (int i = 0; i < voxels->length; i++) {
            if (i >= items->length) {
                break;
            }
            const ecs_entity_t block = voxels->value[i];
            if (!zox_valid(block)) {
                zox_log_error("block invalid [%i]", i)
                continue;
            }
            zox_geter(block, ItemLink, itemLink)
            if (!zox_valid(itemLink->value)) {
                zox_log_error("block item invalid [%i]", i)
                continue;
            }
            items->value[place_index++] = spawn_user_item(world, itemLink->value, data->e);
            zox_set(items->value[place_index - 1], Quantity, { 64 })
        }
    }
    zox_set(data->e, ItemLinks, { items->length, items->value })
}
