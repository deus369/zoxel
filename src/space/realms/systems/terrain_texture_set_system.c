void TerrainTextureSetSystem(ecs_iter_t *it) {
    // todo: link directly to a voxelLinks holder instead of using local_realm (use terrain ones)
    zox_iter_world()
    if (!zox_valid(local_realm)) return;
    const VoxelLinks *voxelLinks = zox_get(local_realm, VoxelLinks)
    GenerateTexture *generateTextures = ecs_field(it, GenerateTexture, 2);
    TilemapSize *tilemapSizes = ecs_field(it, TilemapSize, 3);
    TextureLinks *textureLinkss = ecs_field(it, TextureLinks, 4);
    for (int i = 0; i < it->count; i++) {
        GenerateTexture *generateTexture = &generateTextures[i];
        if (generateTexture->value != 1) continue;
        TilemapSize *tilemapSize = &tilemapSizes[i];
        TextureLinks *textureLinks = &textureLinkss[i];
        // set first voxel texture for now
        int tilemap_length = 2 * (int) (voxelLinks->length / 2);
        tilemapSize->value.x = tilemap_length;
        tilemapSize->value.y = tilemap_length;
        resize_memory_component(TextureLinks, textureLinks, ecs_entity_t, voxelLinks->length)
        for (int j = 0; j < voxelLinks->length; j++) {
            ecs_entity_t voxel_entity = voxelLinks->value[j];
            const Textures *voxel_texture_links = zox_get(voxel_entity, Textures)
            if (voxel_texture_links->length > 0) textureLinks->value[j] = voxel_texture_links->value[0];
        }
        generateTexture->value = 2;
    }
} zox_declare_system(TerrainTextureSetSystem)
