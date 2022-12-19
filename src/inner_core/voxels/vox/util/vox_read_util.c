#include <stdio.h>
#include <stdlib.h>

#define VOX_MAGIC "VOX "
#define VOX_MAIN "MAIN"
#define VOX_FILE_PACK "PACK"
#define VOX_FILE_SIZE "SIZE"
#define VOX_FILE_XYZI "XYZI"
#define VOX_FILE_RGBA "RGBA"
#define VOX_SIZE_INT 32
#define VOX_SUPPORTED_VERSION 150

typedef struct
{
  char name[4];
  int chunk_content;
  int chunk_nums;
  int3 xyz;
} vox_file_size;

typedef struct
{
  char name[4];
  int chunk_content;
  int chunk_nums;
  unsigned char *voxels;
} vox_file_xyzi;

typedef struct
{
  char magic[4];
  int version;
} vox_file_header;

typedef struct
{
  char name[4];
  int chunk_content;
  int chunk_nums;
} vox_file_chunk;

typedef struct
{
  char name[4];
  int chunk_content;
  int chunk_nums;
  int model_nums;
} vox_file_pack;

typedef struct
{
  vox_file_size size;
  vox_file_xyzi xyzi;
} vox_file_chunk_child;

typedef struct
{
    char name[4];
    int chunk_content;
    int chunk_nums;
    color *values;
} vox_file_palette;

typedef struct
{
    vox_file_header header;
    vox_file_chunk main;
    vox_file_pack pack;
    vox_file_chunk_child *chunk_childs;  // allocate dynamically
    vox_file_palette palette;
} vox_file;

int peek(FILE* file)
{
    int c = fgetc(file);
    ungetc(c, file);
    return c;
}

unsigned int default_palette[] =
{
    0x00000000, 0xffffffff, 0xffccffff, 0xff99ffff, 0xff66ffff, 0xff33ffff, 0xff00ffff, 0xffffccff, 0xffccccff, 0xff99ccff, 0xff66ccff, 0xff33ccff, 0xff00ccff, 0xffff99ff, 0xffcc99ff, 0xff9999ff,
    0xff6699ff, 0xff3399ff, 0xff0099ff, 0xffff66ff, 0xffcc66ff, 0xff9966ff, 0xff6666ff, 0xff3366ff, 0xff0066ff, 0xffff33ff, 0xffcc33ff, 0xff9933ff, 0xff6633ff, 0xff3333ff, 0xff0033ff, 0xffff00ff,
    0xffcc00ff, 0xff9900ff, 0xff6600ff, 0xff3300ff, 0xff0000ff, 0xffffffcc, 0xffccffcc, 0xff99ffcc, 0xff66ffcc, 0xff33ffcc, 0xff00ffcc, 0xffffcccc, 0xffcccccc, 0xff99cccc, 0xff66cccc, 0xff33cccc,
    0xff00cccc, 0xffff99cc, 0xffcc99cc, 0xff9999cc, 0xff6699cc, 0xff3399cc, 0xff0099cc, 0xffff66cc, 0xffcc66cc, 0xff9966cc, 0xff6666cc, 0xff3366cc, 0xff0066cc, 0xffff33cc, 0xffcc33cc, 0xff9933cc,
    0xff6633cc, 0xff3333cc, 0xff0033cc, 0xffff00cc, 0xffcc00cc, 0xff9900cc, 0xff6600cc, 0xff3300cc, 0xff0000cc, 0xffffff99, 0xffccff99, 0xff99ff99, 0xff66ff99, 0xff33ff99, 0xff00ff99, 0xffffcc99,
    0xffcccc99, 0xff99cc99, 0xff66cc99, 0xff33cc99, 0xff00cc99, 0xffff9999, 0xffcc9999, 0xff999999, 0xff669999, 0xff339999, 0xff009999, 0xffff6699, 0xffcc6699, 0xff996699, 0xff666699, 0xff336699,
    0xff006699, 0xffff3399, 0xffcc3399, 0xff993399, 0xff663399, 0xff333399, 0xff003399, 0xffff0099, 0xffcc0099, 0xff990099, 0xff660099, 0xff330099, 0xff000099, 0xffffff66, 0xffccff66, 0xff99ff66,
    0xff66ff66, 0xff33ff66, 0xff00ff66, 0xffffcc66, 0xffcccc66, 0xff99cc66, 0xff66cc66, 0xff33cc66, 0xff00cc66, 0xffff9966, 0xffcc9966, 0xff999966, 0xff669966, 0xff339966, 0xff009966, 0xffff6666,
    0xffcc6666, 0xff996666, 0xff666666, 0xff336666, 0xff006666, 0xffff3366, 0xffcc3366, 0xff993366, 0xff663366, 0xff333366, 0xff003366, 0xffff0066, 0xffcc0066, 0xff990066, 0xff660066, 0xff330066,
    0xff000066, 0xffffff33, 0xffccff33, 0xff99ff33, 0xff66ff33, 0xff33ff33, 0xff00ff33, 0xffffcc33, 0xffcccc33, 0xff99cc33, 0xff66cc33, 0xff33cc33, 0xff00cc33, 0xffff9933, 0xffcc9933, 0xff999933,
    0xff669933, 0xff339933, 0xff009933, 0xffff6633, 0xffcc6633, 0xff996633, 0xff666633, 0xff336633, 0xff006633, 0xffff3333, 0xffcc3333, 0xff993333, 0xff663333, 0xff333333, 0xff003333, 0xffff0033,
    0xffcc0033, 0xff990033, 0xff660033, 0xff330033, 0xff000033, 0xffffff00, 0xffccff00, 0xff99ff00, 0xff66ff00, 0xff33ff00, 0xff00ff00, 0xffffcc00, 0xffcccc00, 0xff99cc00, 0xff66cc00, 0xff33cc00,
    0xff00cc00, 0xffff9900, 0xffcc9900, 0xff999900, 0xff669900, 0xff339900, 0xff009900, 0xffff6600, 0xffcc6600, 0xff996600, 0xff666600, 0xff336600, 0xff006600, 0xffff3300, 0xffcc3300, 0xff993300,
    0xff663300, 0xff333300, 0xff003300, 0xffff0000, 0xffcc0000, 0xff990000, 0xff660000, 0xff330000, 0xff0000ee, 0xff0000dd, 0xff0000bb, 0xff0000aa, 0xff000088, 0xff000077, 0xff000055, 0xff000044,
    0xff000022, 0xff000011, 0xff00ee00, 0xff00dd00, 0xff00bb00, 0xff00aa00, 0xff008800, 0xff007700, 0xff005500, 0xff004400, 0xff002200, 0xff001100, 0xffee0000, 0xffdd0000, 0xffbb0000, 0xffaa0000,
    0xff880000, 0xff770000, 0xff550000, 0xff440000, 0xff220000, 0xff110000, 0xffeeeeee, 0xffdddddd, 0xffbbbbbb, 0xffaaaaaa, 0xff888888, 0xff777777, 0xff555555, 0xff444444, 0xff222222, 0xff111111
};

void dispose_vox_file(vox_file *vox)
{
    // first free children voxels
    for (int i = 0; i < vox->pack.model_nums; i++)
    {
        free(vox->chunk_childs[i].xyzi.voxels);
    }
    free(vox->chunk_childs);    // children chunks
    free(vox->palette.values);  // pallete colors
}

/**
This code reads the VOX file header and then reads each chunk in the file one by one.
The chunk id and chunk size are read first, followed by the chunk data itself.
The chunk data is stored in a dynamically allocated buffer and is then processed as needed.
*/
int read_vox(const char* filename, vox_file *vox)
{
    // Open the vox file for reading
    FILE *file = fopen(filename, "r");  // rb
    // Check if the file was opened successfully
    if (file == NULL)
    {
        // Print an error message and exit if the file could not be opened
        printf("Error: Could not open vox file [%s]\n", filename);
        return -1;
    }
    #ifdef zoxel_debug_vox_read
    printf("Success Opening vox file [%s]\n", filename);
    #endif
    // vox_file vox;
    if (fread(&vox->header, sizeof(vox_file_header), 1, file) != 1)
    {
        fprintf(stderr, "Failed to read header\n");
        return -1;
    }
    // compare header, make sure 'VOX ' label is inside it
    if (strncmp(vox->header.magic, VOX_MAGIC, sizeof(vox->header.magic)) != 0)
    {
        fprintf(stderr, "Invalid magic value\n");
        return -1;
    }
    if (vox->header.version != VOX_SUPPORTED_VERSION)
    {
        fprintf(stderr, "Unsupported version [%i]\n", vox->header.version);
        return -1;
    }
    if (fread(&vox->main.name, sizeof(vox->main.name), 1, file) != 1)
    {
        fprintf(stderr, "Failed to read vox->main.name\n");
        return -1;
    }
    if (strncmp(vox->main.name, VOX_MAIN, 4) != 0)
    {
        fprintf(stderr, "Invalid vox->main.name\n");
        return -1;
    }
    if (fread(&vox->main.chunk_content, sizeof(vox->main.chunk_content), 1, file) != 1)
    {
        fprintf(stderr, "Failed to read vox->main.chunk_content\n");
        return -1;
    }
    if (vox->main.chunk_content != 0)
    {
        printf("Bad chunk_content, should be 0.\n");
        return -1;
    }
    if (fread(&vox->main.chunk_nums, sizeof(vox->main.chunk_nums), 1, file) != 1)
    {
        fprintf(stderr, "Failed to read vox->main.chunk_nums\n");
        return -1;
    }
    // pack data
    if (peek(file) == 'P')
    {
        if (fread(&vox->pack.name, sizeof(vox->pack.name), 1, file) != 1)
        {
            fprintf(stderr, "Failed to read vox->pack.name\n");
            return -1;
        }
        if (strncmp(vox->pack.name, VOX_FILE_PACK, sizeof(vox->pack.name)) != 0)
        {
            fprintf(stderr, "Invalid vox->pack.name\n");
            return -1;
        }
        if (fread(&vox->pack.chunk_content, sizeof(vox->pack.chunk_content), 1, file) != 1)
        {
            fprintf(stderr, "Failed to read vox->pack.chunk_content\n");
            return -1;
        }
        if (fread(&vox->pack.chunk_nums, sizeof(vox->pack.chunk_nums), 1, file) != 1)
        {
            fprintf(stderr, "Failed to read vox->pack.chunk_nums\n");
            return -1;
        }
        if (fread(&vox->pack.model_nums, sizeof(vox->pack.model_nums), 1, file) != 1)
        {
            fprintf(stderr, "Failed to read vox->pack.model_nums\n");
            return -1;
        }
        if (vox->pack.model_nums == 0)
        {
            printf("Bad Token: model nums must be greater than zero.\n");
            return -1;
        }
    }
    else
    {
        vox->pack.chunk_content = 0;
        vox->pack.chunk_nums = 0;
        vox->pack.model_nums = 1;
    }
    // chunk childs
    vox->chunk_childs = malloc(vox->pack.model_nums * sizeof(vox_file_chunk_child));
    for (int i = 0; i < vox->pack.model_nums; i++)
    {
        #ifdef zoxel_debug_vox_read
        printf("  - Reading Chunk [%i]\n", i);
        #endif
        vox_file_chunk_child chunk;
        if (fread(&chunk.size.name, sizeof(chunk.size.name), 1, file) != 1)
        {
            fprintf(stderr, "Failed to read chunk.size.name\n");
            return -1;
        }
        if (strncmp(chunk.size.name, VOX_FILE_SIZE, sizeof(chunk.size.name)) != 0)
        {
            fprintf(stderr, "Invalid chunk.size.name\n");
            return -1;
        }

        if (fread(&chunk.size.chunk_content, sizeof(chunk.size.chunk_content), 1, file) != 1)
        {
            fprintf(stderr, "Failed to read chunk.size.chunk_content\n");
            return -1;
        }
        if (chunk.size.chunk_content != 12)
        {
            fprintf(stderr, "Invalid chunk.size.chunk_content, must be 12.\n");
            return -1;
        }

        if (fread(&chunk.size.chunk_nums, sizeof(chunk.size.chunk_nums), 1, file) != 1)
        {
            fprintf(stderr, "Failed to read chunk.size.chunk_nums\n");
            return -1;
        }
        if (fread(&chunk.size.xyz.x, sizeof(chunk.size.xyz.x), 1, file) != 1)
        {
            fprintf(stderr, "Failed to read chunk.size.x\n");
            return -1;
        }
        if (fread(&chunk.size.xyz.y, sizeof(chunk.size.xyz.y), 1, file) != 1)
        {
            fprintf(stderr, "Failed to read chunk.size.y\n");
            return -1;
        }
        if (fread(&chunk.size.xyz.z, sizeof(chunk.size.xyz.z), 1, file) != 1)
        {
            fprintf(stderr, "Failed to read chunk.size.z\n");
            return -1;
        }
        if (fread(&chunk.xyzi.name, sizeof(chunk.xyzi.name), 1, file) != 1)
        {
            fprintf(stderr, "Failed to read chunk.xyzi.name\n");
            return -1;
        }
        if (strncmp(chunk.xyzi.name, VOX_FILE_XYZI, sizeof(chunk.xyzi.name)) != 0)
        {
            fprintf(stderr, "Invalid chunk.xyzi.name\n");
            return -1;
        }
        if (fread(&chunk.xyzi.chunk_content, sizeof(chunk.xyzi.chunk_content), 1, file) != 1)
        {
            fprintf(stderr, "Failed to read chunk.xyzi.chunk_content\n");
            return -1;
        }
        if (fread(&chunk.xyzi.chunk_nums, sizeof(chunk.xyzi.chunk_nums), 1, file) != 1)
        {
            fprintf(stderr, "Failed to read chunk.xyzi.chunk_nums\n");
            return -1;
        }
        if (chunk.xyzi.chunk_nums != 0)
        {
            printf("Bad Token: chunk nums is %i,i t should be 0.\n", chunk.xyzi.chunk_nums);
            return -1;
        }
        int voxel_nums;
        if (fread(&voxel_nums, sizeof(voxel_nums), 1, file) != 1)
        {
            fprintf(stderr, "Failed to read voxel_nums\n");
            return -1;
        }
        int voxels_length = int3_array_size(chunk.size.xyz); // chunk.size.x * chunk.size.y * chunk.size.z;
        int bytes_length = voxel_nums * 4;
        #ifdef zoxel_debug_vox_read
        printf("    - size.chunk_content [%i]\n", chunk.size.chunk_content);
        printf("    - size.chunk_nums [%i]\n", chunk.size.chunk_nums);
        printf("    - size.xyz [%ix%ix%i]\n", chunk.size.xyz.x, chunk.size.xyz.y, chunk.size.xyz.z);
        printf("    - xyzi.chunk_content [%i]\n", chunk.xyzi.chunk_content);
        printf("    - xyzi.chunk_nums [%i]\n", chunk.xyzi.chunk_nums);
        printf("    - voxel_nums [%i]\n", voxel_nums);
        printf("    - voxels_length [%i]\n", voxels_length);
        printf("    - bytes_length [%i]\n", bytes_length);
        #endif
        // allocate voxels
        chunk.xyzi.voxels = malloc(voxels_length);
        for (int j = 0; j < voxels_length; j++)
        {
            chunk.xyzi.voxels[j] = 0;
        }
        // printf("-=== voxel_nums [%i] ===-\n", voxel_nums);
        unsigned char *voxel_bytes = (unsigned char*) malloc(bytes_length);
        if (voxel_bytes == NULL)
        {
            fprintf(stderr, "Failed to allocate memory for voxel_bytes!\n");
            return -1;
        }
        for (int j = 0; j < bytes_length; j++)
        {
            if (feof(file))
            {
                printf("End of file at [%i]\n", j);
                break;
            }
            voxel_bytes[j] = fgetc(file);
        }
        /*if (fread(&voxel_bytes, sizeof(unsigned char), bytes_length, file) != bytes_length)
        {
            fprintf(stderr, "Failed to read voxels!\n");
            free(voxel_bytes);
            return -1;
        }*/
        for (int j = 0; j < bytes_length; j += 4)
        {
            int3 position = (int3) { voxel_bytes[j + 0], voxel_bytes[j + 1], voxel_bytes[j + 2] };
            int array_index = int3_array_index(position, chunk.size.xyz);
            chunk.xyzi.voxels[array_index] = voxel_bytes[j + 3];
            #ifdef zoxel_debug_vox_read
            if (j < 4 * 32)
            {
                printf("        - voxel [%i] [%ix%ix%i] [%i]\n", j, position.x, position.y, position.z, chunk.xyzi.voxels[array_index]);
            }
            #endif
        }
        free(voxel_bytes);
        vox->chunk_childs[i] = chunk;
    }
    // now read pallete
    if (!feof(file))
    {
        if (fread(&vox->palette.name, sizeof(vox->palette.name), 1, file) != 1)
        {
            fprintf(stderr, "Failed to read vox->palette.name\n");
            return -1;
        }
        if (strncmp(vox->palette.name, VOX_FILE_RGBA, sizeof(vox->palette.name)) != 0)
        {
            fprintf(stderr, "Invalid vox->palette.name\n");
            return -1;
        }
        if (fread(&vox->palette.chunk_content, sizeof(vox->palette.chunk_content), 1, file) != 1)
        {
            fprintf(stderr, "Failed to read vox->palette.chunk_content\n");
            return -1;
        }
        if (fread(&vox->palette.chunk_nums, sizeof(vox->palette.chunk_nums), 1, file) != 1)
        {
            fprintf(stderr, "Failed to read vox->palette.chunk_nums\n");
            return -1;
        }
        int colors_length = vox->palette.chunk_content / 4;
        #ifdef zoxel_debug_vox_read
            printf("vox->palette.chunk_content: %i\n", colors_length);
        #endif
        vox->palette.values = malloc(sizeof(color) * colors_length);
        for (int i = 0; i < colors_length; i++)
        {
            if (feof(file))
            {
                printf("End of file at [%i]\n", i);
                break;
            }
            vox->palette.values[i].r = fgetc(file);
            vox->palette.values[i].g = fgetc(file);
            vox->palette.values[i].b = fgetc(file);
            vox->palette.values[i].a = fgetc(file);
            #ifdef zoxel_debug_vox_read
                printf("    - color [%i] [%ix%ix%ix%i]\n", i,
                    vox->palette.values[i].r, vox->palette.values[i].g, vox->palette.values[i].b, vox->palette.values[i].a);
            #endif
        }
    }
    else
    {
        #ifdef zoxel_debug_vox_read
            printf("Using default palette!\n");
        #endif
        vox->palette.values = malloc(sizeof(unsigned int) * 256);
        memcpy(vox->palette.values, default_palette, sizeof(unsigned int) * 256);
    }
    #ifdef zoxel_debug_vox_read
    printf("Success reading vox [%s]\n", filename);
    #endif
    // Close the vox file when we're done
    fclose(file);
    return 0;
}

        /*if (vox->pack.name[0] != 'P' || vox->pack.name[1] != 'A' || vox->pack.name[2] != 'C' || vox->pack.name[3] != 'K')
        {
            printf("Bad Token: token is not PACK\n");
            return -1;
        }*/
/*union
{
    unsigned char c[4];
    color i;
} converter_bytes_to_color;*/

    /*printf("  - pack chunk_content [%i]\n", vox->pack.chunk_content);
    printf("  - pack chunk_nums [%i]\n", vox->pack.chunk_nums);
    printf("  - pack model_nums [%i]\n", vox->pack.model_nums);
    for (int i = 0; i < vox->pack.model_nums; i++)
    {
        vox_file_chunk_child chunk = vox->chunk_childs[i];
        printf("  - chunk [%i]\n", i);
        printf("    - size.chunk_content [%i]\n", chunk.size.chunk_content);
        printf("    - size.chunk_nums [%i]\n", chunk.size.chunk_nums);
        printf("    - size.xyz [%ix%ix%i]\n", chunk.size.x, chunk.size.y, chunk.size.z);

        printf("    - xyzi.chunk_content [%i]\n", chunk.xyzi.chunk_content);
        printf("    - xyzi.chunk_nums [%i]\n", chunk.xyzi.chunk_nums);
        // printf("    - xyzi.xyz [%ix%ix%i]\n", chunk.xyzi.x, chunk.xyzi.y, chunk.xyzi.z);
        
        for (int j = 0; j < chunk.size.x * chunk.size.y * chunk.size.z; j++)
        {
            if (j < 16)
            {
            // printf("      - size.xyz [%i]\n", chunk.xyzi.voxels[j]);
            }
        }
    }*/
        // unsigned char *palette_bytes = malloc(vox->palette.chunk_content);
        // palette_bytes[j] = fgetc(file);
        /*for (int j = 0, i = 0; j < vox->palette.chunk_content; j += 4, i++)
        {
            converter_bytes_to_color.c[0] = palette_bytes[j];
            converter_bytes_to_color.c[1] = palette_bytes[j + 1];
            converter_bytes_to_color.c[2] = palette_bytes[j + 2];
            converter_bytes_to_color.c[3] = palette_bytes[j + 3];
            memcpy(&vox->palette.values[i], converter_bytes_to_color.c, 4);
            // voxel.palette.values[i / 4] = BitConverter.ToUInt32(bytePalette, i - 4);
            #ifdef zoxel_debug_vox_read
                printf("Pallete [%i] is [%ix%ix%ix%i]\n", i,
                    vox->palette.values[i].r, vox->palette.values[i].b, vox->palette.values[i].g, vox->palette.values[i].a);
            #endif
        }
        free(palette_bytes);*/
/*typedef struct {
  unsigned char x;
  unsigned char y;
  unsigned char z;
  unsigned char color;
} vox_voxel;*/

/*typedef struct Voxel {
  unsigned char x;
  unsigned char y;
  unsigned char z;
  unsigned char color;
} Voxel;*/

/* Define a struct to store the vox file data. */
/*typedef struct VoxFile {
  int numVoxels;
  Voxel* voxels;
} VoxFile;*/

// dynamically set voxels array
/*typedef struct
{
  unsigned char x;
  unsigned char y;
  unsigned char z;
  unsigned char *voxels;
} vox_file_voxels;*/
  // vox_file_voxels voxels;
      /*for (int j = 0; j < chunk.xyzi.voxels.x * chunk.xyzi.voxels.y * chunk.xyzi.voxels.z; j++)
      {
        if (j < 16)
        {
          printf("      - size.xyz [%i]\n", chunk.xyzi.voxels.voxels[j]);
        }
      }*/

      /*for (int j = 0; j < _voxels.Length; j += 4)
      {
          var x = _voxels[j];
          var y = _voxels[j + 1];
          var z = _voxels[j + 2];
          var c = _voxels[j + 3];

          voxels[x, z, y] = c;
      }*/


    /*
    // The rest of the file consists of a series of chunks. Each chunk has a
    // chunk id and chunk size, followed by the chunk data. You can read the
    // chunk data using the following code:
    char chunk_id[4];
    int chunk_size;
    // for each chunk
    while (fread(chunk_id, sizeof(chunk_id), 1, file) == 1)
    {
      if (fread(&chunk_size, sizeof(chunk_size), 1, file) != 1)
      {
        fprintf(stderr, "Failed to read chunk size\n");
        return -1;
      }
      printf("Read chunk size [%i]\n", chunk_size);

      // Allocate memory for the chunk data
      char* chunk_data = malloc(chunk_size);
      if (chunk_data == NULL)
      {
        perror("Failed to allocate memory for chunk data");
        return -1;
      }
      // Read the chunk data
      if (fread(chunk_data, chunk_size, 1, file) != 1)
      {
        fprintf(stderr, "Failed to read chunk data of size [%i]\n", chunk_size);
        free(chunk_data);
        return -1;
      }

      // Do something with the chunk data
      printf("Read chunk_data!\n");
      // Allocate a 3D array to store the voxels
      voxel*** voxels = malloc(grid_size_x * sizeof(voxel**));
      for (int i = 0; i < grid_size_x; i++) {
        voxels[i] = malloc(grid_size_y * sizeof(voxel*));
        for (int j = 0; j < grid_size_y; j++) {
          voxels[i][j] = malloc(grid_size_z * sizeof(voxel));
        }
      }

      // Iterate over the voxels in the grid and populate the 3D array
      int color = -1;
      for (int x = 0; x < grid_size_x; x++) {
        for (int y = 0; y < grid_size_y; y++) {
          for (int z = 0; z < grid_size_z; z++) {
            // Unpack the packed integer value to extract the voxel data
            // ...
            voxel v = {x, y, z, color };
            voxels[x][y][z] = v;
          }
        }
      }

      // Iterate over the 3D array and print the voxel data
      for (int x = 0; x < grid_size_x; x++) {
        for (int y = 0; y < grid_size_y; y++) {
          for (int z = 0; z < grid_size_z; z++) {
            voxel v = voxels[x][y][z];
            printf("Voxel at (%d, %d, %d): color=%d\n", v.x, v.y, v.z, v.color);
          }
        }
      }
      // ...
      free(chunk_data);
    }*/

    // Read the magic number from the file
    /*fread(magic, sizeof(char), 4, vox_file);

    // Check if the magic number is correct
    if (strcmp(magic, "VOX ") != 0)
    {
        // Print an error message and exit if the magic number is invalid
        printf("Error: Invalid vox file!\n");
        exit(1);
    }

    // Read the version number from the file
    fread(&version, sizeof(int), 1, vox_file);

    // Check if the version number is supported
    if (version != 150)
    {
        // Print an error message and exit if the version is not supported
        printf("Error: Unsupported vox file version!\n");
        exit(1);
    }*/

    // Read the voxel data from the file
    // ...
