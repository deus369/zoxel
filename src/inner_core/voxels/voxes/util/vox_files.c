#define vox_file_chicken "voxes/monsters/chicken.vox"
#define vox_file_slime "voxes/monsters/slime.vox"
#define vox_file_mrpenguin "voxes/monsters/mrpenguin.vox"

int vox_files_count = 0;
//! load a bunch of vox files from resources/voxes
vox_file *vox_files;

void dispose_vox_files() {
    for (int i = 0; i < vox_files_count; i++) {
        dispose_vox_file(&vox_files[i]);
    }
    free(vox_files);
}

void load_vox_files() {
    vox_files_count = 3;
    vox_files = malloc(sizeof(vox_file) * vox_files_count);
    vox_file chicken_vox;
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
    free(mrpenguin_vox_path);
}