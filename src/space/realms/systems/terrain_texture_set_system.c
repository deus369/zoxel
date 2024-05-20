void TerrainTextureSetSystem(ecs_iter_t *it) {
    zox_iter_world()
    zox_field_in(RealmLink, realmLinks, 1)
    zox_field_out(GenerateTexture, generateTextures, 2)
    zox_field_out(TilemapSize, tilemapSizes, 3)
    zox_field_out(TextureLinks, textureLinkss, 4)
    for (int i = 0; i < it->count; i++) {
        zox_field_i_in(RealmLink, realmLinks, realmLink)
        if (!zox_valid(realmLink->value) || !zox_has(realmLink->value, VoxelLinks)) continue;
        zox_field_i_out(GenerateTexture, generateTextures, generateTexture)
        if (generateTexture->value != 1) continue;
        zox_field_i_out(TilemapSize, tilemapSizes, tilemapSize)
        zox_field_i_out(TextureLinks, textureLinkss, textureLinks)
        const VoxelLinks *voxelLinks = zox_get(realmLink->value, VoxelLinks)
        // set first voxel texture for now
        int tilemap_length = 2 * (int) (voxelLinks->length / 2);
        tilemapSize->value.x = tilemap_length;
        tilemapSize->value.y = tilemap_length;
        resize_memory_component(TextureLinks, textureLinks, ecs_entity_t, voxelLinks->length)
        for (int j = 0; j < voxelLinks->length; j++) {
            const ecs_entity_t voxel_entity = voxelLinks->value[j];
            const Textures *voxel_texture_links = zox_get(voxel_entity, Textures)
            if (voxel_texture_links->length > 0) textureLinks->value[j] = voxel_texture_links->value[0];
        }
        generateTexture->value = 2;
    }
} zox_declare_system(TerrainTextureSetSystem)
