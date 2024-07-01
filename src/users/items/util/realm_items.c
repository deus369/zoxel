ecs_entity_t meta_item_block;

void spawn_realm_items(ecs_world_t *world, const ecs_entity_t realm) {
    const VoxelLinks *voxels = zox_get(realm, VoxelLinks)
    if (voxels->length == 0 || voxels->value == NULL) {
        zox_log(" ! no voxels to spawn items from\n")
        return;
    }
    const ecs_entity_t dirt_block = voxels->value[0];

    zox_get_muter(realm, ItemLinks, items)
    // clear previous
    for (int i = 0; i < items->length; i++) if (items->value[i]) zox_delete(items->value[i])

    resize_memory_component(ItemLinks, items, ecs_entity_t, 1)

    if (zox_valid(dirt_block) && zox_has(dirt_block, ZoxName) && zox_has(dirt_block, Textures)) {
        const ZoxName *voxel_name = zox_get(dirt_block, ZoxName)
        const Textures *textures = zox_get(dirt_block, Textures)
        const ecs_entity_t dirt_texture = textures->value[0];
        items->value[0] = spawn_meta_item_zox_name(world, voxel_name, prefab_item); // "block");
        zox_set(items->value[0], TextureLink, { dirt_texture });
        meta_item_block = items->value[0];
        zox_log(" + spawning item for block [%s]\n", convert_zext_to_text(voxel_name->value, voxel_name->length))
    } else {
        zox_log(" ! problem with dirt_block components name? [%i]\n", zox_has(dirt_block, ZoxName))
    }
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
