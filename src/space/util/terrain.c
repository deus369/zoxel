void on_terrain_settings_changed(ecs_world_t *world, const ecs_entity_t realm) {
    if (!zox_has(realm, VoxelLinks)) return;
    const VoxelLinks *voxels = zox_get(realm, VoxelLinks)
    for (int k = 0; k < voxels->length; k++) {
        const ecs_entity_t voxel = voxels->value[k];
        zox_geter(voxel, TextureLinks, textures);
        for (int l = 0; l < textures->length; l++) {
            zox_set(textures->value[l], GenerateTexture, { 1 })
        }
    }
    zox_geter(realm, TilemapLink, tilemapLink)
    zox_set(tilemapLink->value, GenerateTexture, { zox_generate_texture_trigger })
}
