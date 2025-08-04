// triggers on VoxelsDirty flag
void TerrainTextureSetSystem(ecs_iter_t *it) {
    zox_sys_world()
    zox_sys_begin()
    zox_sys_in(RealmLink)
    zox_sys_out(GenerateTexture)
    zox_sys_out(TilemapSize)
    zox_sys_out(TextureLinks)
    for (int i = 0; i < it->count; i++) {
        zox_sys_i(RealmLink, realmLink)
        zox_sys_o(GenerateTexture, generateTexture)
        zox_sys_o(TilemapSize, tilemapSize)
        zox_sys_o(TextureLinks, textureLinks)
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
        clear_memory_component(TextureLinks, textureLinks)
        zox_geter(realmLink->value, VoxelLinks, blocks)
        for (int j = 0; j < blocks->length; j++) {
            const ecs_entity_t block = blocks->value[j];
            if (!zox_valid(block)) {
                continue;
            }
            zox_geter(block, TextureLinks, block_textures)
            for (int k = 0; k < block_textures->length; k++) {
                const ecs_entity_t block_texture =  block_textures->value[k];
                add_to_TextureLinks(textureLinks, block_texture);
            }
        }
        int tilemap_length = next_power_of_two_root(textureLinks->length);
        tilemapSize->value = int2_single(tilemap_length);
        zox_set(realmLink->value, VoxelsDirty, { 0 })
        generateTexture->value = zox_generate_texture_trigger;
        // zox_log("tilemap count [%i] length [%i]", textureLinks->length, tilemap_length)
    }
} zox_declare_system(TerrainTextureSetSystem)