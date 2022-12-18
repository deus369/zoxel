#include <stdio.h>
#include <stdlib.h>

#define zoxel_debug_vox_read

/* Define a struct to store the voxel data. */
typedef struct Voxel {
  unsigned char x;
  unsigned char y;
  unsigned char z;
  unsigned char color;
} Voxel;

/* Define a struct to store the vox file data. */
typedef struct VoxFile {
  int numVoxels;
  Voxel* voxels;
} VoxFile;

#define VOX_MAGIC "VOX "
#define VOX_MAIN "MAIN"
#define VOX_FILE_SIZE "SIZE"
#define VOX_FILE_XYZI "XYZI"
#define VOX_SIZE_INT 32
#define VOX_SUPPORTED_VERSION 150

typedef struct {
  unsigned char x;
  unsigned char y;
  unsigned char z;
  unsigned char color;
} vox_voxel;

// dynamically set voxels array
/*typedef struct
{
  unsigned char x;
  unsigned char y;
  unsigned char z;
  unsigned char *voxels;
} vox_file_voxels;*/
  // vox_file_voxels voxels;

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
  
} vox_file_pallete;

typedef struct
{
  vox_file_header header;
  vox_file_chunk main;
  vox_file_pack pack;
  vox_file_pallete palette;
  vox_file_chunk_child *chunk_childs;  // allocate dynamically
} vox_file;

int peek(FILE* file)
{
  int c = fgetc(file);
  ungetc(c, file);
  return c;
}

/**
This code reads the VOX file header and then reads each chunk in the file one by one.
The chunk id and chunk size are read first, followed by the chunk data itself.
The chunk data is stored in a dynamically allocated buffer and is then processed as needed.
*/
int read_vox(const char* filename, vox_file *vox)
{
    // Open the vox file for reading
    // FILE *file = fopen(filename, "rb");
    FILE *file = fopen(filename, "r");
    // Check if the file was opened successfully
    if (file == NULL)
    {
        // Print an error message and exit if the file could not be opened
        printf("Error: Could not open vox file [%s]\n", filename);
        return -1;
    }
    #ifdef zoxel_debug_vox_read
    printf("== Reading vox file [%s] ==\n", filename);
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
      if (vox->pack.name[0] != 'P' || vox->pack.name[1] != 'A' || vox->pack.name[2] != 'C' || vox->pack.name[3] != 'K')
      {
        printf("Bad Token: token is not PACK\n");
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

    #ifdef zoxel_debug_vox_read

    #endif
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
        else
        {
          voxel_bytes[j] = fgetc(file);
        }
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
    #ifdef zoxel_debug_vox_read
    printf("== Success reading vox [%s] ==\n", filename);
    #endif
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

    // Close the vox file when we're done
    fclose(file);
    return 0;
}