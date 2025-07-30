/**
 * This code reads the VOX file header and then reads each chunk in the file one by one.
 * The chunk id and chunk size are read first, followed by the chunk data itself.
 * The chunk data is stored in a dynamically allocated buffer and is then processed as needed.
 */
int read_vox(const char* filename, vox_file *vox) {
    if (!filename) {
        return EXIT_FAILURE;
    }
    #ifdef zox_log_files
    zox_log(" + loading file [%s]\n", filename)
    #endif
    // Open the vox file for reading
    FILE *file = fopen(filename, "rb"); // "r"
    // Check if the file was opened successfully
    if (!file) {
        // Print an error message and exit if the file could not be opened
        zox_log(" - error: Could not open vox file [%s]\n", filename)
        return EXIT_FAILURE;
    }
    #ifdef zoxel_debug_vox_read
    zox_log(" + success opening vox file [%s]\n", filename)
    #endif
    // vox_file vox;
    if (fread(&vox->header, sizeof(vox_file_header), 1, file) != 1) {
        zox_log_errno("Failed to read header");
        return EXIT_FAILURE;
    }
    // compare header, make sure 'VOX ' label is inside it
    if (strncmp(vox->header.magic, VOX_MAGIC, sizeof(vox->header.magic)) != 0) {
        zox_log_errno("Invalid magic value");
        return EXIT_FAILURE;
    }
    if (vox->header.version != VOX_SUPPORTED_VERSION) {
        zox_log_errno("Unsupported version [%i]", vox->header.version);
        return EXIT_FAILURE;
    }
    if (fread(&vox->main.name, sizeof(vox->main.name), 1, file) != 1) {
        zox_log_errno("Failed to read vox->main.name");
        return EXIT_FAILURE;
    }
    if (strncmp(vox->main.name, VOX_MAIN, 4) != 0) {
        zox_log_errno("Invalid vox->main.name");
        return EXIT_FAILURE;
    }
    if (fread(&vox->main.chunk_content, sizeof(vox->main.chunk_content), 1, file) != 1) {
        zox_log_errno("Failed to read vox->main.chunk_content");
        return EXIT_FAILURE;
    }
    if (vox->main.chunk_content != 0) {
        zox_log_errno("Bad chunk_content, should be 0.");
        return EXIT_FAILURE;
    }
    if (fread(&vox->main.chunk_nums, sizeof(vox->main.chunk_nums), 1, file) != 1) {
        zox_log_errno("Failed to read vox->main.chunk_nums");
        return EXIT_FAILURE;
    }
    // pack data
    if (peek(file) == 'P') {
        if (fread(&vox->pack.name, sizeof(vox->pack.name), 1, file) != 1) {
            zox_log_errno("Failed to read vox->pack.name");
            return EXIT_FAILURE;
        }
        if (strncmp(vox->pack.name, VOX_FILE_PACK, sizeof(vox->pack.name)) != 0) {
            zox_log_errno("Invalid vox->pack.name");
            return EXIT_FAILURE;
        }
        if (fread(&vox->pack.chunk_content, sizeof(vox->pack.chunk_content), 1, file) != 1) {
            zox_log_errno("Failed to read vox->pack.chunk_content");
            return EXIT_FAILURE;
        }
        if (fread(&vox->pack.chunk_nums, sizeof(vox->pack.chunk_nums), 1, file) != 1) {
            zox_log_errno("Failed to read vox->pack.chunk_nums");
            return EXIT_FAILURE;
        }
        if (fread(&vox->pack.model_nums, sizeof(vox->pack.model_nums), 1, file) != 1) {
            zox_log_errno("Failed to read vox->pack.model_nums");
            return EXIT_FAILURE;
        }
        if (vox->pack.model_nums == 0) {
            zox_log("Bad Token: model nums must be greater than zero.");
            return EXIT_FAILURE;
        }
    } else {
        vox->pack.chunk_content = 0;
        vox->pack.chunk_nums = 0;
        vox->pack.model_nums = 1;
    }
    // chunk childs
    vox->chunks = malloc(vox->pack.model_nums * sizeof(vox_file_chunk_child));
    for (int i = 0; i < vox->pack.model_nums; i++) {
        #ifdef zoxel_debug_vox_read
        zox_log("  - Reading Chunk [%i]\n", i)
        #endif
        vox_file_chunk_child chunk;
        if (fread(&chunk.size.name, sizeof(chunk.size.name), 1, file) != 1) {
            zox_log_errno("Failed to read chunk.size.name");
            return EXIT_FAILURE;
        }
        if (strncmp(chunk.size.name, VOX_FILE_SIZE, sizeof(chunk.size.name)) != 0) {
            zox_log_errno("Invalid chunk.size.name");
            return EXIT_FAILURE;
        }
        if (fread(&chunk.size.chunk_content, sizeof(chunk.size.chunk_content), 1, file) != 1) {
            zox_log_errno("Failed to read chunk.size.chunk_content");
            return EXIT_FAILURE;
        }
        if (chunk.size.chunk_content != 12) {
            zox_log_errno("Invalid chunk.size.chunk_content, must be 12.");
            return EXIT_FAILURE;
        }
        if (fread(&chunk.size.chunk_nums, sizeof(chunk.size.chunk_nums), 1, file) != 1) {
            zox_log_errno("Failed to read chunk.size.chunk_nums");
            return EXIT_FAILURE;
        }
        if (fread(&chunk.size.xyz.x, sizeof(chunk.size.xyz.x), 1, file) != 1) {
            zox_log_errno("Failed to read chunk.size.x");
            return EXIT_FAILURE;
        }
        if (fread(&chunk.size.xyz.z, sizeof(chunk.size.xyz.z), 1, file) != 1) {
            zox_log_errno("Failed to read chunk.size.z");
            return EXIT_FAILURE;
        }
        if (fread(&chunk.size.xyz.y, sizeof(chunk.size.xyz.y), 1, file) != 1) {
            zox_log_errno("Failed to read chunk.size.y");
            return EXIT_FAILURE;
        }
        if (fread(&chunk.xyzi.name, sizeof(chunk.xyzi.name), 1, file) != 1) {
            zox_log_errno("Failed to read chunk.xyzi.name");
            return EXIT_FAILURE;
        }
        if (strncmp(chunk.xyzi.name, VOX_FILE_XYZI, sizeof(chunk.xyzi.name)) != 0) {
            zox_log_errno("Invalid chunk.xyzi.name");
            return EXIT_FAILURE;
        }
        if (fread(&chunk.xyzi.chunk_content, sizeof(chunk.xyzi.chunk_content), 1, file) != 1) {
            zox_log_errno("Failed to read chunk.xyzi.chunk_content");
            return EXIT_FAILURE;
        }
        if (fread(&chunk.xyzi.chunk_nums, sizeof(chunk.xyzi.chunk_nums), 1, file) != 1) {
            zox_log_errno("Failed to read chunk.xyzi.chunk_nums");
            return EXIT_FAILURE;
        }
        if (chunk.xyzi.chunk_nums != 0) {
            zox_log_error("Bad Token: chunk nums is %i,i t should be 0.", chunk.xyzi.chunk_nums);
            return EXIT_FAILURE;
        }
        int voxel_nums;
        if (fread(&voxel_nums, sizeof(voxel_nums), 1, file) != 1) {
            zox_log_errno("Failed to read voxel_nums");
            return EXIT_FAILURE;
        }
        int voxels_length = int3_array_size(chunk.size.xyz); // chunk.size.x * chunk.size.y * chunk.size.z;
        int bytes_length = voxel_nums * 4;
        #ifdef zoxel_debug_vox_read
        zox_log("    - size.chunk_content [%i]\n", chunk.size.chunk_content);
        zox_log("    - size.chunk_nums [%i]\n", chunk.size.chunk_nums);
        zox_log("    - size.xyz [%ix%ix%i]\n", chunk.size.xyz.x, chunk.size.xyz.y, chunk.size.xyz.z);
        zox_log("    - xyzi.chunk_content [%i]\n", chunk.xyzi.chunk_content);
        zox_log("    - xyzi.chunk_nums [%i]\n", chunk.xyzi.chunk_nums);
        zox_log("    - voxel_nums [%i]\n", voxel_nums);
        zox_log("    - voxels_length [%i]\n", voxels_length);
        zox_log("    - bytes_length [%i]\n", bytes_length);
        #endif
        // allocate voxels
        chunk.xyzi.voxels = malloc(voxels_length);
        for (int j = 0; j < voxels_length; j++) chunk.xyzi.voxels[j] = 0;
        // zox_log("-=== voxel_nums [%i] ===-\n", voxel_nums);
        byte *voxel_bytes = (byte*) malloc(bytes_length);
        if (voxel_bytes == NULL)
        {
            zox_log_errno("Failed to allocate memory for voxel_bytes!");
            return EXIT_FAILURE;
        }
        for (int j = 0; j < bytes_length; j++) {
            if (feof(file)) {
                zox_log("End of file at [%i]\n", j)
                break;
            }
            voxel_bytes[j] = fgetc(file);
        }
        for (int j = 0; j < bytes_length; j += 4) {
            // int3 position = (int3) { voxel_bytes[j + 0], voxel_bytes[j + 1], voxel_bytes[j + 2] };
            int3 position = (int3) { voxel_bytes[j + 0], voxel_bytes[j + 2], voxel_bytes[j + 1] };
            // flip z, on vox file import it flips z voxels
            #ifdef zoxel_voxel_vox_flipz
            position.z = chunk.size.xyz.z - 1 - position.z;
            #endif
            // int array_index = int3_array_index2(position, chunk.size.xyz);
            int array_index = int3_array_index(position, chunk.size.xyz);
            if (array_index < 0 || array_index >= voxels_length) {
                zox_log(" -     array_index out of bounds  [%i] at [%ix%ix%i]\n", array_index, position.x, position.y, position.z)
                return EXIT_FAILURE;
            }
            chunk.xyzi.voxels[array_index] = voxel_bytes[j + 3];
            #ifdef zoxel_debug_vox_read
            if (j < 4 * 32) {
                zox_log("        - voxel [%i] [%ix%ix%i] [%i]\n", j, position.x, position.y, position.z, chunk.xyzi.voxels[array_index]);
            }
            #endif
        }
        free(voxel_bytes);
        vox->chunks[i] = chunk;
    }
    // now read pallete
    if (!feof(file)) {
        if (fread(&vox->palette.name, sizeof(vox->palette.name), 1, file) != 1) {
            zox_log_errno("Failed to read vox->palette.name");
            return EXIT_FAILURE;
        }
        if (strncmp(vox->palette.name, VOX_FILE_RGBA, sizeof(vox->palette.name)) != 0) {
            zox_log_errno("Invalid vox->palette.name");
            return EXIT_FAILURE;
        }
        if (fread(&vox->palette.chunk_content, sizeof(vox->palette.chunk_content), 1, file) != 1) {
            zox_log_errno("Failed to read vox->palette.chunk_content");
            return EXIT_FAILURE;
        }
        if (fread(&vox->palette.chunk_nums, sizeof(vox->palette.chunk_nums), 1, file) != 1) {
            zox_log_errno("Failed to read vox->palette.chunk_nums");
            return EXIT_FAILURE;
        }
        int colors_length = vox->palette.chunk_content / 4;
        #ifdef zoxel_debug_vox_read
        zox_log("vox->palette.chunk_content: %i\n", colors_length);
        #endif
        vox->palette.values = malloc(sizeof(color) * colors_length);
        vox->palette.values_length = colors_length;
        vox->palette.values_rgb = malloc(sizeof(color_rgb) * colors_length);
        for (int i = 0; i < colors_length; i++) {
            if (feof(file)) {
                zox_log("End of file at [%i]\n", i);
                break;
            }
            vox->palette.values[i].r = fgetc(file);
            vox->palette.values[i].g = fgetc(file);
            vox->palette.values[i].b = fgetc(file);
            vox->palette.values[i].a = fgetc(file);
            vox->palette.values_rgb[i].r = vox->palette.values[i].r;
            vox->palette.values_rgb[i].g = vox->palette.values[i].g;
            vox->palette.values_rgb[i].b = vox->palette.values[i].b;
            #ifdef zoxel_debug_vox_read
            zox_log("    - color [%i] [%ix%ix%ix%i]\n", i,
                    vox->palette.values[i].r, vox->palette.values[i].g, vox->palette.values[i].b, vox->palette.values[i].a);
            #endif
        }
    } else {
        #ifdef zoxel_debug_vox_read
        zox_log(" + using default palette")
        #endif
        vox->palette.values = malloc(sizeof(unsigned int) * 256);
        memcpy(vox->palette.values, default_palette, sizeof(unsigned int) * 256);
        int colors_length = 256;
        vox->palette.values_length = colors_length;
        vox->palette.values_rgb = malloc(sizeof(color_rgb) * colors_length);
        for (int i = 0; i < colors_length; i++) {
            vox->palette.values_rgb[i].r = vox->palette.values[i].r;
            vox->palette.values_rgb[i].g = vox->palette.values[i].g;
            vox->palette.values_rgb[i].b = vox->palette.values[i].b;
        }

    }
    #ifdef zoxel_debug_vox_read
    zox_log(" + success reading vox [%s]\n", filename)
    #endif
    // Close the vox file when we're done
    fclose(file);
    return EXIT_SUCCESS;
}
