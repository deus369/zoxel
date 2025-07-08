ecs_entity_t meta_item_block_dirt;
ecs_entity_t meta_item_block_dark;
ecs_entity_t meta_item_block_obsidian;
ecs_entity_t meta_item_block_sand;
ecs_entity_t meta_item_block_stone;
ecs_entity_t meta_item_block_dungeon_core;

ecs_entity_t spawn_block_item(ecs_world_t *world, const ecs_entity_t block) {
    if (!zox_valid(block) || !zox_has(block, ZoxName) || !zox_has(block, Textures)) {
        zox_log_error(" ! problem with block components name? [%i]\n", zox_has(block, ZoxName))
        return 0;
    }
    // get block data
    zox_geter(block, ZoxName, voxel_name)
    zox_geter(block, Textures, textures)
    // spawn item
    const ecs_entity_t e = spawn_meta_item_zox_name(world, prefab_item, voxel_name);
    if (textures->length > 0) {
        zox_set(e, TextureLink, { textures->value[0] })
    } else {
        zox_log("! warning: [todo] implement vox item textures [%s]", zox_get_name(block))
        const ecs_entity_t blank = string_hashmap_get(files_hashmap_textures, new_string_data("blank"));
        zox_set(e, TextureLink, { blank })
        // zox_log(" ! block [%s] had no textures [%i]\n",  convert_zext_to_text(voxel_name->value, voxel_name->length), textures->length)
    }
    zox_add_tag(e, ItemBlock)
    zox_set(e, BlockLink, { block })
    // actually for grass we want to set itemLink differently
    zox_set(block, ItemLink, { e })
    // zox_set_name(item, zox_get_name(block));
    zox_name(zox_get_name(block));
    // zox_log(" + block item [%s] [%s]\n", zox_get_name(block), zox_get_name(e))
    // zox_log(" + spawning item for block [%s] textures [%i]\n", convert_zext_to_text(voxel_name->value, voxel_name->length), textures->length)
    return e;
}

void spawn_realm_items(ecs_world_t *world, const ecs_entity_t realm) {
    if (!zox_has(realm, ItemLinks)) {
        zox_log("! realm does not have ItemLinks [%lu]\n", realm)
        return;
    }
    if (!zox_has(realm, VoxelLinks)) {
        zox_log("! realm does not have VoxelLinks [%lu]\n", realm)
        return;
    }
    zox_geter(realm, VoxelLinks, voxels)
    if (!voxels) {
        zox_log("! realm voxels was null [%lu]\n", realm)
        return;
    }
    if (voxels->length == 0 || voxels->value == NULL) {
        zox_log(" ! no voxels to spawn items from\n")
        return;
    }
    // i should make a BlockItemLinks perhaps? nah  that overcomplicates
    // clear previous
    zox_geter(realm, ItemLinks, oldItems)
    if (oldItems) {
        for (int i = 0; i < oldItems->length; i++) {
            if (oldItems->value[i]) {
                zox_delete(oldItems->value[i])
            }
        }
    }
    ItemLinks *items = &((ItemLinks) { 0, NULL });
    resize_memory_component(ItemLinks, items, ecs_entity_t, voxels->length)
    for (int i = 0; i < voxels->length; i++) {
        const ecs_entity_t block = voxels->value[i];
        if (!zox_valid(block)) {
            zox_log_error("block [%i] invalid", i)
            items->value[i] = 0;
            continue;
        }
        items->value[i] = spawn_block_item(world, block);
        if (i == zox_block_grass - 1) {
            const ecs_entity_t item_block_dirt = items->value[zox_block_dirt - 1];
            zox_set(block, ItemLink, { item_block_dirt })
        }
    }
    zox_set(realm, ItemLinks, { items->length, items->value })

    meta_item_block_dirt = items->value[zox_block_dirt - 1];
    meta_item_block_obsidian = items->value[zox_block_obsidian - 1];
    meta_item_block_dark = items->value[zox_block_dark - 1];
    meta_item_block_dungeon_core = items->value[zox_block_dungeon_core - 1];
    meta_item_block_sand = items->value[zox_block_sand - 1];
    meta_item_block_stone = items->value[zox_block_stone - 1];

#ifdef zox_log_realm_generate
    zox_log(" + generated realm [items]")
#endif
}
