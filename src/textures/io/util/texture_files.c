// #define zox_print_texture_files

ecs_entity_t spawn_texture_filepath(ecs_world_t *world, const ecs_entity_t prefab, const char *filepath) {
    zox_instance(prefab)
    // zox_name("texture_filepath")
    TextureData *textureData = &((TextureData) { 0, NULL });
    int2 texture_size = int2_zero;
    // zox_get_muter(e, TextureData, textureData)
    // zox_get_muter(e, TextureSize, textureSize)
    // if (textureData->value) free(textureData->value);
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

void load_files_textures(ecs_world_t *world) {
    char* load_directory = concat_file_path(resources_path, directory_textures);
    FileList files = get_files(load_directory);
    files_count_textures = files.count;
    files_textures = malloc(sizeof(ecs_entity_t) * files.count);
    files_hashmap_textures = create_string_hashmap(files.count);
    zox_log_io(" + io loaded [textures] [%i]", files.count)
    for (int i = 0; i < files.count; i++) {
        char* filepath = files.files[i];
        char* filename = files.filenames[i];
        zox_log_io("   - [%i] [texture] [%s]", i, filepath)
        const ecs_entity_t e = spawn_texture_filepath(world, prefab_texture, filepath);
        if (e) string_hashmap_add(files_hashmap_textures, new_string_data_clone(filename), e);
        files_textures[i] = e;
    }
    free_files(&files);
}

void dispose_files_textures() {
    zox_log_io(" > disposing [%i] [textures]", files_hashmap_textures->size)
    string_hashmap_dispose(files_hashmap_textures);
    files_hashmap_textures = NULL;
    free(files_textures);
    files_textures = NULL;
}

/*ecs_entity_t spawn_from_file_texture(ecs_world_t *world, int index) {
    if (index < 0 || index >= files_count_textures) return 0;
    zox_instance(prefab_texture)
    zox_name("texture_file")
    // copy textureData and textureSize from file
    // ecs_entity_t source_texture = files_textures[index];
    // copy texture data over
    // idk what to do with this one
    // *textureData = zox_get_mut(
    // load_texture_from_png();
    return e;
}*/

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
        zox_log_line("! texture [%s] was not found", filename)
        return;
    }
    clone_texture_data(world, e, texture_source);
    zox_set(e, GenerateTexture, { zox_generate_texture_none })
    zox_set(e, TextureDirty, { 1 })
}

void clone_texture_entity_to_entity(ecs_world_t *world, const ecs_entity_t e, const ecs_entity_t texture_source) {
    if (!texture_source) {
        zox_log_line("! texture [%lu] was invalid", texture_source)
        return;
    }
    clone_texture_data(world, e, texture_source);
    zox_set(e, GenerateTexture, { zox_generate_texture_none })
    zox_set(e, TextureDirty, { 1 })
}
