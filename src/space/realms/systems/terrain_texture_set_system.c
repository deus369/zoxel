void TerrainTextureSetSystem(ecs_iter_t *it) {
    // todo: link directly to a voxelLinks holder instead of using local_realm (use terrain ones)
    ecs_world_t *world = it->world;
    if (!ecs_is_valid(world, local_realm)) return;
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
        // zoxel_log(" + tilemap length %i\n", tilemap_length);
        tilemapSize->value.x = tilemap_length;
        tilemapSize->value.y = tilemap_length;
        resize_memory_component(TextureLinks, textureLinks, ecs_entity_t, voxelLinks->length)
        for (int j = 0; j < voxelLinks->length; j++) {
            ecs_entity_t voxel_entity = voxelLinks->value[j];
            const Textures *voxel_texture_links = zox_get(voxel_entity, Textures)
            if (voxel_texture_links->length > 0) textureLinks->value[j] = voxel_texture_links->value[0];
            //zoxel_log("     > voxel_texture_set [%lu] [%lu]\n", voxel_entity, textureLinks->value[j]);
        }
        generateTexture->value = 2;
        // zoxel_log("    > tilemap textures linked [%lu] - count [%i]\n", it->entities[i], voxelLinks->length);
    }
} zox_declare_system(TerrainTextureSetSystem)
