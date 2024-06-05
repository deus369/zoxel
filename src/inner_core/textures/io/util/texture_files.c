// #define zox_print_texture_files

ecs_entity_t spawn_from_file_path_texture(ecs_world_t *world, const char *filepath, const unsigned char index) {
    zox_instance(prefab_texture)
    zox_name("texture_filepath")
    TextureData *textureData = zox_get_mut(e, TextureData)
    TextureSize *textureSize = zox_get_mut(e, TextureSize)
    if (textureData->value) free(textureData->value);
    textureData->value = load_texture_from_png(filepath, &textureSize->value, &textureData->length);
    zox_modified(e, TextureData)
    zox_modified(e, TextureSize)
    int calculated_length = textureSize->value.x * textureSize->value.y;
    if (textureData->length != calculated_length) zox_log(" + loaded texture issues: %i != %i\n", textureData->length, calculated_length)
    return e;
}

void load_files_textures(ecs_world_t *world) {
    // get a list of files in monsters_directory
    char* load_directory = concat_file_path(resources_path, directory_textures);
    // list_files(load_directory);
    FileList files = get_files(load_directory);
#ifdef zox_print_texture_files
    zox_log("   > textures found [%i]\n", files.count)
#endif
    files_count_textures = files.count;
    files_textures = malloc(sizeof(ecs_entity_t) * files.count);
    files_textures_hashmap = create_string_hashmap(files.count);
    for (int i = 0; i < files.count; i++) {
        char* filepath = files.files[i];
        char* filename = files.filenames[i];
        const ecs_entity_t e = spawn_from_file_path_texture(world, filepath, i);
        files_textures[i] = e;
        string_hashmap_add(files_textures_hashmap, new_string_data_clone(filename), e);
#ifdef zox_print_texture_files
        zox_log("       > [%i] texture [%s]\n", i, filepath)
#endif
    }
    free_files(&files);
    free(load_directory);
}

void dispose_files_textures(ecs_world_t *world) {
    string_hashmap_dispose(files_textures_hashmap);
    files_textures_hashmap = NULL;
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
