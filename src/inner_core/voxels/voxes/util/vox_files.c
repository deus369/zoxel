// #define zox_print_files

void load_vox_file(const char* filename, vox_file *vox) {
#ifdef zox_disable_io
    return;
#endif
    vox->chunks = NULL;
    read_vox(filename, vox);
}

void load_files_voxes(ecs_world_t *world, const ecs_entity_t prefab) {
    // get a list of files in monsters_directory
    char* full_monsters_directory = concat_file_path(resources_path, monsters_directory);
    // list_files(full_monsters_directory);
    FileList files = get_files(full_monsters_directory);
#ifdef zox_print_files
    zox_log("   > voxes found [%i]\n", files.count)
#endif
    files_voxes_count = files.count;
    files_voxes = malloc(sizeof(ecs_entity_t) * files_voxes_count);
    files_hashmap_voxes = create_string_hashmap(files_voxes_count);
    for (int i = 0; i < files.count; i++) {
        char* filepath = files.files[i];
        char* filename = files.filenames[i];
#ifdef zox_print_files
        zox_log("   > [%i] vox file [%s]\n", i, filepath)
#endif
        vox_file data;
        load_vox_file(filepath, &data);
        const ecs_entity_t e = spawn_vox_file(world, prefab, &data);
        files_voxes[i] = e;
        string_hashmap_add(files_hashmap_voxes, new_string_data_clone(filename), e);
        dispose_vox_file(&data);
        // free(filepath);
    }
    free_files(&files);
    free(full_monsters_directory);
}

void initialize_voxes(ecs_world_t *world) {
    load_files_voxes(world, prefab_vox_file);
}


void dispose_files_voxes(ecs_world_t *world) {
    string_hashmap_dispose(files_hashmap_voxes);
    files_hashmap_voxes = NULL;
    free(files_voxes);
    files_voxes = NULL;
}
