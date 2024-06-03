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
    vox_files_count = files.count;
    vox_files = malloc(sizeof(ecs_entity_t) * vox_files_count);
    for (int i = 0; i < files.count; i++) {
        char* filepath = files.files[i]; // concat_file_path(full_monsters_directory, files.files[i]);
#ifdef zox_print_files
        zox_log("   > [%i] vox file [%s]\n", i, filepath)
#endif
        vox_file data;
        load_vox_file(filepath, &data);
        const ecs_entity_t e = spawn_vox_file(world, prefab, &data);
        vox_files[i] = e;
        dispose_vox_file(&data);
        // free(filepath);
    }
    free_files(&files);
    free(full_monsters_directory);
}

void initialize_voxes(ecs_world_t *world) {
    load_files_voxes(world, prefab_vox_file);
}
