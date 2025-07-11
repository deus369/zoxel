ecs_entity_t spawn_texture_filepath(ecs_world_t *world, const ecs_entity_t prefab, const char *filepath) {
    zox_instance(prefab)
    zox_name("texture_filepath")
    TextureData *textureData = &((TextureData) { 0, NULL });
    int2 texture_size = int2_zero;
    textureData->value = load_texture_from_png(filepath, &texture_size);
    textureData->length = (texture_size.x * texture_size.y);
    if (!textureData->value) {
        zox_log(" ! load error [texture null] at [%s]\n", filepath)
        zox_delete(e)
        return 0;
    }
    zox_set(e, TextureData, { textureData->length, textureData->value })
    zox_set(e, TextureSize, { texture_size })
    #ifdef zox_disable_io_textures
    zox_log(" ! texture io disabled at [%s]\n", filepath)
    zox_delete(e)
    return 0;
    #endif
    return e;
}

ecs_entity_t spawn_texture_filename(ecs_world_t *world, char *filename) {
    const ecs_entity_t source = string_hashmap_get(files_hashmap_textures, new_string_data(filename));
    zox_instance(prefab_texture)
    zox_name("texture_filename")
    zox_set(e, GenerateTexture, { zox_generate_texture_none })
    clone_texture_data(world, e, source);
    zox_set(e, TextureDirty, { 1 })
    return e;
}

void clone_texture_to_entity(ecs_world_t *world, const ecs_entity_t e, char *filename) {
    const ecs_entity_t texture_source = string_hashmap_get(files_hashmap_textures, new_string_data(filename));
    if (!texture_source) {
        zox_log("! texture [%s] was not found", filename)
        return;
    }
    clone_texture_data(world, e, texture_source);
    zox_set(e, GenerateTexture, { zox_generate_texture_none })
    zox_set(e, TextureDirty, { 1 })
}

void clone_texture_entity_to_entity(ecs_world_t *world, const ecs_entity_t e, const ecs_entity_t texture_source) {
    if (!texture_source) {
        zox_log("! texture [%lu] was invalid", texture_source)
        return;
    }
    clone_texture_data(world, e, texture_source);
    zox_set(e, GenerateTexture, { zox_generate_texture_none })
    zox_set(e, TextureDirty, { 1 })
}