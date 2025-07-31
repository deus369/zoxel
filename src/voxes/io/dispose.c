

void dispose_vox_file(vox_file *vox) {
    if (vox->chunks) {
        // first free children voxels
        for (int i = 0; i < vox->pack.model_nums; i++) {
            if (vox->chunks[i].xyzi.voxels) {
                free(vox->chunks[i].xyzi.voxels);
            }
        }
        free(vox->chunks);    // children chunks
    }
    if (vox->palette.values) {
        free(vox->palette.values);  // pallete colorRGBs
    }
    if (vox->palette.values_rgb) {
        free(vox->palette.values_rgb);  // pallete colorRGBs
    }
}
