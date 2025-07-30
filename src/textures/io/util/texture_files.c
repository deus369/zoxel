// #define zox_print_texture_files
void load_files_textures(ecs_world_t *world) {
    char* load_directory = concat_file_path(resources_path, directory_textures);
    zox_logv("  - Loading Files Textures [%s]", load_directory);
    FileList files = get_files(load_directory, 0);
    files_count_textures = files.count;
    files_textures = malloc(sizeof(ecs_entity_t) * files.count);
    files_hashmap_textures = create_string_hashmap(files.count);
    zox_log_io(" + io loaded [textures] [%i]", files.count)
    for (int i = 0; i < files.count; i++) {
        char* filepath = files.files[i];
        char* filename = files.filenames[i];
        zox_log_io("   - [%i] [texture] [%s]", i, filepath)
        const ecs_entity_t e = spawn_texture_filepath(world, prefab_texture, filepath);
        if (e) {
            string_hashmap_add(files_hashmap_textures, new_string_data_clone(filename), e);
        }
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