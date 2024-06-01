// #define zox_print_files

ecs_entity_t spawn_from_file_path_texture(ecs_world_t *world, const char *filepath, const unsigned char index) {
    zox_instance(prefab_texture)
    zox_name("texture_filepath")
    TextureData *textureData = zox_get_mut(e, TextureData)
    TextureSize *textureSize = zox_get_mut(e, TextureSize)
    if (textureData->value) free(textureData->value);
    textureData->value = load_texture_from_png(filepath, &textureSize->value, &textureData->length);
    zox_modified(e, TextureData)
    zox_modified(e, TextureSize)
    // zox_log("   > loaded texture [%s] with size [%ix%i] length: %i\n", filepath, textureSize->value.x, textureSize->value.y, textureData->length)
    // if (index == 2) for (int i = 0; i < 16; i++) zox_log("      - color %ix%ix%ix%i\n", textureData->value[i].r, textureData->value[i].g, textureData->value[i].b, textureData->value[i].b)
    int calculated_length = textureSize->value.x * textureSize->value.y;
    if (textureData->length != calculated_length) zox_log(" + loaded texture issues: %i != %i\n", textureData->length, calculated_length)
    return e;
}

void load_files_textures(ecs_world_t *world) {
    // get a list of files in monsters_directory
    char* load_directory = concat_file_path(resources_path, directory_textures);
    // list_files(load_directory);
    FileList files = get_files(load_directory);
#ifdef zox_print_files
    zox_log("   > textures found [%i]\n", files.count)
#endif
    files_count_textures = files.count;
    files_textures = malloc(sizeof(ecs_entity_t) * files.count);
    for (int i = 0; i < files.count; i++) {
        char* filepath = concat_file_path(load_directory, files.files[i]);
        files_textures[i] = spawn_from_file_path_texture(world, filepath, i);
#ifdef zox_print_files
        zox_log("       > [%i] texture [%s]\n", i, filepath)
#endif
        free(filepath);
    }
    free_files(files);
    free(load_directory);
}

void dispose_files_textures(ecs_world_t *world) {
    // for (int i = 0; i < files_count_textures; i++) zox_delete(files_textures[i])
    free(files_textures);
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
