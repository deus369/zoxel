#define VOX_MAGIC "VOX "
#define VOX_MAIN "MAIN"
#define VOX_FILE_PACK "PACK"
#define VOX_FILE_SIZE "SIZE"
#define VOX_FILE_XYZI "XYZI"
#define VOX_FILE_RGBA "RGBA"
// #define VOX_SIZE_INT 32
#define VOX_SUPPORTED_VERSION 150
#define zoxel_voxel_vox_flipz
// #define zoxel_debug_vox_read

int peek(FILE* file) {
    int c = fgetc(file);
    ungetc(c, file);
    return c;
}

#include "dispose.c"
#include "read.c"
// #include "read2.c"
#include "files.c"