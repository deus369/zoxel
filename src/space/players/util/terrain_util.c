void on_terrain_settings_changed(ecs_world_t *world, const ecs_entity_t realm) {
    if (!zox_has(realm, VoxelLinks)) return;
    const VoxelLinks *voxelLinks = zox_get(realm, VoxelLinks)
    for (int k = 0; k < voxelLinks->length; k++) {
        ecs_entity_t voxel = voxelLinks->value[k];
        const Textures *textureLinks = zox_get(voxel, Textures)
        zox_set(textureLinks->value[0], GenerateTexture, { 1 })
    }
    if (!local_terrain) return;
    const TilemapLink *tilemapLink = zox_get(local_terrain, TilemapLink)
    zox_set(tilemapLink->value, GenerateTexture, { 1 })
}
