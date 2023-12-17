#define directory_textures "textures"character_slash

int files_count_textures = 0;
ecs_entity_t *files_textures;

ecs_entity_t spawn_from_file_path_texture(ecs_world_t *world, const char *filepath) {
    zox_instance(prefab_texture)
    zox_name("texture_filepath")
    TextureData *textureData = zox_get_mut(e, TextureData)
    TextureSize *textureSize = zox_get_mut(e, TextureSize)
    load_texture_from_png(filepath, textureData, textureSize);
    // zox_log("   > loaded texture [%s] with size [%ix%i] length: %i\n", filepath, textureSize->value.x, textureSize->value.y, textureData->length)
    // for (int i = 0; i < 16; i++) zox_log("color %ix%ix%i\n", textureData->value[i].r, textureData->value[i].g, textureData->value[i].b)
    zox_modified(e, TextureData)
    zox_modified(e, TextureSize)
#ifdef zoxel_debug_spawns
    zox_log(" + spawned texture [%lu]\n", e)
#endif
    return e;
}

void load_files_textures(ecs_world_t *world) {
    // get a list of files in monsters_directory
    char* load_directory = concat_file_path(resources_path, directory_textures);
    // list_files(load_directory);
    FileList files = get_files(load_directory);
    zox_log("   > textures found [%i]\n", files.count)
    files_count_textures = files.count;
    files_textures = malloc(sizeof(ecs_entity_t) * files.count);
    for (int i = 0; i < files.count; i++) {
        char* filepath = concat_file_path(load_directory, files.files[i]);
        zox_log("       > texture file [%s]\n", filepath)
        // load texture - filepath
        files_textures[i] = spawn_from_file_path_texture(world, filepath);
        free(filepath);
    }
    free_files(files);
    free(load_directory);
}

void dispose_files_textures(ecs_world_t *world) {
    // for (int i = 0; i < files_count_textures; i++) zox_delete(files_textures[i])
    free(files_textures);
}

ecs_entity_t spawn_from_file_texture(ecs_world_t *world, int index) {
    if (index < 0 || index >= files_count_textures) return 0;
    zox_instance(prefab_texture)
    zox_name("texture_file")
    // copy textureData and textureSize from file
    ecs_entity_t source_texture = files_textures[index];
    // copy texture data over
    // idk what to do with this one
    // *textureData = zox_get_mut(
    // load_texture_from_png();
#ifdef zoxel_debug_spawns
    zox_log(" + spawned texture [%lu]\n", e)
#endif
    return e;
}
