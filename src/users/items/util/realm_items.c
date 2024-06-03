ecs_entity_t meta_item_block;

void spawn_realm_items(ecs_world_t *world, const ecs_entity_t realm) {
    ItemLinks *items = zox_get_mut(realm, ItemLinks)
    resize_memory_component(ItemLinks, items, ecs_entity_t, 1)
    items->value[0] = spawn_meta_item(world, "block");


    // set texture
    // zox_set(items->value[0], TextureLink, { files_textures[2] });

    const VoxelLinks *voxels = zox_get(realm, VoxelLinks)
    const Textures *textures = zox_get(voxels->value[0], Textures)
    const ecs_entity_t dirt_texture = textures->value[0];
    zox_set(items->value[0], TextureLink, { dirt_texture });


    zox_modified(realm, ItemLinks)
    meta_item_block = items->value[0];
}
