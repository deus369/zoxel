#define monsters_directory "voxes/" // monsters/
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

void load_vox_file(int index, char* filename) {
#ifdef zox_disable_io
    return;
#endif
    vox_file loaded_vox;
    loaded_vox.chunks = NULL;
    char* vox_path = concat_file_path(resources_path, filename);
    if (read_vox(vox_path, &loaded_vox) == EXIT_SUCCESS) vox_files[index] = loaded_vox;
    else {
        vox_files[index] = loaded_vox;
        zoxel_log(" ! failed loading file %s\n", filename);
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

    /*vox_file chicken_vox;
    char* chicken_vox_path = concat_file_path(resources_path, vox_file_chicken);
    if (read_vox(chicken_vox_path, &chicken_vox) == EXIT_SUCCESS) {
        vox_files[0] = chicken_vox;
    }
    free(chicken_vox_path);
    vox_file vox_slime;
    char* slime_vox_path = concat_file_path(resources_path, vox_file_slime);
    if (read_vox(slime_vox_path, &vox_slime) == EXIT_SUCCESS) {
        vox_files[1] = vox_slime;
    }
    free(slime_vox_path);
    vox_file vox_mrpenguin;
    char* mrpenguin_vox_path = concat_file_path(resources_path, vox_file_mrpenguin);
    if (read_vox(mrpenguin_vox_path, &vox_mrpenguin) == EXIT_SUCCESS) {
        vox_files[2] = vox_mrpenguin;
    }
    free(mrpenguin_vox_path);*/
