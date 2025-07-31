// Runtime toggle for timing logs
byte zox_time_load_vox = 0;

// Function to get file size
long get_file_size(FILE *file) {
    if (!file) return -1;
    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    fseek(file, 0, SEEK_SET);
    return size;
}

// Optimized function to read .vox file with adjusted axis handling
int read_vox(const char* filename, vox_file *vox) {
    double start_total = get_time_ms();
    double start, section_sum = 0.0;

    // Read file
    start = get_time_ms();
    FILE *file = fopen(filename, "rb");
    if (!file) {
        zox_log(" ! [vox] failed to open file [%s]", filename);
        return EXIT_FAILURE;
    }
    long file_size = get_file_size(file);
    if (file_size <= 0) {
        zox_log(" ! [vox] invalid file size for [%s]", filename);
        fclose(file);
        return EXIT_FAILURE;
    }
    byte *file_buffer = malloc(file_size);
    if (!file_buffer || fread(file_buffer, file_size, 1, file) != 1) {
        zox_log(" ! [vox] failed to read file [%s]", filename);
        free(file_buffer);
        fclose(file);
        return EXIT_FAILURE;
    }
    fclose(file);
    double file_read_time = get_time_ms() - start;
    section_sum += file_read_time;
    if (zox_time_load_vox) zox_log(" + [vox] file read time: %.2f ms", file_read_time);

    byte *ptr = file_buffer;

    // Parse header and main chunk
    start = get_time_ms();
    if (ptr + sizeof(vox_file_header) + sizeof(vox_file_chunk) > file_buffer + file_size) {
        zox_log(" ! [vox] file too small for header or main chunk");
        free(file_buffer);
        return EXIT_FAILURE;
    }
    memcpy(&vox->header, ptr, sizeof(vox_file_header));
    ptr += sizeof(vox_file_header);
    if (strncmp(vox->header.magic, "VOX ", 4) != 0) {
        zox_log(" ! [vox] invalid magic value");
        free(file_buffer);
        return EXIT_FAILURE;
    }
    memcpy(&vox->main, ptr, sizeof(vox_file_chunk));
    ptr += sizeof(vox_file_chunk);

    // Parse pack chunk
    if (ptr + 4 <= file_buffer + file_size && !strncmp((char*)ptr, "PACK", 4)) {
        if (ptr + sizeof(vox_file_pack) > file_buffer + file_size) {
            zox_log(" ! [vox] file too small for pack chunk");
            free(file_buffer);
            return EXIT_FAILURE;
        }
        memcpy(&vox->pack, ptr, sizeof(vox_file_pack));
        ptr += sizeof(vox_file_pack);
    } else {
        vox->pack.model_nums = 1;
    }
    if (vox->pack.model_nums <= 0) {
        zox_log(" ! [vox] invalid model_nums: %d", vox->pack.model_nums);
        free(file_buffer);
        return EXIT_FAILURE;
    }
    if (zox_time_load_vox) zox_log(" + [vox] model_nums: %d", vox->pack.model_nums);

    // Allocate chunks and parse in single pass
    vox->chunks = malloc(vox->pack.model_nums * sizeof(vox_file_chunk_child));
    if (!vox->chunks) {
        zox_log(" ! [vox] failed to allocate chunks");
        free(file_buffer);
        return EXIT_FAILURE;
    }
    size_t total_voxel_memory = 0;
    byte *voxel_ptr = NULL;
    for (int i = 0; i < vox->pack.model_nums; i++) {
        if (ptr + sizeof(vox_file_size) + 12 > file_buffer + file_size) {
            zox_log(" ! [vox] file too small for chunk %d", i);
            free(vox->chunks);
            free(file_buffer);
            return EXIT_FAILURE;
        }
        vox_file_size size;
        memcpy(&size, ptr, sizeof(vox_file_size));
        ptr += sizeof(vox_file_size);
        vox->chunks[i].size.xyz.x = size.xyz.x;
        vox->chunks[i].size.xyz.y = size.xyz.z; // Swap Y and Z
        vox->chunks[i].size.xyz.z = size.xyz.y;
        int3 xyz = {size.xyz.x, size.xyz.z, size.xyz.y};
        int voxels_length = int3_array_size(xyz);
        if (voxels_length <= 0) {
            zox_log(" ! [vox] invalid voxel length for chunk %d", i);
            free(vox->chunks);
            free(file_buffer);
            return EXIT_FAILURE;
        }
        total_voxel_memory += voxels_length;
        memcpy(&vox->chunks[i].xyzi.name, ptr, 4); ptr += 4;
        memcpy(&vox->chunks[i].xyzi.chunk_content, ptr, 4); ptr += 4;
        memcpy(&vox->chunks[i].xyzi.chunk_nums, ptr, 4); ptr += 4;
        int num_voxels;
        memcpy(&num_voxels, ptr, 4); ptr += 4;
        if (num_voxels < 0 || ptr + num_voxels * 4 > file_buffer + file_size) {
            zox_log(" ! [vox] invalid num_voxels for chunk %d: %d", i, num_voxels);
            free(vox->chunks);
            free(file_buffer);
            return EXIT_FAILURE;
        }
        if (!voxel_ptr) {
            voxel_ptr = calloc(total_voxel_memory, 1);
            if (!voxel_ptr) {
                zox_log(" ! [vox] failed to allocate voxel buffer");
                free(vox->chunks);
                free(file_buffer);
                return EXIT_FAILURE;
            }
        }
        vox->chunks[i].xyzi.voxels = voxel_ptr;
        voxel_ptr += voxels_length;
        if (zox_time_load_vox) zox_log(" + [vox] chunk %d num_voxels: %d", i, num_voxels);
        for (int j = 0; j < num_voxels; j++) {
            byte x = *ptr++;
            byte y = *ptr++;
            byte z = *ptr++;
            byte color_index = *ptr++;
            byte adjusted_y = z; // Use Z as Y
            byte adjusted_z = vox->chunks[i].size.xyz.z - 1 - y; // Flip Y to Z
            int3 position = {x, adjusted_y, adjusted_z};
            int array_index = int3_array_index(position, vox->chunks[i].size.xyz);
            if (array_index < 0 || array_index >= voxels_length) {
                zox_log(" ! [vox] invalid array index for chunk %d voxel %d: %d", i, j, array_index);
                free(vox->chunks[0].xyzi.voxels);
                free(vox->chunks);
                free(file_buffer);
                return EXIT_FAILURE;
            }
            vox->chunks[i].xyzi.voxels[array_index] = color_index;
        }
    }
    double chunk_parse_time = get_time_ms() - start;
    section_sum += chunk_parse_time;
    if (zox_time_load_vox) zox_log(" + [vox] chunk parse time: %.2f ms", chunk_parse_time);

    // Parse palette
    start = get_time_ms();
    if (zox_time_load_vox) zox_log(" + [vox] palette ptr offset: %ld, file_size: %ld", ptr - file_buffer, file_size);
    if (ptr + 4 <= file_buffer + file_size && !strncmp((char*)ptr, "RGBA", 4)) {
        if (zox_time_load_vox) zox_log(" + [vox] found RGBA chunk");
        if (ptr + 12 > file_buffer + file_size) {
            zox_log(" ! [vox] file too small for palette header");
            free(vox->chunks[0].xyzi.voxels);
            free(vox->chunks);
            free(file_buffer);
            return EXIT_FAILURE;
        }
        memcpy(&vox->palette.name, ptr, 4); ptr += 4;
        memcpy(&vox->palette.chunk_content, ptr, 4); ptr += 4;
        memcpy(&vox->palette.chunk_nums, ptr, 4); ptr += 4;
        int colors_length = vox->palette.chunk_content / 4;
        if (zox_time_load_vox) zox_log(" + [vox] palette colors_length: %d", colors_length);
        if (colors_length <= 0 || ptr + sizeof(color) * colors_length > file_buffer + file_size) {
            zox_log(" ! [vox] invalid palette colors_length: %d", colors_length);
            free(vox->chunks[0].xyzi.voxels);
            free(vox->chunks);
            free(file_buffer);
            return EXIT_FAILURE;
        }
        vox->palette.values = malloc(sizeof(color) * colors_length);
        vox->palette.values_rgb = malloc(sizeof(color_rgb) * colors_length);
        if (!vox->palette.values || !vox->palette.values_rgb) {
            zox_log(" ! [vox] failed to allocate palette");
            free(vox->palette.values);
            free(vox->palette.values_rgb);
            free(vox->chunks[0].xyzi.voxels);
            free(vox->chunks);
            free(file_buffer);
            return EXIT_FAILURE;
        }
        memcpy(vox->palette.values, ptr, sizeof(color) * colors_length);
        ptr += sizeof(color) * colors_length;
        vox->palette.values_length = colors_length;
        for (int i = 0; i < colors_length; i++) {
            vox->palette.values_rgb[i].r = vox->palette.values[i].r;
            vox->palette.values_rgb[i].g = vox->palette.values[i].g;
            vox->palette.values_rgb[i].b = vox->palette.values[i].b;
        }
    } else {
        if (zox_time_load_vox) zox_log(" + [vox] using default palette");
        int colors_length = 256;
        vox->palette.values = malloc(sizeof(color) * colors_length);
        vox->palette.values_rgb = malloc(sizeof(color_rgb) * colors_length);
        if (!vox->palette.values || !vox->palette.values_rgb) {
            zox_log(" ! [vox] failed to allocate default palette");
            free(vox->palette.values);
            free(vox->palette.values_rgb);
            free(vox->chunks[0].xyzi.voxels);
            free(vox->chunks);
            free(file_buffer);
            return EXIT_FAILURE;
        }
        memcpy(vox->palette.values, default_palette, sizeof(color) * colors_length);
        vox->palette.values_length = colors_length;
        for (int i = 0; i < colors_length; i++) {
            vox->palette.values_rgb[i].r = vox->palette.values[i].r;
            vox->palette.values_rgb[i].g = vox->palette.values[i].g;
            vox->palette.values_rgb[i].b = vox->palette.values[i].b;
        }
    }
    double palette_parse_time = get_time_ms() - start;
    section_sum += palette_parse_time;
    if (zox_time_load_vox) zox_log(" + [vox] palette parse time: %.2f ms", palette_parse_time);

    free(file_buffer);
    double total_time = get_time_ms() - start_total;
    if (zox_time_load_vox) zox_log(" + [vox] total time: %.2f ms, unaccounted: %.2f ms", total_time, total_time - section_sum);
    return EXIT_SUCCESS;
}