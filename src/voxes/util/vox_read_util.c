#define VOX_MAGIC "VOX "
#define VOX_MAIN "MAIN"
#define VOX_FILE_PACK "PACK"
#define VOX_FILE_SIZE "SIZE"
#define VOX_FILE_XYZI "XYZI"
#define VOX_FILE_RGBA "RGBA"
#define VOX_SIZE_INT 32
#define VOX_SUPPORTED_VERSION 150
#define zoxel_voxel_vox_flipz
// #define zoxel_debug_vox_read

int peek(FILE* file) {
    int c = fgetc(file);
    ungetc(c, file);
    return c;
}

void dispose_vox_file(vox_file *vox) {
    if (vox->chunks) {
        // first free children voxels
        for (int i = 0; i < vox->pack.model_nums; i++) free(vox->chunks[i].xyzi.voxels);
        free(vox->chunks);    // children chunks
    }
    if (vox->palette.values) free(vox->palette.values);  // pallete colorRGBs
    if (vox->palette.values_rgb) free(vox->palette.values_rgb);  // pallete colorRGBs
}

/**
This code reads the VOX file header and then reads each chunk in the file one by one.
The chunk id and chunk size are read first, followed by the chunk data itself.
The chunk data is stored in a dynamically allocated buffer and is then processed as needed.
*/
int read_vox(const char* filename, vox_file *vox) {
    if (!filename) return EXIT_FAILURE;
#ifdef zoxel_log_files
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
        zoxel_log_error(stderr, "Failed to read header\n");
        return EXIT_FAILURE;
    }
    // compare header, make sure 'VOX ' label is inside it
    if (strncmp(vox->header.magic, VOX_MAGIC, sizeof(vox->header.magic)) != 0) {
        zoxel_log_error(stderr, "Invalid magic value\n");
        return EXIT_FAILURE;
    }
    if (vox->header.version != VOX_SUPPORTED_VERSION) {
        zoxel_log_error(stderr, "Unsupported version [%i]\n", vox->header.version);
        return EXIT_FAILURE;
    }
    if (fread(&vox->main.name, sizeof(vox->main.name), 1, file) != 1) {
        zoxel_log_error(stderr, "Failed to read vox->main.name\n");
        return EXIT_FAILURE;
    }
    if (strncmp(vox->main.name, VOX_MAIN, 4) != 0) {
        zoxel_log_error(stderr, "Invalid vox->main.name\n");
        return EXIT_FAILURE;
    }
    if (fread(&vox->main.chunk_content, sizeof(vox->main.chunk_content), 1, file) != 1) {
        zoxel_log_error(stderr, "Failed to read vox->main.chunk_content\n");
        return EXIT_FAILURE;
    }
    if (vox->main.chunk_content != 0) {
        zoxel_log("Bad chunk_content, should be 0.\n");
        return EXIT_FAILURE;
    }
    if (fread(&vox->main.chunk_nums, sizeof(vox->main.chunk_nums), 1, file) != 1) {
        zoxel_log_error(stderr, "Failed to read vox->main.chunk_nums\n");
        return EXIT_FAILURE;
    }
    // pack data
    if (peek(file) == 'P') {
        if (fread(&vox->pack.name, sizeof(vox->pack.name), 1, file) != 1) {
            zoxel_log_error(stderr, "Failed to read vox->pack.name\n");
            return EXIT_FAILURE;
        }
        if (strncmp(vox->pack.name, VOX_FILE_PACK, sizeof(vox->pack.name)) != 0) {
            zoxel_log_error(stderr, "Invalid vox->pack.name\n");
            return EXIT_FAILURE;
        }
        if (fread(&vox->pack.chunk_content, sizeof(vox->pack.chunk_content), 1, file) != 1) {
            zoxel_log_error(stderr, "Failed to read vox->pack.chunk_content\n");
            return EXIT_FAILURE;
        }
        if (fread(&vox->pack.chunk_nums, sizeof(vox->pack.chunk_nums), 1, file) != 1) {
            zoxel_log_error(stderr, "Failed to read vox->pack.chunk_nums\n");
            return EXIT_FAILURE;
        }
        if (fread(&vox->pack.model_nums, sizeof(vox->pack.model_nums), 1, file) != 1) {
            zoxel_log_error(stderr, "Failed to read vox->pack.model_nums\n");
            return EXIT_FAILURE;
        }
        if (vox->pack.model_nums == 0) {
            zoxel_log("Bad Token: model nums must be greater than zero.\n");
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
            zoxel_log_error(stderr, "Failed to read chunk.size.name\n");
            return EXIT_FAILURE;
        }
        if (strncmp(chunk.size.name, VOX_FILE_SIZE, sizeof(chunk.size.name)) != 0) {
            zoxel_log_error(stderr, "Invalid chunk.size.name\n");
            return EXIT_FAILURE;
        }
        if (fread(&chunk.size.chunk_content, sizeof(chunk.size.chunk_content), 1, file) != 1) {
            zoxel_log_error(stderr, "Failed to read chunk.size.chunk_content\n");
            return EXIT_FAILURE;
        }
        if (chunk.size.chunk_content != 12) {
            zoxel_log_error(stderr, "Invalid chunk.size.chunk_content, must be 12.\n");
            return EXIT_FAILURE;
        }
        if (fread(&chunk.size.chunk_nums, sizeof(chunk.size.chunk_nums), 1, file) != 1) {
            zoxel_log_error(stderr, "Failed to read chunk.size.chunk_nums\n");
            return EXIT_FAILURE;
        }
        if (fread(&chunk.size.xyz.x, sizeof(chunk.size.xyz.x), 1, file) != 1) {
            zoxel_log_error(stderr, "Failed to read chunk.size.x\n");
            return EXIT_FAILURE;
        }
        if (fread(&chunk.size.xyz.z, sizeof(chunk.size.xyz.z), 1, file) != 1) {
            zoxel_log_error(stderr, "Failed to read chunk.size.z\n");
            return EXIT_FAILURE;
        }
        if (fread(&chunk.size.xyz.y, sizeof(chunk.size.xyz.y), 1, file) != 1) {
            zoxel_log_error(stderr, "Failed to read chunk.size.y\n");
            return EXIT_FAILURE;
        }
        if (fread(&chunk.xyzi.name, sizeof(chunk.xyzi.name), 1, file) != 1) {
            zoxel_log_error(stderr, "Failed to read chunk.xyzi.name\n");
            return EXIT_FAILURE;
        }
        if (strncmp(chunk.xyzi.name, VOX_FILE_XYZI, sizeof(chunk.xyzi.name)) != 0) {
            zoxel_log_error(stderr, "Invalid chunk.xyzi.name\n");
            return EXIT_FAILURE;
        }
        if (fread(&chunk.xyzi.chunk_content, sizeof(chunk.xyzi.chunk_content), 1, file) != 1) {
            zoxel_log_error(stderr, "Failed to read chunk.xyzi.chunk_content\n");
            return EXIT_FAILURE;
        }
        if (fread(&chunk.xyzi.chunk_nums, sizeof(chunk.xyzi.chunk_nums), 1, file) != 1) {
            zoxel_log_error(stderr, "Failed to read chunk.xyzi.chunk_nums\n");
            return EXIT_FAILURE;
        }
        if (chunk.xyzi.chunk_nums != 0) {
            zoxel_log("Bad Token: chunk nums is %i,i t should be 0.\n", chunk.xyzi.chunk_nums);
            return EXIT_FAILURE;
        }
        int voxel_nums;
        if (fread(&voxel_nums, sizeof(voxel_nums), 1, file) != 1) {
            zoxel_log_error(stderr, "Failed to read voxel_nums\n");
            return EXIT_FAILURE;
        }
        int voxels_length = int3_array_size(chunk.size.xyz); // chunk.size.x * chunk.size.y * chunk.size.z;
        int bytes_length = voxel_nums * 4;
#ifdef zoxel_debug_vox_read
        zoxel_log("    - size.chunk_content [%i]\n", chunk.size.chunk_content);
        zoxel_log("    - size.chunk_nums [%i]\n", chunk.size.chunk_nums);
        zoxel_log("    - size.xyz [%ix%ix%i]\n", chunk.size.xyz.x, chunk.size.xyz.y, chunk.size.xyz.z);
        zoxel_log("    - xyzi.chunk_content [%i]\n", chunk.xyzi.chunk_content);
        zoxel_log("    - xyzi.chunk_nums [%i]\n", chunk.xyzi.chunk_nums);
        zoxel_log("    - voxel_nums [%i]\n", voxel_nums);
        zoxel_log("    - voxels_length [%i]\n", voxels_length);
        zoxel_log("    - bytes_length [%i]\n", bytes_length);
#endif
        // allocate voxels
        chunk.xyzi.voxels = malloc(voxels_length);
        for (int j = 0; j < voxels_length; j++) chunk.xyzi.voxels[j] = 0;
        // zoxel_log("-=== voxel_nums [%i] ===-\n", voxel_nums);
        unsigned char *voxel_bytes = (unsigned char*) malloc(bytes_length);
        if (voxel_bytes == NULL)
        {
            zoxel_log_error(stderr, "Failed to allocate memory for voxel_bytes!\n");
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
                zoxel_log("        - voxel [%i] [%ix%ix%i] [%i]\n", j, position.x, position.y, position.z, chunk.xyzi.voxels[array_index]);
            }
#endif
        }
        free(voxel_bytes);
        vox->chunks[i] = chunk;
    }
    // now read pallete
    if (!feof(file)) {
        if (fread(&vox->palette.name, sizeof(vox->palette.name), 1, file) != 1) {
            zoxel_log_error(stderr, "Failed to read vox->palette.name\n");
            return EXIT_FAILURE;
        }
        if (strncmp(vox->palette.name, VOX_FILE_RGBA, sizeof(vox->palette.name)) != 0) {
            zoxel_log_error(stderr, "Invalid vox->palette.name\n");
            return EXIT_FAILURE;
        }
        if (fread(&vox->palette.chunk_content, sizeof(vox->palette.chunk_content), 1, file) != 1) {
            zoxel_log_error(stderr, "Failed to read vox->palette.chunk_content\n");
            return EXIT_FAILURE;
        }
        if (fread(&vox->palette.chunk_nums, sizeof(vox->palette.chunk_nums), 1, file) != 1) {
            zoxel_log_error(stderr, "Failed to read vox->palette.chunk_nums\n");
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
                zoxel_log("End of file at [%i]\n", i);
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
                zoxel_log("    - color [%i] [%ix%ix%ix%i]\n", i,
                    vox->palette.values[i].r, vox->palette.values[i].g, vox->palette.values[i].b, vox->palette.values[i].a);
            #endif
        }
    } else {
#ifdef zoxel_debug_vox_read
        zox_log(" + using default palette\n")
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
