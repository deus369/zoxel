// triggers on VoxelsDirty flag
void TerrainTextureSetSystem(ecs_iter_t *it) {
    zox_field_world()
    zox_field_in(RealmLink, realmLinks, 1)
    zox_field_out(GenerateTexture, generateTextures, 2)
    zox_field_out(TilemapSize, tilemapSizes, 3)
    zox_field_out(TextureLinks, textureLinkss, 4)
    for (int i = 0; i < it->count; i++) {
        zox_field_i(RealmLink, realmLinks, realmLink)
        if (!zox_valid(realmLink->value) || !zox_has(realmLink->value, VoxelLinks)) {
            zox_log_error("invalid realm in [TerrainTextureSetSystem]")
            continue;
        }
        zox_geter(realmLink->value, VoxelsDirty, voxelsDirty)
        if (!voxelsDirty->value) {
            continue;
        }
        // wait for realm to generate, voxels and textures
        zox_geter(realmLink->value, GenerateRealm, generateRealm)
        if (generateRealm->value) {
            continue;
        }
        zox_field_o(GenerateTexture, generateTextures, generateTexture)
        zox_field_o(TilemapSize, tilemapSizes, tilemapSize)
        zox_field_o(TextureLinks, textureLinkss, textureLinks)
        zox_set(realmLink->value, VoxelsDirty, { 0 })
        zox_geter(realmLink->value, VoxelLinks, blocks)
        int textures_count = 0;
        for (int j = 0; j < blocks->length; j++) {
            const ecs_entity_t block = blocks->value[j];
            if (zox_valid(block)) {
                zox_geter(block, Textures, voxel_texture_links)
                textures_count += voxel_texture_links->length;
            }
        }
        resize_memory_component(TextureLinks, textureLinks, ecs_entity_t, textures_count)
        int tilemap_length = next_power_of_two(textures_count);
        tilemapSize->value = (int2) { tilemap_length, tilemap_length };
        int l = 0;
        for (int j = 0; j < blocks->length; j++) {
            const ecs_entity_t block = blocks->value[j];
            if (zox_valid(block)) {
                const Textures *voxel_texture_links = zox_get(block, Textures)
                for (int k = 0; k < voxel_texture_links->length; k++) {
                    textureLinks->value[l++] = voxel_texture_links->value[k];
                }
            }
        }
        generateTexture->value = zox_generate_texture_trigger;
    }
} zox_declare_system(TerrainTextureSetSystem)