#define monsters_directory "voxes"character_slash
#define vox_file_littlecube monsters_directory"littlecube.vox"
#define vox_file_chicken monsters_directory"chicken.vox"
#define vox_file_slime monsters_directory"slime.vox"
#define vox_file_mrpenguin monsters_directory"mrpenguin.vox"

int vox_files_count = 0;
//! load a bunch of vox files from resources/voxes
vox_file *vox_files;

void dispose_vox_files() {
#ifdef zox_disable_io
    return;
#endif
    for (int i = 0; i < vox_files_count; i++) dispose_vox_file(&vox_files[i]);
    free(vox_files);
}

void load_vox_file(int index, const char* filename) {
#ifdef zox_disable_io
    return;
#endif
    vox_file loaded_vox;
    loaded_vox.chunks = NULL;
    char* vox_path = concat_file_path(resources_path, filename);
    if (read_vox(vox_path, &loaded_vox) == EXIT_SUCCESS) vox_files[index] = loaded_vox;
    else {
        vox_files[index] = loaded_vox;
        zox_log(" ! failed loading file %s\n", vox_path)
    }
    free(vox_path);
}

void load_vox_files() {
    vox_files_count = 4;
    vox_files = malloc(sizeof(vox_file) * vox_files_count);
    load_vox_file(0, vox_file_littlecube);
    load_vox_file(1, vox_file_chicken);
    load_vox_file(2, vox_file_slime);
    load_vox_file(3, vox_file_mrpenguin);
}
