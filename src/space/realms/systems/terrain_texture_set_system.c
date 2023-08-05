void TerrainTextureSetSystem(ecs_iter_t *it) {
    // todo: link directly to a voxelLinks holder instead of using local_realm (use terrain ones)
    if (!ecs_is_valid(it->world, local_realm)) return;
    const VoxelLinks *voxelLinks = ecs_get(it->world, local_realm, VoxelLinks);
    const GenerateTexture *generateTextures = ecs_field(it, GenerateTexture, 2);
    TilemapSize *tilemapSizes = ecs_field(it, TilemapSize, 3);
    TextureLinks *textureLinkss = ecs_field(it, TextureLinks, 4);
    for (int i = 0; i < it->count; i++) {
        const GenerateTexture *generateTexture = &generateTextures[i];
        if (generateTexture->value == 0) continue;
        TilemapSize *tilemapSize = &tilemapSizes[i];
        TextureLinks *textureLinks = &textureLinkss[i];
        // set first voxel texture for now
        int tilemap_length = 2 * (int) (voxelLinks->length / 2);
        // zoxel_log(" + tilemap length %i\n", tilemap_length);
        tilemapSize->value.x = tilemap_length;
        tilemapSize->value.y = tilemap_length;
        initialize_memory_component(textureLinks, ecs_entity_t, voxelLinks->length)
        for (int j = 0; j < voxelLinks->length; j++) {
            ecs_entity_t voxel_entity = voxelLinks->value[j];
            const TextureLinks *voxel_texture_links = ecs_get(it->world, voxel_entity, TextureLinks);
            if (voxel_texture_links->length > 0) textureLinks->value[j] = voxel_texture_links->value[0];
            //zoxel_log("     > voxel_texture_set [%lu] [%lu]\n", voxel_entity, textureLinks->value[j]);
        }
        // zoxel_log("    > tilemap textures linked [%lu] - count [%i]\n", it->entities[i], voxelLinks->length);
    }
} zox_declare_system(TerrainTextureSetSystem)