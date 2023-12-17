#define monsters_directory "voxes"character_slash

// todo: load vox_file as an entity, with filename as it's name, foroo easy use in game engine
//! load a bunch of vox files from resources/voxes
int vox_files_count = 0;
vox_file *vox_files;

void dispose_vox_files() {
#ifdef zox_disable_io
    return;
#endif
    for (int i = 0; i < vox_files_count; i++) dispose_vox_file(&vox_files[i]);
    free(vox_files);
}

void load_vox_file(const char* filename, vox_file *vox) {
#ifdef zox_disable_io
    return;
#endif
    vox->chunks = NULL;
    read_vox(filename, vox);
}

void load_files_voxes() {
    // get a list of files in monsters_directory
    char* full_monsters_directory = concat_file_path(resources_path, monsters_directory);
    list_files(full_monsters_directory);
    FileList fileList = get_files(full_monsters_directory);
    vox_files_count = fileList.count;
    vox_files = malloc(sizeof(vox_file) * vox_files_count);
    for (int i = 0; i < fileList.count; i++) {
        char* vox_path = concat_file_path(full_monsters_directory, fileList.files[i]);
        load_vox_file(vox_path, &vox_files[i]);
        free(vox_path);
    }
    free_files(fileList);
    free(full_monsters_directory);
}

    // vox_file loaded_vox;
    // return loaded_vox;
    /*vox_file loaded_vox;
    loaded_vox.chunks = NULL;
    char* vox_path = concat_file_path(resources_path, filename);
    if (read_vox(vox_path, &loaded_vox) == EXIT_SUCCESS) vox_files[index] = loaded_vox;
    else {
        vox_files[index] = loaded_vox;
        zox_log(" ! failed loading file %s\n", vox_path)
    }
    free(vox_path);*/
    /*vox_files_count = 4;
    vox_files = malloc(sizeof(vox_file) * vox_files_count);
    load_vox_file(0, vox_file_littlecube);
    load_vox_file(1, vox_file_chicken);
    load_vox_file(2, vox_file_slime);
    load_vox_file(3, vox_file_mrpenguin);*/
