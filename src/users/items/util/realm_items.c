ecs_entity_t meta_item_block_dirt;
ecs_entity_t meta_item_block_dark;
ecs_entity_t meta_item_block_obsidian;
ecs_entity_t meta_item_block_sand;
ecs_entity_t meta_item_block_stone;

ecs_entity_t spawn_block_item(ecs_world_t *world, const ecs_entity_t block) {
    if (zox_valid(block) && zox_has(block, ZoxName) && zox_has(block, Textures)) {
        // get block dataww
        const ZoxName *voxel_name = zox_get(block, ZoxName)
        const Textures *textures = zox_get(block, Textures)
        // spawn item
        const ecs_entity_t e = spawn_meta_item_zox_name(world, prefab_item, voxel_name);
        if (textures->length > 0) {
            zox_set(e, TextureLink, { textures->value[0] })
        } else {
            // zox_set(item, TextureLink, { 0 })
            // zox_log(" ! block [%s] had no textures [%i]\n",  convert_zext_to_text(voxel_name->value, voxel_name->length), textures->length)
        }
        zox_add_tag(e, ItemBlock)
        zox_set(e, BlockLink, { block })
        zox_set(block, ItemLink, { e })
        // zox_set_name(item, zox_get_name(block));
        zox_name(zox_get_name(block));
        // zox_log(" + block item [%s] [%s]\n", zox_get_name(block), zox_get_name(e))
        // zox_log(" + spawning item for block [%s] textures [%i]\n", convert_zext_to_text(voxel_name->value, voxel_name->length), textures->length)
        return e;
    } else {
        zox_log(" ! problem with block components name? [%i]\n", zox_has(block, ZoxName))
        return 0;
    }
}

void spawn_realm_items(ecs_world_t *world, const ecs_entity_t realm) {
    const VoxelLinks *voxels = zox_get(realm, VoxelLinks)
    if (voxels->length == 0 || voxels->value == NULL) {
        zox_log(" ! no voxels to spawn items from\n")
        return;
    }
    // i should make a BlockItemLinks perhaps? nah  that overcomplicates
    zox_get_muter(realm, ItemLinks, items)
    // clear previous
    for (int i = 0; i < items->length; i++) if (items->value[i]) zox_delete(items->value[i])
    resize_memory_component(ItemLinks, items, ecs_entity_t, voxels->length)

    for (int i = 0; i < voxels->length; i++) {
        items->value[i] = spawn_block_item(world, voxels->value[i]);
    }
    meta_item_block_dirt = items->value[zox_block_dirt - 1];
    meta_item_block_obsidian = items->value[zox_block_obsidian - 1];
    meta_item_block_dark = items->value[zox_block_dark - 1];
    meta_item_block_sand = items->value[zox_block_sand - 1];
    meta_item_block_stone = items->value[zox_block_stone - 1];

#ifdef zox_log_realm_generate
    zox_log(" + generated realm [items]\n")
#endif
}


/*void respawn_realm_items(ecs_world_t *world, const ecs_entity_t realm) {
    zox_get_mutt(realm, ItemLinks, itemLinks)
    for (int i = 0; i < itemLinks->length; i++) zox_delete(itemLinks->value[i])
    clear_memory_component(ItemLinks, itemLinks)
    spawn_realm_items(world, realm);
}*/


// dirt item
// since memory moved with flecs, do again
// voxels = zox_get(realm, VoxelLinks)
// const ecs_entity_t dirt_block = voxels->value[0];
