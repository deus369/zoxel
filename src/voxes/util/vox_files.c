// #define zox_print_files

void load_vox_file(const char* filename, vox_file *vox) {
#ifdef zox_disable_io
    return;
#endif
    vox->chunks = NULL;
    read_vox(filename, vox);
}

void load_files_voxes(ecs_world_t *world, const ecs_entity_t prefab) {
    char* load_directory = concat_file_path(resources_path, directory_voxes);
    FileList files = get_files(load_directory, 0);
    files_voxes_count = files.count;
    files_voxes = malloc(sizeof(ecs_entity_t) * files_voxes_count);
    files_hashmap_voxes = create_string_hashmap(files_voxes_count);
    zox_log_io(" + io loaded [voxes] [%i]", files.count)
    for (int i = 0; i < files.count; i++) {
        char* filepath = files.files[i];
        char* filename = files.filenames[i];
        zox_log_io("   - [%i] [vox] [%s]", i, filepath)
        vox_file data;
        load_vox_file(filepath, &data);
        const ecs_entity_t e = spawn_vox_file(world, prefab, &data);
        dispose_vox_file(&data);
        if (e) string_hashmap_add(files_hashmap_voxes, new_string_data_clone(filename), e);
        files_voxes[i] = e;
    }
    free_files(&files);
}

void dispose_files_voxes(ecs_world_t *world) {
    zox_log_io(" > disposing [%i] [voxes]", files_hashmap_voxes->size)
    string_hashmap_dispose(files_hashmap_voxes);
    files_hashmap_voxes = NULL;
    free(files_voxes);
    files_voxes = NULL;
}
