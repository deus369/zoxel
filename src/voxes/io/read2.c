// Function to get file size
long get_file_size(FILE *file) {
    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    fseek(file, 0, SEEK_SET);
    return size;
}

// Optimized function to read .vox file with adjusted axis handling
int read_vox(const char* filename, vox_file *vox) {
    FILE *file = fopen(filename, "rb");
    if (!file) {
        zox_log_errno(" ! [vox] failed to open file [%s]\n", filename);
        return EXIT_FAILURE;
    }

    // Read entire file into a single buffer
    long file_size = get_file_size(file);
    byte *file_buffer = malloc(file_size);
    if (!file_buffer) {
        zox_log_errno(" ! [vox] failed to allocate file buffer\n");
        fclose(file);
        return EXIT_FAILURE;
    }
    if (fread(file_buffer, file_size, 1, file) != 1) {
        zox_log_errno(" ! [vox] failed to read file [%s]\n", filename);
        free(file_buffer);
        fclose(file);
        return EXIT_FAILURE;
    }
    fclose(file);

    byte *ptr = file_buffer;

    // Parse header
    memcpy(&vox->header, ptr, sizeof(vox_file_header));
    ptr += sizeof(vox_file_header);
    if (strncmp(vox->header.magic, "VOX ", 4) != 0) {
        zox_log(" ! [vox] invalid magic value\n");
        free(file_buffer);
        return EXIT_FAILURE;
    }

    // Parse main chunk
    memcpy(&vox->main, ptr, sizeof(vox_file_chunk));
    ptr += sizeof(vox_file_chunk);

    // Parse pack chunk if present
    if (strncmp(ptr, "PACK", 4) == 0) {
        memcpy(&vox->pack, ptr, sizeof(vox_file_pack));
        ptr += sizeof(vox_file_pack);
    } else {
        vox->pack.model_nums = 1;
    }

    // Allocate chunks array
    vox->chunks = malloc(vox->pack.model_nums * sizeof(vox_file_chunk_child));
    if (!vox->chunks) {
        zox_log_errno(" ! [vox] failed to allocate chunks\n");
        free(file_buffer);
        return EXIT_FAILURE;
    }

    // First pass: calculate total voxel memory
    size_t total_voxel_memory = 0;
    byte *temp_ptr = ptr;
    for (int i = 0; i < vox->pack.model_nums; i++) {
        vox_file_size size;
        memcpy(&size, temp_ptr, sizeof(vox_file_size));
        temp_ptr += sizeof(vox_file_size);
        int3 xyz = size.xyz;
        int voxels_length = int3_array_size(xyz);
        total_voxel_memory += voxels_length;
        temp_ptr += 12; // Skip XYZI header: name[4], chunk_content[4], chunk_nums[4]
        int num_voxels;
        memcpy(&num_voxels, temp_ptr, 4);
        temp_ptr += 4 + num_voxels * 4;
    }

    // Allocate voxel buffer
    byte *voxel_buffer = calloc(total_voxel_memory, 1);
    if (!voxel_buffer) {
        zox_log_errno(" ! [vox] failed to allocate voxel buffer\n");
        free(vox->chunks);
        free(file_buffer);
        return EXIT_FAILURE;
    }
    byte *voxel_ptr = voxel_buffer;

    // Second pass: parse chunks and set voxel data with adjusted axis handling
    for (int i = 0; i < vox->pack.model_nums; i++) {
        memcpy(&vox->chunks[i].size, ptr, sizeof(vox_file_size));
        ptr += sizeof(vox_file_size);
        vox->chunks[i].xyzi.voxels = voxel_ptr;
        memcpy(&vox->chunks[i].xyzi.name, ptr, 4); ptr += 4;
        memcpy(&vox->chunks[i].xyzi.chunk_content, ptr, 4); ptr += 4;
        memcpy(&vox->chunks[i].xyzi.chunk_nums, ptr, 4); ptr += 4;
        int num_voxels;
        memcpy(&num_voxels, ptr, 4); ptr += 4;
        for (int j = 0; j < num_voxels; j++) {
            byte x = *ptr++;
            byte y = *ptr++;
            byte z = *ptr++;
            byte color_index = *ptr++;
            // Adjust axes: swap Y and Z, flip Z to fix backward and downward orientation
            byte adjusted_y = z; // Use Z as Y (up)
            byte adjusted_z = vox->chunks[i].size.xyz.z - 1 - y; // Flip Y to Z
            int3 position = {x, adjusted_y, adjusted_z};
            int array_index = int3_array_index(position, vox->chunks[i].size.xyz);
            #ifdef zoxel_debug_vox_read
            if (j < 32) {
                zox_log("        - voxel [%i] [x:%i y:%i z:%i] -> [index:%i]\n",
                        j, position.x, position.y, position.z, array_index);
            }
            #endif
            vox->chunks[i].xyzi.voxels[array_index] = color_index;
        }
        voxel_ptr += int3_array_size(vox->chunks[i].size.xyz);
    }

    // Parse palette if present
    if (strncmp(ptr, "RGBA", 4) == 0) {
        memcpy(&vox->palette.name, ptr, 4); ptr += 4;
        memcpy(&vox->palette.chunk_content, ptr, 4); ptr += 4;
        memcpy(&vox->palette.chunk_nums, ptr, 4); ptr += 4;
        int colors_length = vox->palette.chunk_content / 4;
        vox->palette.values = malloc(sizeof(color) * colors_length);
        if (!vox->palette.values) {
            zox_log_errno(" ! [vox] failed to allocate palette values\n");
            free(voxel_buffer);
            free(vox->chunks);
            free(file_buffer);
            return EXIT_FAILURE;
        }
        memcpy(vox->palette.values, ptr, sizeof(color) * colors_length);
        ptr += sizeof(color) * colors_length;
        vox->palette.values_length = colors_length;
        vox->palette.values_rgb = malloc(sizeof(color_rgb) * colors_length);
        if (!vox->palette.values_rgb) {
            zox_log_errno(" ! [vox] failed to allocate palette values_rgb\n");
            free(vox->palette.values);
            free(voxel_buffer);
            free(vox->chunks);
            free(file_buffer);
            return EXIT_FAILURE;
        }
        for (int i = 0; i < colors_length; i++) {
            vox->palette.values_rgb[i].r = vox->palette.values[i].r;
            vox->palette.values_rgb[i].g = vox->palette.values[i].g;
            vox->palette.values_rgb[i].b = vox->palette.values[i].b;
        }
    } else {
        int colors_length = 256;
        vox->palette.values_length = colors_length;
        vox->palette.values = malloc(sizeof(color) * colors_length);
        if (!vox->palette.values) {
            zox_log_errno(" ! [vox] failed to allocate default palette values\n");
            free(voxel_buffer);
            free(vox->chunks);
            free(file_buffer);
            return EXIT_FAILURE;
        }
        memcpy(vox->palette.values, default_palette, sizeof(color) * colors_length);
        vox->palette.values_rgb = malloc(sizeof(color_rgb) * colors_length);
        if (!vox->palette.values_rgb) {
            zox_log_errno(" ! [vox] failed to allocate default palette values_rgb\n");
            free(vox->palette.values);
            free(voxel_buffer);
            free(vox->chunks);
            free(file_buffer);
            return EXIT_FAILURE;
        }
        for (int i = 0; i < colors_length; i++) {
            vox->palette.values_rgb[i].r = vox->palette.values[i].r;
            vox->palette.values_rgb[i].g = vox->palette.values[i].g;
            vox->palette.values_rgb[i].b = vox->palette.values[i].b;
        }
    }

    free(file_buffer);
    return EXIT_SUCCESS;
}