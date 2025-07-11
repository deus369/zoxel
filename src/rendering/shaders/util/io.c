void load_files_shaders(ecs_world_t *world) {
    char* load_directory = concat_file_path(resources_path, directory_shaders);
    FileList files = get_files(load_directory, 1);
    files_shaders = malloc(sizeof(ecs_entity_t) * files.count);
    files_hashmap_shaders = create_string_hashmap(files.count);
    zox_log_io(" + io loaded [shaders] [%i]", files.count)
    for (int i = 0; i < files.count; i++) {
        char* filepath = files.files[i];
        char* filename = files.filenames[i];
        zox_log_io("   - [%i] [shader] [%s]", i, filepath)
        const ecs_entity_t e = spawn_file_shader_at_path(world, prefab_file_shader, filepath);
        if (e) {
            string_hashmap_add(files_hashmap_shaders, new_string_data_clone(filename), e);
        }
        files_shaders[i] = e;
    }
    free_files(&files);
    files_count_shaders = files.count;
}

void dispose_files_shaders() {
    zox_log_io(" > disposing [%i] [shaders]", files_hashmap_shaders->size)
    string_hashmap_dispose(files_hashmap_shaders);
    files_hashmap_shaders = NULL;
    free(files_shaders);
    files_shaders = NULL;
}